#ifndef POSITIONSTATDIALOG_H
#define POSITIONSTATDIALOG_H

#include <QDialog>

#include "chessboard.h"

namespace Ui {
class PositionStatDialog;
}

class PositionStatDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PositionStatDialog(ChessBoard& chessBoard, PieceColor color, QWidget *parent = 0);
    ~PositionStatDialog();
    
private:
    Ui::PositionStatDialog *ui;
};

#endif // POSITIONSTATDIALOG_H
