#include "positionstatdialog.h"
#include "ui_positionstatdialog.h"

#include "statprovider.h"

PositionStatDialog::PositionStatDialog(ChessBoard& chessBoard,
                                       PieceColor color,
                                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PositionStatDialog)
{
    ui->setupUi(this);

    StatProvider statProvider;
    PositionStat stat = statProvider.getStatForPosition(chessBoard, color);

    QString whiteTextPattern = "White wins: %1 - %2%";
    QString blackTextPattern = "Black wins: %1 - %2%";
    QString drawnsTextPattern = "Drawns : %1 - %2%";

    ui->qlWhiteStat->setText(whiteTextPattern.arg(
                                 stat.getWhiteWinsCount()).arg(
                                 stat.getWhiteWinsPercent()));

    ui->qlBlackStat->setText(blackTextPattern.arg(
                                 stat.getBlackWinsCount()).arg(
                                 stat.getBlackWinsPercent()));

    ui->qlDrawnsStat->setText(drawnsTextPattern.arg(
                                 stat.getDrawnsCount()).arg(
                                 stat.getDrawnsPercent()));
}

PositionStatDialog::~PositionStatDialog()
{
    delete ui;
}
