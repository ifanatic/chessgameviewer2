#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QString>

#include "chessboard.h"

class ChessboardView : public QWidget
{
    Q_OBJECT

private:
    ChessBoard* _chessBoard;


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);

public:
    ChessboardView(QWidget* parent = NULL);

    void setChessboard(ChessBoard* chessBoard) { _chessBoard = chessBoard; }

    void updateChessboard();

signals:
    void onPieceClick(int row, int col);
};

#endif // CHESSBOARDVIEW_H
