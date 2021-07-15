#include "singlegame.h"

SingleGame::SingleGame()
{

}

//
void SingleGame::select(int id, int row, int col){
    if(!this->_bRedTurn){
        return;
    }

    //执行父类的函数（保证原有功能）
    Board::select(id, row, col);

    //如果轮到黑棋，调用电脑走棋
    if(!this->_bRedTurn){
        Step* tmp = getBestMove();
        movePiece(tmp->_moveid, tmp->_killid, tmp->_rowTo, tmp->_colTo);
        delete tmp;
        update();

    }

}

//
void SingleGame::getAllPossibleMoves(QVector<Step *> &steps){
    //遍历
    for(int i = 16 ; i < 32 ; ++i){
        if(_p[i]._dead){
            continue;
        }

        for(int row = 0 ; row <= 9 ; ++row){
            for(int col = 0 ; col <= 8 ; ++col){
                int killid = this->getPieceId(row, col);
                if(sameColor(killid, i)){
                    continue;
                }

                if(canMove(i, killid, row, col)){
                    saveStep(i, killid, row, col, steps);
                }
            }
        }
    }
}

//
void SingleGame::fakeMove(Step *step){

    killPiece(step->_killid);
    doMovePiece(step->_moveid, step->_rowTo, step->_colTo);
}

//
void SingleGame::unfakeMove(Step *step){
    relivePiece(step->_killid);
    doMovePiece(step->_moveid, step->_rowFrom, step->_colFrom);
}

//评价局面分
//仅实现了一步自走，很笨
int SingleGame::calcScore(){
    /*
     *  车   马   象   士   将   炮   卒
     *  10   8    4    4   999  7    3
     *
     */
    static int chessScore[] = {10, 8, 8, 4, 999, 7, 3};

    //  blackScore - redScore;
    int blackScore = 0, redScore = 0;
    for(int i = 0 ; i < 16 ; ++i){
        if(_p[i]._dead){
            continue;
        }
        redScore += chessScore[_p[i]._type];
    }

    for(int i = 16 ; i < 32 ; ++i){
        if(_p[i]._dead){
            continue;
        }
        blackScore += chessScore[_p[i]._type];
    }

    return blackScore - redScore;
}

//
Step* SingleGame::getBestMove(){
/*
**  1.找出可以走的步
**  2.尝试走
**  3.评估结果
**  4.做出最好的选择
*/

    QVector<Step*> steps;
    //1
    getAllPossibleMoves(steps);
    //2,3
    int maxScore = -10000;
    Step* ret = nullptr;
    for(auto it = steps.begin() ; it != steps.end() ; ++it){
        Step* s = *it;

        fakeMove(s);
        int score = calcScore();
        unfakeMove(s);

        if(score > maxScore){
            maxScore = score;
            ret = s;
        }
    }

    //4
    return ret;

}
