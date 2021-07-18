#ifndef NETGAME_H
#define NETGAME_H

#include "board.h"
#include <QTcpServer>
#include <QTcpSocket>

/*
 *  1.执红执黑      第一个字节固定值1，第二个字节是执棋信息，1-》接收方红，0-》接收方黑
 *  2.点击信息      第一个字节固定值2，第二个row，第三个col， 第四个点击id
 *
*/
class NetGame : public Board
{
    Q_OBJECT
public:
    NetGame(bool server);



    QTcpServer* _server;
    QTcpSocket* _socket;


    virtual void select(int id, int row, int col);


public slots:
    void slotNewConnection();
    void slotRecv();

};

#endif // NETGAME_H
