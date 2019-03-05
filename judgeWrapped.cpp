#include "judgeWrapped.h"

QVector< QVector<Candy*> > getWrapped(int shape, int type) {
    if (shape < 2) {
        QVector< QVector<Candy*> > wrapped(3, QVector<Candy*>(3));
        if (shape == 0) {
            wrapped[0][1] = wrapped[0][2] = NULL;
            wrapped[1][1] = wrapped[1][2] = NULL;
        }
        else {
            wrapped[1][0] = wrapped[1][2] = NULL;
            wrapped[2][0] = wrapped[2][2] = NULL;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (wrapped[i].at(j) != NULL)
                    wrapped[i].at(j)->setCandy(type);
            }
        }

        return wrapped;
    }
    else {
        QVector< QVector<Candy*> > wrapped(4, QVector<Candy*>(4));
        wrapped[0][0] = wrapped[0][2] = wrapped[0][3] = NULL;
        wrapped[1][0] = wrapped[1][2] = wrapped[1][3] = NULL;
        wrapped[2][0] = wrapped[1][2] = wrapped[2][3] = NULL;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (wrapped[i].at(j) != NULL)
                    wrapped[i].at(j)->setCandy(type);
            }
        }

        return wrapped;
    }
}

QVector< QVector<Candy*> > rotateWrapped(QVector< QVector<Candy*> > wrapped, int shape, int rotate) {
    int bound = (shape < 2) ? 2 : 3;
    QVector< QVector<Candy*> > newWrapped(bound+1, QVector<Candy*> (bound+1));

    switch (rotate) {
    case 0:
        for (int i = 0; i < bound+1; i++) {
            for (int j = 0; j < bound+1; j++)
                newWrapped[i][j] = wrapped[i][j];
        }
        break;
    case 1:
        for (int i = 0; i < bound+1; i++) {
            for (int j = 0; j < bound+1; j++)
                newWrapped[i][j] = wrapped[j][bound-i];
        }
        break;
    case 2:
        for (int i = 0; i < bound+1; i++) {
            for (int j = 0; j < bound+1; j++)
                newWrapped[i][j] = wrapped[bound-i][bound-j];
        }
        break;
    case 3:
        for (int i = 0; i < bound+1; i++) {
            for (int j = 0; j < bound+1; j++)
                newWrapped[i][j] = wrapped[bound-j].at(i);
        }
        break;
    }

    return newWrapped;
}

bool isWrapped(const QVector< QVector<Candy*> > &a, const QVector< QVector<Candy*> > &b, int bound) {
    for (int i = 0; i < bound; i++) {
        for (int j = 0; j < bound; j++) {
            if (a[i].at(j)->getCandy() != b[i].at(j)->getCandy())
                return false;
        }
    }

    return true;
}

void checkLWrapped(QVector< QVector<Candy*> > board, int dimension) {
    QVector< QVector<Candy*> > wrapped(3, QVector<Candy*> (3));
    QVector< QVector<Candy*> > same(3, QVector<Candy*> (3));

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            wrapped = getWrapped(0, board[i][j]->getCandy());

            for (int k = 0; k < 4; k++) {
                wrapped = rotateWrapped(wrapped, 0, k);

                for (int x = i; x < 3; x++) {
                    for (int y = j; y < 3; y++)
                        same[x][y] = board[x].at(y);
                }

                if (isWrapped(same, wrapped, 3)) {
                    for (int x = 0; x < 3; x++) {
                        for (int y = 0; y < 3; y++)
                            same[x].at(y)->setCandy(0);
                    }
                }
            }
        }
    }
}

void checkTWrapped(QVector< QVector<Candy*> > board, int dimension) {
    QVector< QVector<Candy*> > wrapped(3, QVector<Candy*> (3));
    QVector< QVector<Candy*> > same(3, QVector<Candy*> (3));

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            wrapped = getWrapped(1, board[i][j]->getCandy());

            for (int k = 0; k < 4; k++) {
                wrapped = rotateWrapped(wrapped, 1, k);

                for (int x = i; x < 3; x++) {
                    for (int y = j; y < 3; y++)
                        same[x][y] = board[x].at(y);
                }

                if (isWrapped(same, wrapped, 3)) {
                    for (int x = 0; x < 3; x++) {
                        for (int y = 0; y < 3; y++)
                            same[x].at(y)->setCandy(0);
                    }
                }
            }
        }
    }
}

void checkXWrapped(QVector< QVector<Candy*> > board, int dimension) {
    QVector< QVector<Candy*> > wrapped(4, QVector<Candy*> (4));
    QVector< QVector<Candy*> > same(4, QVector<Candy*> (4));

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            wrapped = getWrapped(2, board[i][j]->getCandy());

            for (int k = 0; k < 4; k++) {
                wrapped = rotateWrapped(wrapped, 2, k);

                for (int x = i; x < 4; x++) {
                    for (int y = j; y < 4; y++)
                        same[x][y] = board[x].at(y);
                }

                if (isWrapped(same, wrapped, 4)) {
                    for (int x = 0; x < 4; x++) {
                        for (int y = 0; y < 4; y++)
                            same[x].at(y)->setCandy(0);
                    }
                }
            }
        }
    }
}
