#include "piecepathview.h"

#include <QPainter>
#include <QBitmap>
#include <QPoint>
#include <QPen>
#include <QBrush>

#include <utils.h>

void PiecePathView::paintEvent(QPaintEvent *event)
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

    if(_positions.size())
    {
        QPoint from;
        QPoint to;

        painter.setPen(QPen(QBrush(Qt::blue), 5));

        for(int i = (_positions.size() - 2); i >= 0; --i)
        {
            from.setX(_positions[i].col * stepWidth + stepWidth / 2);
            from.setY((7 - _positions[i].row) * stepHeight + stepHeight / 2);

            to.setX(_positions[i + 1].col * stepWidth + stepWidth / 2);
            to.setY((7 - _positions[i + 1].row) * stepHeight + stepHeight / 2);

            painter.drawLine(from, to);
        }

        painter.setPen(QPen(QBrush(Qt::red), 8));

        for(int i = (_positions.size() - 2); i >= 0; --i)
        {
            from.setX(_positions[i].col * stepWidth + stepWidth / 2);
            from.setY((7 - _positions[i].row) * stepHeight + stepHeight / 2);

            to.setX(_positions[i + 1].col * stepWidth + stepWidth / 2);
            to.setY((7 - _positions[i + 1].row) * stepHeight + stepHeight / 2);

            painter.drawEllipse(from, 7, 7);
            painter.drawEllipse(to, 7, 7);
        }

        QPixmap pieceGlyph(getFileNameForPiece(_piece));
        pieceGlyph.setMask(pieceGlyph.createMaskFromColor(QColor(255, 255, 0)));

        painter.drawPixmap(_positions[0].col * stepWidth, height - stepHeight * (_positions[0].row + 1),
                           stepWidth, stepHeight,
                           pieceGlyph);
    }
}

PiecePathView::PiecePathView(QWidget *parent) :
    QWidget(parent)
{

}
