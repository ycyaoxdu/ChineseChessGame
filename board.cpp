#include "board.h"

#include <QPainter>


Board::Board(QWidget *parent) : QWidget(parent)
{
    init();
}

/*
**
*/
void Board::init(){
    for(int i = 0 ; i < 32 ; ++i){
        _p[i].init(i);
    }
    update();
}


/*
**
*/
QPoint Board::transform(int row, int col){
    /*
        棋盘相对坐标转换为平面绝对坐标
    */
    int r = (1 + row) * _d;
    int c = (1 + col) * _d;
    return QPoint{r, c};
}


/*
**
*/
bool Board::isDead(int id){
    /*
        由id判断棋子是否存活
    */
    if(id >=0 && id <32){
        return _p[id]._dead;
    }
    return false;
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
   //获取棋子中心点相对坐标
   //要把相对坐标转换为绝对坐标
   return transform(_p[id]._col, _p[id]._row);
   //此处row,col交换位置才得到了正确的结果
}


QRect Board::getCell(int id){
    //写字的区域
    QPoint p = pieceCenter(id);

    return QRect{QPoint{p.x()-_r, p.y()-_r}, QSize(_d, _d )};
}

//是否可选（控制红黑）
bool Board::canSelect(int id){
    return _bRedTurn == _p[id]._red;
}

//
bool Board::sameColor(int p1, int p2){
    if(p1 == -1 || p2 == -1){
        return false;
    }
    return _p[p1]._red == _p[p2]._red;
}

//
bool Board::isBottomSide(int id){
    //黑在下
    // true ^ true = false
    // false ^ true = true
    return _p[id]._red ^ true;
}

//赋权值相加，对纵向和横向加以区别
int Board::count(int row1, int col1, int row2, int col2){
    return 10 * abs(row1-row2) + abs(col1-col2);
}
//
int Board::calCount(int id, int row, int col){
    return count(_p[id]._row, _p[id]._col, row, col);
}

//
bool Board::kaXIANGyan(int id, int row, int col){
    int rEye = (_p[id]._row + row) / 2 ;
    int cEye = (_p[id]._col + col) / 2 ;
    if(getPieceId(rEye, cEye) != -1){
        return true;
    }
    return false;
}

//
bool Board::banMAtui(int id, int row, int col, bool crosswise){
    if(crosswise){
        //横向
        int tmp = (_p[id]._col + col) / 2 ;
        if(getPieceId(_p[id]._col, tmp) != -1){
            return true;
        }
    } else {
        //纵向
        int tmp = (_p[id]._row + row) / 2 ;
        if(getPieceId(tmp, _p[id]._col) != -1){
            return true;
        }
    }
    return false;
}

//
int Board::getPieceCountAtLine(int row1, int col1, int row2, int col2){
    if(row1 != row2 && col1 != col2){
        return -1;
    }
    if(row1 == row2 && col1 == col2){
        return -1;
    }
    int ret = 0;

    if(row1 == row2){
        int cMin = col1 < col2 ? col1 : col2 ;
        int cMax = col1 > col2 ? col1 : col2 ;
        //
        for(int c = cMin + 1 ; c < cMax ; ++c){
            if(getPieceId(row1, c) != -1){
                ++ret;
            }
        }
    } else {
        int rMin = row1 < row2 ? row1 : row2 ;
        int rMax = row1 > row2 ? row1 : row2 ;
        //
        for (int r = rMin + 1; r < rMax ; ++r){
            if(getPieceId(r, col1) != -1){
                ++ret;
            }
        }
    }
    return ret;
}

/*
**
*/
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
    if(id == _selectid){
        p.setBrush(QBrush(Qt::gray));
    } else {
        p.setBrush(QBrush(Qt::yellow));
    }

    p.drawEllipse(pieceCenter(id), _r, _r);

    p.setFont(QFont("system", _r*1.2, 700));
    p.drawText(getCell(id), getName(id), QTextOption(Qt::AlignCenter));


    update();
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

/*
**
*/
void Board::mouseReleaseEvent(QMouseEvent *ev){
    /*
        捕捉鼠标点击（释放过程）事件
    */
    //左键控制
    if(ev->button() != Qt::LeftButton){
        return;
    }
    //获取到的坐标里，xy是反的
    click(ev->pos());
}

void Board::click(QPoint pt){
    int r, c;
    bool clicked = getClickPos(pt, r, c);
    if(!clicked){
        return;
    }
    //获取点击位置棋子编号
    int clickid = getPieceId(r, c);

    select(clickid, r, c);
}

//找到鼠标点击的点
bool Board::getClickPos(QPoint p, int &row, int &col){
    //依次遍历，找到棋子
    for(row = 0 ; row <= 9 ; ++row){
        for(col = 0 ; col <= 8 ; ++col){
                                                //交换x，y
            QPoint dist = transform(row, col) - QPoint{p.y(), p.x()};
            if(dist.x() * dist.x() + dist.y() * dist.y() < _r * _r){
                return true;
            }
        }
    }
    return false;
}

//获取棋子id
int Board::getPieceId(int row, int col){
    for(int i = 0 ; i < 32 ; ++i){
        if( _p[i]._row == row && _p[i]._col == col  && !isDead(i)){
            return i;
        }
    }
    return -1;
}

//选择棋子
void Board::select(int id, int row, int col){
    if(_selectid == -1){
        trySelect(id);
    } else {
        tryMove(id, row, col);
    }
}


//尝试选中
void Board::trySelect(int id){
    //判断边（红黑）
    if(!canSelect(id)){
        return;
    }
    _selectid = id;
    update();
}


//
void Board::killPiece(int id){
    if(id == -1){
        return;
    }
    _p[id]._dead = true;
}



//尝试移动
void Board::tryMove(int killid, int row, int col){
    if(killid != -1 && sameColor(killid, _selectid)){
        trySelect(killid);
        return;
    }

    if(canMove(_selectid, killid, row, col)){
        //移动棋子
        movePiece(_selectid, killid, row, col);
        //重置选中的序号
        _selectid = -1;
        //更新棋盘
        update();
    }
}

//
bool Board::canMoveJU(int sel, int kill, int row, int col){
    int cnt = calCount(sel, row, col);
    if(cnt > 10 && cnt % 10 != 0){
        return false;
    }
    int row1 = _p[sel]._row;
    int col1 = _p[sel]._col;

    int n = getPieceCountAtLine(row1, col1, row, col);
    if(n == 0){
        return true;
    }

    return false;

}
//
bool Board::canMoveMA(int sel, int kill, int row, int col){
    int cnt = calCount(sel, row, col);
    if(cnt == 12){
        return !banMAtui(sel, row, col, true);
    }
    if(cnt == 21){
        return !banMAtui(sel, row, col, false);
    }

    return false;

}
//
bool Board::canMoveXIANG(int sel, int kill, int row, int col){
    if(isBottomSide(sel)){
        if(row < 5){
            return false;
        }
    } else {
        if(row > 4){
            return false;
        }
    }
    int cnt = calCount(sel, row, col);
    if(cnt != 22 ){
        return false;
    }
    return !kaXIANGyan(sel, row, col);
}
//
bool Board::canMoveSHI(int sel, int kill, int row, int col){
    if(col < 3 || col > 5){
        return false;
    }
    if(isBottomSide(sel)){
        if(row < 7){
            return false;
        }
    } else {
        if(row > 2){
            return false;
        }
    }
    int cnt = calCount(sel, row, col);
    if(cnt == 11){
        return true;
    }

    return false;
}
//
bool Board::canMoveJIANG(int sel, int kill, int row, int col){
    if(col < 3 || col > 5){
        return false;
    }
    if(isBottomSide(sel)){
        if(row < 7){
            return false;
        }
    } else {
        if(row > 2){
            return false;
        }
    }
    int cnt = calCount(sel, row, col);
    if(cnt == 10 || cnt == 1){
        return true;
    }

    return false;

}
//
bool Board::canMovePAO(int sel, int kill, int row, int col){
    int cnt = calCount(sel, row, col);
    if(cnt > 10 && cnt % 10 != 0){
        return false;
    }
    int row1 = _p[sel]._row;
    int col1 = _p[sel]._col;

    int n = getPieceCountAtLine(row1, col1, row, col);
    if(n == 1 && kill != -1){
        return true;
    }
    if(n == 0 && kill == -1){
        return true;
    }

    return false;

}
//
bool Board::canMoveZU(int sel, int kill, int row, int col){
    int cnt = calCount(sel, row, col);
    if(cnt != 1 && cnt != 10){
        return false;
    }
    int row1 = _p[sel]._row;

    if(isBottomSide(sel)){
        if(row1 >= 5){
            //只能前进
            return (row - row1 < 0);
        } else {
            //前进或横移
            return (row - row1 <= 0);
        }
    } else {
        if(row1 <= 4){
            return (row - row1 > 0);
        } else {
            return (row - row1 >= 0);
        }
    }

    return false;
}

//判断是否可移动
bool Board::canMove(int sel, int kill, int row, int col){
    if(sameColor(sel, kill)){
        return false;
    }
    //走棋规则
    switch (_p[sel]._type) {
    case Piece::JU:
       return canMoveJU(sel, kill, row, col);
    case Piece::MA:
       return canMoveMA(sel, kill, row, col);
    case Piece::XIANG:
        return canMoveXIANG(sel, kill, row, col);
    case Piece::SHI:
        return canMoveSHI(sel, kill, row, col);
    case Piece::JIANG:
        return canMoveJIANG(sel, kill, row, col);
    case Piece::PAO:
        return canMovePAO(sel, kill, row, col);
    case Piece::ZU:
        return canMoveZU(sel, kill, row, col);
    default:
        return false;
    }
    return false;
}

//移动
void Board::movePiece(int sel, int kill, int row, int col){

    //被杀棋子不再显示
    killPiece(kill);
    //执行移动
    doMovePiece(sel, row, col);

}
//
void Board::doMovePiece(int sel, int row, int col){
    _p[sel]._row = row;
    _p[sel]._col = col;

    //控制交换走棋
    _bRedTurn = !_bRedTurn;
}
