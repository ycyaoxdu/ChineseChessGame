#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QBrush>
#include <QMouseEvent>
#include <QVector>

#include "piece.h"
#include "step.h"

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);

    //board varaibles
    int _d = 40;
    int _r = _d/2;

    //game data
    Piece _p[32];
    bool _bRedTurn = true;
    bool _bottomSide;
    int _selectid = -1;
    int killid = -1;
    QVector<Step*> _steps;


    //init
    void init(bool bottomRed);

    //transform
    QPoint transform(int row, int col);

    //get info func
    bool isDead(int id);
    bool isRed(int id);
    QString getName(int id);
    QPoint pieceCenter(int id);
    QRect getCell(int id);
    int getPieceId(int row, int col);
    bool canSelect(int id);
    bool sameColor(int p1, int p2);
    bool isBottomSide(int id);
    int count(int row1, int col1, int row2, int col2);
    int calCount(int id, int row, int col);
    bool kaXIANGyan(int id, int row, int col);
    bool banMAtui(int id, int row, int col, bool crosswise);
    int getPieceCountAtLine(int row1, int col1, int row2, int col2);


    //draw
    virtual void paintEvent(QPaintEvent *);
    void drawPiece(QPainter& p, int id);
    void drawInitPosition(QPainter& p, int row, int col);
    void drawBoard(QPainter& p);


    //select & move
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    void click(QPoint pt);
    bool getClickPos(QPoint p, int &row, int &col);
    void select(int id, int row, int col);
    void trySelect(int id);
    void tryMove(int killId, int row, int col);
    bool canMove(int sel, int kill, int row, int col);
    bool canMoveJU(int sel, int kill, int row, int col);
    bool canMoveMA(int sel, int kill, int row, int col);
    bool canMoveXIANG(int sel, int kill, int row, int col);
    bool canMoveSHI(int sel, int kill, int row, int col);
    bool canMoveJIANG(int sel, int kill, int row, int col);
    bool canMovePAO(int sel, int kill, int row, int col);
    bool canMoveZU(int sel, int kill, int row, int col);

    void movePiece(int sel, int kill, int row, int col);
    void doMovePiece(int sel, int row, int col);
    void killPiece(int id);

    //
    void relivePiece(int id);
    void saveStep(int moveid, int killid, int row, int col, QVector<Step*> &steps);
    void doStepBack(Step *step);
    void stepBack();


signals:

};

#endif // BOARD_H
