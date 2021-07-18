#include "netgame.h"

NetGame::NetGame(bool server)
{
    _socket = NULL;
    _server = NULL;

    if(server){
        _server = new QTcpServer(this);
        _server->listen(QHostAddress::Any, 9999);

        connect(_server, SIGNAL(newConnection()), this, SLOT(slotNewConnection() ));
    } else {
        _socket = new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"), 9999);

        connect(_socket, SIGNAL(readyRead()), this, SLOT(slotRecv() ));
    }

}


void NetGame::select(int id, int row, int col){

    //防止黑点红、红点黑
    if(_selectid == -1 && id != -1){
        if(_p[id]._red != _bottomSide){
            return;
        }
    }


    Board::select(id, row, col);

    //transfer data
    char buf[4];
    buf[0] = 2;
    buf[1] = 9-row;
    buf[2] = 8-col;
    buf[3] = id;

    _socket->write(buf, 4);
}



void NetGame::slotNewConnection(){
    if(_socket){
        return;
    }

    _server->nextPendingConnection();

    connect(_socket, SIGNAL(readyRead()), this, SLOT(slotRecv() ));
    //data
    char buf[2];
    buf[0] = 1;
    buf[1] = 1;
    _socket->write(buf, 2);

    init(buf[1]==1);
}

void NetGame::slotRecv(){
    QByteArray ba = _socket->readAll();
    char cmd = ba[0];
    if(cmd == 1){
        //init
        init(ba[1]==0);
    } else if(cmd == 2) {
        int row = ba[1];
        int col = ba[2];
        int id = ba[3];

        Board::select(id, row, col);
    }

}
