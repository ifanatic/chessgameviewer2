#include "piecepathdialog.h"
#include "ui_piecepathdialog.h"

PiecePathDialog::PiecePathDialog(const ChessBoardPiece &piece,
                                 const vector<ChessPosition> &positions,
                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PiecePathDialog)
{
    ui->setupUi(this);

    ui->widget->setPositions(positions);
    ui->widget->setPiece(piece);
    ui->widget->update();
}

PiecePathDialog::~PiecePathDialog()
{
    delete ui;
}
