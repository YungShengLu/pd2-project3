#ifndef JUDGESTRIPED
#define JUDGESTRIPED

#include "QHeaderfile.h"
#include "candy.h"

using namespace std;

void checkHStriped(QVector< QVector<Candy*> > board, int dimension);
void checkVStriped(QVector< QVector<Candy*> > board, int dimension);

#endif // JUDGESTRIPED

