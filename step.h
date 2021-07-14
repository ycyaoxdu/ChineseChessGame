#ifndef STEP_H
#define STEP_H

#include <QObject>
#include "piece.h"

class Step : public QObject
{
    Q_OBJECT
public:
    explicit Step(QObject *parent = nullptr);

    //var
    int _moveid;
    int _killid;
    Piece::TYPE _type;
    bool _red;

    int _rowFrom;
    int _rowTo;
    int _colFrom;
    int _colTo;

signals:

};

#endif // STEP_H
