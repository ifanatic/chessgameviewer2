#include "chessboardview.h"

#include <iostream>

#include <QPainter>
#include <QFile>
#include <QBitmap>
#include <iostream>
#include <QPen>

#include "utils.h"

void ChessboardView::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    int widht = this->width();
    int height=this->height();

    int stepWidth = widht / 8;
    int stepHeight = height / 8;

    bool black = false;

    for(int i = 0; i < 8; ++i)
    {
        black = !black;

        for(int j = 0; j < 8; ++j)
        {
            QColor color = black ? QColor(200, 200, 200) : QColor(100, 100, 100);
            painter.fillRect(i * stepWidth, j * stepHeight, stepWidth, stepHeight, color);
            black = !black;

        }
    }

    if(_chessBoard != NULL)
    {
        PieceType type = None;

        for(int i = 0; i < 8; ++i)
        {
            for(int j = 0; j < 8; ++j)
            {
                type = _chessBoard->getPiece(i, j).type;

                if(type != None)
                {
                    QPixmap pieceGlyph(getFileNameForPiece(_chessBoard->getPiece(i, j)));
                    pieceGlyph.setMask(pieceGlyph.createMaskFromColor(QColor(255, 255, 0)));

                    painter.drawPixmap(j * stepWidth, height - stepHeight * (i + 1),
                                       stepWidth, stepHeight,
                                       pieceGlyph);
                }
            }
        }

        ChessPosition lastSrc = _chessBoard->lastSrc();
        ChessPosition lastDst = _chessBoard->lastDst();

        if(lastSrc.col >= 0 && lastSrc.row >= 0)
        {
//            painter.setBrush(Qt::SolidPattern);
            QPen pen(QColor(255, 0, 0));
            pen.setWidth(5);
            painter.setPen(pen);

            painter.drawRect(stepWidth * lastSrc.col + 5, height - stepHeight * (lastSrc.row + 1),
                                 stepWidth - 10, stepHeight - 10);
        }

        if(lastDst.col >= 0 && lastDst.row >= 0)
        {
//            painter.setBrush(Qt::SolidPattern);
            QPen pen(QColor(0, 0, 255));
            pen.setWidth(5);
            painter.setPen(pen);

            painter.drawRect(stepWidth * lastDst.col + 5, height - stepHeight * (lastDst.row + 1),
                                 stepWidth - 10, stepHeight - 10);
        }
    }

    painter.end();
}

void ChessboardView::mousePressEvent(QMouseEvent* event)
{
    int widht = this->width();
    int height=this->height();

    int stepWidth = widht / 8;
    int stepHeight = height / 8;

    int row = (int)(((double)(height - event->y()) / (double)height) * 8);
    int col = (int)(((double)(event->x()) / (double)widht) * 8);

    if(event->button() == Qt::LeftButton)
    {
        if(_chessBoard == NULL)
        {
            return;
        }

        if(_chessBoard->getPiece(row, col).type != None)
        {
            emit onPieceClick(row, col);
        }
    }
}

ChessboardView::ChessboardView(QWidget* parent) : QWidget(parent)
{
    setGeometry(this->geometry().x(), this->geometry().y(), 500, 500);

    _chessBoard = NULL;
}

void ChessboardView::updateChessboard()
{
    this->repaint();
}
