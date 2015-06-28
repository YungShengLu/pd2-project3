#include "judgeLined.h"

void checkHLined(QVector< QVector<Candy*> > board, int dimension) {
    QVector<Candy*> same;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (same.empty())
                same.push_back(board[i][j]);
            else if (!same.empty()) {
                if (same.size() == 3) {
                    for (int k = 0; k < 3; k++)
                        same[k]->setCandy(0);
                    same.clear();
                    same.push_back(board[i][j]);
                }
                else if (board[i][j]->getCol() == same.back()->getCol() + 1) {
                    if (board[i][j]->getCandy() == same.back()->getCandy())
                        same.push_back(board[i][j]);
                    else {
                        same.clear();
                        same.push_back(board[i][j]);
                    }
                }
            }
        }

        if (same.size() == 3) {
            for (int k = 0; k < 3; k++)
                same[k]->setCandy(0);
        }

        same.clear();
    }
}

void checkVLined(QVector< QVector<Candy*> > board, int dimension) {
    QVector<Candy*> same;

    for (int j = 0; j < dimension; j++) {
        for (int i = 0; i < dimension; i++) {
            if (same.empty())
                same.push_back(board[i][j]);
            else if (!same.empty()) {
                if (same.size() == 3) {
                    for (int k = 0; k < 3; k++)
                        same[k]->setCandy(0);
                    same.clear();
                    same.push_back(board[i][j]);
                }
                else if (board[i][j]->getCol() == same.back()->getCol() + 1) {
                    if (board[i][j]->getCandy() == same.back()->getCandy())
                        same.push_back(board[i][j]);
                    else {
                        same.clear();
                        same.push_back(board[i][j]);
                    }
                }
            }
        }

        if (same.size() == 3) {
            for (int k = 0; k < 3; k++)
                same[k]->setCandy(0);
        }

        same.clear();
    }
}
