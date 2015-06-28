#ifndef CANDY
#define CANDY

#include "QHeaderfile.h"

class Candy {

public:
    Candy(int i, int j);
    Candy(const Candy &other);
    Candy(int type);

    void setCandy(int type);
    int getCandy();
    void setEffect(int effect);
    int getEffect();
    void setRow(int row);
    int getRow();
    void setCol(int col);
    int getCol();
    void upgrade();
    void setMove(bool isMove);
    bool getMove();

private:
    int row, col, type, effect;
    bool isMove;

};

#endif // CANDY

