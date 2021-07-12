#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QBrush>

#include "piece.h"

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);

    //init
    void init();

    //draw
    virtual void paintEvent(QPaintEvent *);
    void drawPiece(QPainter& p, int id);

    //transform
    QPoint transform(int row, int col);

    //
    bool isDead(int id);
    bool isRed(int id);
    QString getName(int id);
    QPoint pieceCenter(int id);
    QPoint getTopLeft(int id);
    QRect getCell(int id);


    //varaibles
    int _d = 40;
    int _r = _d/2;
    Piece _p[32];



signals:

};

#endif // BOARD_H
