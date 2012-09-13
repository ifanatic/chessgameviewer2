#ifndef PIECEPATHVIEW_H
#define PIECEPATHVIEW_H

#include <QWidget>

#include <vector>
#include <algorithm>

#include "chessboard.h"

using namespace std;

class PiecePathView : public QWidget
{
    Q_OBJECT

private:
    vector<ChessPosition> _positions;
    ChessBoardPiece _piece;

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit PiecePathView(
                           QWidget *parent = 0);
    

    void setPositions(const vector<ChessPosition>& positions)
    {
        _positions = positions;
    }

    void setPiece(const ChessBoardPiece& piece)
    {
        _piece = piece;
    }

signals:
    
public slots:
    
};

#endif // PIECEPATHVIEW_H
