#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "board.h"


class SingleGame : public Board
{
    Q_OBJECT
public:
    SingleGame(){
        _level = 3;
    };

    virtual void select(int id, int row, int col);

    Step* getBestMove();

    void getAllPossibleMoves(QVector<Step*> &steps);

    void fakeMove(Step* step);
    void unfakeMove(Step* step);
    int calcScore();

    int getMinScore(int level);
    int getMaxScore(int level);

    int _level;

public slots:
    //槽函数
    void computerMove();


};

#endif // SINGLEGAME_H
