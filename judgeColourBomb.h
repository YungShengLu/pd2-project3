#ifndef JUDGECOLOURBOMB
#define JUDGECOLOURBOMB

#include "QHeaderfile.h"
#include "candy.h"

using namespace std;

void checkHColour(QVector< QVector<Candy*> > board, int dimension);
void checkVColour(QVector< QVector<Candy*> > board, int dimension);
QVector<Candy*> checkXColour(QVector< QVector<Candy*>> board, QVector<Candy*> same);

#endif // JUDGECOLOURBOMB

