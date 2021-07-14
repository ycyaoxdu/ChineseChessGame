#include "piece.h"

Piece::Piece(){

}

QString Piece::name(){
    switch(this->_type){
    case JU:
        return "车";
    case MA:
        return "马";
    case XIANG:
        return "相";
    case SHI:
        return "士";
    case JIANG:
        return "将";
    case PAO:
        return "炮";
    case ZU:
        return "卒";
    }
    return "错误";
}

void Piece::init(int id){
    this->_id = id;
    this->_dead = false;
    this->_red = (id<16);
    if(id < 16){
        this->_row = this->pos[id].r;
        this->_col = this->pos[id].c;
        this->_type = this->pos[id].t;
    } else {
        this->_row = 9 - this->pos[id -16].r;
        this->_col = 8 - this->pos[id -16].c;
        this->_type = this->pos[id -16].t;
    }
}

void Piece::rotate(){
    this->_row = 9-this->_row;
    this->_col = 8-this->_col;
}
