#ifndef JUDGEWRAPPED
#define JUDGEWRAPPED

#include "QHeaderfile.h"
#include "candy.h"

using namespace std;

QVector< QVector<Candy*> > getWrapped(int shape, int type);
QVector< QVector<Candy*> > rotateWrapped(QVector< QVector<Candy*> > wrapped, int shape, int rotate);
bool isWrapped(const QVector< QVector<Candy*> > &a, const QVector< QVector<Candy*> > &b, int bound);
void checkLWrapped(QVector< QVector<Candy*> > board, int dimension);
void checkTWrapped(QVector< QVector<Candy*> > board, int dimension);
void checkXWrapped(QVector< QVector<Candy*> > board, int dimension);

#endif // JUDGEWRAPPED
