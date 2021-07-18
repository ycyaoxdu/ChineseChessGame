#include "mainwindow.h"
#include <QHBoxLayout>
#include "singlegame.h"
#include "multigame.h"
#include "netgame.h"


MainWindow::MainWindow(int gameType, QWidget *parent) : QWidget(parent)
{
    _gameType = gameType;

    if(_gameType == 0){
        SingleGame* game = new SingleGame;
        CtrlPanel* panel = new CtrlPanel;

        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);

        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));


    } else if(_gameType == 1){
        MultiGame* game = new MultiGame;
        CtrlPanel* panel = new CtrlPanel;

        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    } else if(_gameType == 2){
        NetGame* game = new NetGame(true);
        CtrlPanel* panel = new CtrlPanel;

        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    } else if(_gameType == 3){
        NetGame* game = new NetGame(false);
        CtrlPanel* panel = new CtrlPanel;

        QHBoxLayout* hLay = new QHBoxLayout(this);
        hLay->addWidget(game, 1);
        hLay->addWidget(panel);
        connect(panel, SIGNAL(sigBack()), game, SLOT(slotBack()));
    }

}
