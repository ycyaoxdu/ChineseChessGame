#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "board.h"

class SingleGame : public Board
{
public:
    SingleGame();

    void select(int id, int row, int col);

    Step* getBestMove();

    void getAllPossibleMoves(QVector<Step*> &steps);

    void fakeMove(Step* step);
    void unfakeMove(Step* step);
    int calcScore();


};

#endif // SINGLEGAME_H
