#include "board.h"

#include <QPainter>


Board::Board(QWidget *parent) : QWidget(parent)
{

}

QPoint Board::transform(int row, int col){
    /*
        棋盘相对坐标转换为平面绝对坐标
    */
    int r = (1 + row) * _d;
    int c = (1 + col) * _d;
    return QPoint{r, c};
}


void Board::paintEvent(QPaintEvent *){
    /*
        画棋盘
    */

    QPainter p(this);

    //横线
    for(int i = 0 ; i <= 9 ; ++i){
        p.drawLine(transform(0, i), transform(8, i));
    }
    //竖线
    for(int j = 0 ; j <= 8 ; ++j){
        if(j == 0 || j == 8){
            p.drawLine(transform(j, 4), transform(j, 5));
        }
        p.drawLine(transform(j, 0), transform(j, 4));
        p.drawLine(transform(j, 5), transform(j, 9));
    }
    //宫格
    p.drawLine(transform(3, 0), transform(5, 2));
    p.drawLine(transform(3, 2), transform(5, 0));
    p.drawLine(transform(3, 7), transform(5, 9));
    p.drawLine(transform(3, 9), transform(5, 7));


    return;
}
