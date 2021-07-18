#include "singlegame.h"

#include <QTimer>

//
void SingleGame::select(int id, int row, int col){
    if(!this->_bRedTurn){
        return;
    }

    //执行父类的函数（保证原有功能）
    Board::select(id, row, col);

    //如果轮到黑棋，调用电脑走棋
    if(!this->_bRedTurn){
        //等待0.1秒（刷新棋盘），在执行主机思考过程
        /*启动0.1秒定时器，防止主线程阻塞过久*/
        QTimer::singleShot(100, this, SLOT(computerMove()));

    }

}

//
void SingleGame::computerMove(){
    Step* tmp = getBestMove();
    movePiece(tmp->_moveid, tmp->_killid, tmp->_rowTo, tmp->_colTo);
    delete tmp;
    update();
}


//
void SingleGame::getAllPossibleMoves(QVector<Step *> &steps){
    //遍历
    //可计算红或黑可走的步数
    int min = 16, max = 32;
    if(this->_bRedTurn){
        min = 0;
        max = 16;
    }

    for(int i = min ; i < max ; ++i){
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
int SingleGame::calcScore(){
    /*
     *  车   马   象   士   将   炮   卒
     *
     */
    static int chessScore[] = {1000, 499, 100, 100, 15000, 501, 200};

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
int SingleGame::getMinScore(int level, int curMaxScore){
    if(level == 0){
        return calcScore();
    }

    //
    QVector<Step*> steps;
    getAllPossibleMoves(steps);

    int minScore = 999999;
    while(steps.count()){
        Step* s = steps.back();
        steps.removeLast();

        fakeMove(s);
        int score = getMaxScore(level-1, minScore);
        unfakeMove(s);
        delete s;

        //剪枝
        if(score <= curMaxScore){
            while(steps.count()){
                Step* step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }


        if(score < minScore){
            minScore = score ;
        }
    }
    return minScore;
}

//
int SingleGame::getMaxScore(int level, int curMinScore){
    if(level == 0){
        return calcScore();
    }
    //
    QVector<Step*> steps;
    getAllPossibleMoves(steps);

    int maxScore = -999999;
    while(steps.count()){
        Step* s = steps.back();
        steps.removeLast();

        fakeMove(s);
        int score = getMinScore(level-1, maxScore);
        unfakeMove(s);
        delete s;

        //剪枝
        if(score >= curMinScore){
            while(steps.count()){
                Step* step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if(score > maxScore){
            maxScore = score ;
        }

    }
    return maxScore;
}


//两步智能：内层选出所有可能路径的最小值，外层在各路径的最小值里选最大的一个

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
    int maxScore = -999999;

    Step* ret = nullptr;
    while(steps.count()){
        Step* s = steps.back();
        steps.removeLast();

        fakeMove(s);
        int score = getMinScore(this->_level-1, maxScore);
        unfakeMove(s);

        if(score > maxScore){
            maxScore = score;

            if(ret) {delete ret;}
            ret = s;
        } else {
            delete s;
        }
    }

    //4
    return ret;

}
