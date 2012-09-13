#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include "gameplayer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSqlQueryModel* _gamesModel;
    GamePlayer* _player;

    bool _isNeedSelectFigure;

    bool openGame(int id);
    void updateViews();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbSearch_clicked();

    void on_pbClear_clicked();

    void on_pbOpen_clicked();

    void on_pbNext_clicked();

    void on_pbPrev_clicked();

    void on_pbBegin_clicked();

    void on_pbEnd_clicked();

    void on_pbFindPgn_clicked();

    void on_actionImport_PGN_triggered();

    void on_actionExport_to_PGN_triggered();

    void on_qpbStatForPos_clicked();

    void onPieceClicked(int row, int col);

    void on_qlTrackFigure_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
