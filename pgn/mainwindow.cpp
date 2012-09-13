#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>
#include <iostream>
#include <sstream>
#include <QSqlRecord>

#include <QMessageBox>
#include <QModelIndexList>

#include <iostream>

#include "ply.h"
#include "fenform.h"

#include <QFileDialog>
#include <QProgressDialog>

#include "pgnimporter.h"
#include "gamefinder.h"
#include "pgnexporter.h"

#include "positionstatdialog.h"
#include "piecepathtracer.h"
#include "piecepathdialog.h"

bool MainWindow::openGame(int id)
{
    cout << "opengame: " << endl;

    GameFinder finder;
    Game game = finder.getGameById(id);

    ui->lBlack->setText(game.tags()["Black"].value().c_str());
    ui->lWhite->setText(game.tags()["White"].value().c_str());
    ui->lWinner->setText(game.tags()["Result"].value().c_str());

    vector<pgn::Ply> moves;

    ui->lwMoves->clear();

    MoveList::iterator moveIter = game.moves().begin();
    MoveList::iterator moveIterEnd = game.moves().end();

    QString whitePattern = "White: %1";
    QString blackPattern = "Black: %1";
    while(moveIter != moveIterEnd)
    {
        ostringstream notation;

        if(moveIter->white() != NULL)
        {
            notation << (*moveIter->white());

            ui->lwMoves->addItem(new QListWidgetItem(whitePattern.arg(
                                                         notation.str().c_str()), ui->lwMoves));
            moves.push_back(*moveIter->white());
        }

        if(moveIter->black() != NULL)
        {
            notation.clear();
            notation.str("");

            notation << (*moveIter->black());

            ui->lwMoves->addItem(new QListWidgetItem(blackPattern.arg(
                                                         notation.str().c_str()), ui->lwMoves));
            moves.push_back(*moveIter->black());
        }

        ++moveIter;
    }

    _player->setMoves(moves);
    _player->goToBegin();

    updateViews();

    return true;
}

void MainWindow::updateViews()
{
    if(_player->getCurrentPos() > 0)
    {
        ui->lwMoves->item(_player->getCurrentPos())->setSelected(true);

        ui->lwMoves->scrollTo(ui->lwMoves->selectionModel()->currentIndex());
    }

    ui->cbvGame->updateChessboard();

    if(_player->getCurrentPos() < 1)
    {
        ui->pbPrev->setEnabled(false);
    }
    else
    {
        ui->pbPrev->setEnabled(true);
    }

    if(_player->getCurrentPos() == (_player->movesCount() - 1))
    {
        ui->pbNext->setEnabled(false);
    }
    else
    {
        ui->pbNext->setEnabled(true);
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->cbvGame, SIGNAL(onPieceClick(int,int)), this, SLOT(onPieceClicked(int,int)));

    _gamesModel = new QSqlQueryModel(this);
    _gamesModel->setQuery("SELECT * FROM GAMES");

    _player = new GamePlayer();

    ui->tvGames->setModel(_gamesModel);
    ui->tvGames->hideColumn(0);

    _isNeedSelectFigure = false;
}

MainWindow::~MainWindow()
{
    if(_player != NULL)
    {
        delete _player;
    }

    delete ui;
}

void MainWindow::on_pbSearch_clicked()
{
    QString pattern = "select * from games where id in (select game_id from moves where "
            "fen like '%1')";
    pattern = pattern.arg(ui->leSearchString->text().trimmed());

    _gamesModel->setQuery(pattern);
}

void MainWindow::on_pbClear_clicked()
{
    _gamesModel->setQuery("SELECT * FROM GAMES");
}

void MainWindow::on_pbOpen_clicked()
{
    QModelIndexList selRows = ui->tvGames->selectionModel()->selectedRows();

    if(selRows.size() == 0)
    {
        std::cout << "No items selected" << std::endl;
        return;
    }

    QModelIndex selectedElement = selRows.at(0);
    QString text = _gamesModel->data(_gamesModel->index(selectedElement.row(), 0)).toString();

    if(!openGame(text.toInt()))
    {
        QMessageBox msg;
        msg.setText(QString("Cannot open game #") + text);
        msg.exec();
    }
    else
    {
        cout << "Open complete" << endl;
        ui->cbvGame->setChessboard(&_player->chessBoard());
    }
}

void MainWindow::on_pbNext_clicked()
{
    _player->next();

    updateViews();
}

void MainWindow::on_pbPrev_clicked()
{
    _player->prev();

    updateViews();
}

void MainWindow::on_pbBegin_clicked()
{
    _player->goToBegin();

    updateViews();
}

void MainWindow::on_pbEnd_clicked()
{
    _player->goToEnd();

    updateViews();
}

void MainWindow::on_pbFindPgn_clicked()
{
    FENForm fen;
    QString fenStr = fen.getFENForm(_player->chessBoard(), _player->currentColor()).c_str();
    ui->leSearchString->setText(fenStr);
    ui->pbSearch->click();
}

void MainWindow::on_actionImport_PGN_triggered()
{
    QFileDialog openFileDialog(this);
    openFileDialog.exec();
    openFileDialog.setFilter("*.pgn");

    if(openFileDialog.result() == QDialog::Accepted)
    {
        if(openFileDialog.selectedFiles().size() == 0)
        {
            return;
        }

        PGNImporter importer;

        QProgressDialog progressDialog(QString("Import"), "", 0, 100);

        connect(&importer, SIGNAL(onProgress(int)), &progressDialog, SLOT(setValue(int)));
        importer.importFromFile(openFileDialog.selectedFiles()[0]);

        ui->pbClear->click();
    }
}

void MainWindow::on_actionExport_to_PGN_triggered()
{
    QFileDialog openFileDialog(this);
    openFileDialog.exec();
    openFileDialog.setFilter("*.pgn");

    if(openFileDialog.result() == QDialog::Accepted)
    {
        if(openFileDialog.selectedFiles().size() == 0)
        {
            return;
        }

        vector<int> ids;

        for(int i = 0; i < _gamesModel->rowCount(); ++i)
        {
            QModelIndex selectedElement = _gamesModel->index(i, 0);
            QString text = _gamesModel->data(
                        _gamesModel->index(selectedElement.row(), 0)).toString();
            ids.push_back(text.toInt());
        }

        PGNExporter exporter;

        QProgressDialog progressDialog(QString("Import"), "", 0, 100);

        connect(&exporter, SIGNAL(onProgress(int)), &progressDialog, SLOT(setValue(int)));
        exporter.exportToFile(ids, openFileDialog.selectedFiles()[0]);

//        ui->pbClear->click();
    }
}

void MainWindow::on_qpbStatForPos_clicked()
{
    PositionStatDialog statDialog(_player->chessBoard(), _player->currentColor(), this);
    statDialog.exec();
}

void MainWindow::onPieceClicked(int row, int col)
{
    if(_isNeedSelectFigure)
    {


        PiecePathTracer pathTracer;
        vector<ChessPosition> path = pathTracer.path(
                    _player->getMoves(),
                    _player->getCurrentPos(),
                    ChessPosition(row, col));
        _isNeedSelectFigure = false;

        PiecePathDialog pathDialog(
                    _player->chessBoard().getPiece(row, col),
                    path,
                    this);
        pathDialog.exec();
    }
}

void MainWindow::on_qlTrackFigure_clicked()
{
    _isNeedSelectFigure = true;
}
