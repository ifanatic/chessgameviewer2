#ifndef PIECEPATHDIALOG_H
#define PIECEPATHDIALOG_H

#include <QDialog>

#include <algorithm>
#include <vector>

#include "chessboard.h"

using namespace std;

namespace Ui {
class PiecePathDialog;
}

class PiecePathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PiecePathDialog(const ChessBoardPiece& piece,
                             const vector<ChessPosition>& positions,
                             QWidget *parent = 0);
    ~PiecePathDialog();
    
private:
    Ui::PiecePathDialog *ui;
};

#endif // PIECEPATHDIALOG_H
