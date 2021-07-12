#include "board.h"

#include <QPainter>


Board::Board(QWidget *parent) : QWidget(parent)
{
    init();
}

void Board::init(){
    for(int i = 0 ; i < 32 ; ++i){
        _p[i].init(i);
    }
    update();
}

QPoint Board::transform(int row, int col){
    /*
        棋盘相对坐标转换为平面绝对坐标
    */
    int r = (1 + row) * _d;
    int c = (1 + col) * _d;
    return QPoint{r, c};
}

bool Board::isDead(int id){
    /*
        由id判断棋子是否存活
    */
    if(id >=0 && id <32){
        return _p[id]._dead;
    }
    return true;
}

bool Board::isRed(int id){
    //获取颜色
    return _p[id]._red;
}

QString Board::getName(int id){
    //获取棋子名称
    return _p[id].name();
}

QPoint Board::pieceCenter(int id){
   //获取棋子中心点坐标
   //要把相对坐标转换为绝对坐标
   return transform(_p[id]._col, _p[id]._row);
   //此处row,col交换位置才得到了正确的结果
}

QPoint Board::getTopLeft(int id){
    //获取棋子左上角点的坐标
    return pieceCenter(id) - QPoint(_r, _r);
}

QRect Board::getCell(int id){
    //写字的区域
    //-1：该矩形包含左上两条边，不包含右下两条边
    return QRect{getTopLeft(id), QSize(_d, _d )};
}

void Board::drawPiece(QPainter &p, int id){
    /*
        画棋子：圆、底色、字、字色
    */
    if(isDead(id)){
        return;
    }
    //根据棋色设置颜色
    QColor color;
    if(isRed(id)){
        color = Qt::red;
    } else {
        color = Qt::black;
    }
    //设置笔和颜色
    p.setPen(QPen(QBrush(color), 2));
    //设置底色
    p.setBrush(QBrush(Qt::yellow));

    p.drawEllipse(pieceCenter(id), _r, _r);

    p.setFont(QFont("system", _r*1.2, 700));
    p.drawText(getCell(id), getName(id), QTextOption(Qt::AlignCenter));

    return;
}

void Board::paintEvent(QPaintEvent *){
    /*
        画棋盘：横线、竖线、棋子
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

    //
    for(int i = 0 ; i< 32 ; ++i){
        drawPiece(p, i);
    }

    return;
}
