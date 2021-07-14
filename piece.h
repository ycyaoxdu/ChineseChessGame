#ifndef PIECE_H
#define PIECE_H

#include <QString>

class Piece
{
public:
    Piece();

    //
    enum TYPE {
        JU, MA, XIANG, SHI, JIANG, PAO, ZU
    };

    //var
    int _id = -1;
    TYPE _type;
    int _row = -1;
    int _col = -1;
    bool _red = false;
    bool _dead = false;

    struct {
        int r, c;
        TYPE t;
    } pos[16] = {
    {0, 0, JU},
    {0, 1, MA},
    {0, 2, XIANG},
    {0, 3, SHI},
    {0, 4, JIANG},
    {0, 5, SHI},
    {0, 6, XIANG},
    {0, 7, MA},
    {0, 8, JU},

    {2, 1, PAO},
    {2, 7, PAO},

    {3, 0, ZU},
    {3, 2, ZU},
    {3, 4, ZU},
    {3, 6, ZU},
    {3, 8, ZU},

    };

    //
    QString name();
    void init(int id);

    void rotate();

};

#endif // PIECE_H
