#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPoint>

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);

    //draw
    virtual void paintEvent(QPaintEvent *);


    //transform
    QPoint transform(int row, int col);


    //varaibles
    int _d = 40;
    int _r = _d/2;


signals:

};

#endif // BOARD_H
