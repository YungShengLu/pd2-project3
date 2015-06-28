#include "judgeColourBomb.h"

void checkHColour(QVector< QVector<Candy*> > board, int dimension) {
    QVector<Candy*> same;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (same.empty())
                same.push_back(board[i][j]);
            else if (!same.empty()) {
                if (same.size() == 5) {
                    same = checkXColour(board, same);

                    for (int k = 0; k < 5; k++)
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

        if (same.size() == 5) {
            for (int k = 0; k < 5; k++)
                same[k]->setCandy(0);
        }

        same.clear();
    }
}

void checkVColour(QVector< QVector<Candy*> > board, int dimension) {
    QVector<Candy*> same;

    for (int j = 0; j < dimension; j++) {
        for (int i = 0; i < dimension; i++) {
            if (same.empty())
                same.push_back(board[i][j]);
            else if (!same.empty()) {
                if (same.size() == 5) {
                    same = checkXColour(board, same);

                    for (int k = 0; k < 5; k++)
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

        if (same.size() == 5) {
            for (int k = 0; k < 5; k++)
                same[k]->setCandy(0);
        }

        same.clear();
    }
}

QVector<Candy*> checkXColour(QVector< QVector<Candy*> > board, QVector<Candy*> same) {
    Candy *middle = same.at(2);
    int row = middle->getRow();
    int col = middle->getCol();

    if (same.at(0)->getRow() - same.at(1)->getRow() == 0) {
        if (board[row][col+1]->getCandy() == middle->getCandy()) {
            if (board[row][col+2]->getCandy() == middle->getCandy()) {
                same.push_back(board[row][col+1]);
                same.push_back(board[row][col+2]);
            }
        }
        else if (board[row][col-1]->getCandy() == middle->getCandy()) {
            if (board[row][col-2]->getCandy() == middle->getCandy()) {
                same.push_back(board[row][col-1]);
                same.push_back(board[row][col-2]);
            }
        }
    }
    else {
        if (board[row+1][col]->getCandy() == middle->getCandy()) {
            if (board[row+2][col]->getCandy() == middle->getCandy()) {
                same.push_back(board[row+1][col]);
                same.push_back(board[row+2][col]);
            }
        }
        else if (board[row-1][col]->getCandy() == middle->getCandy()) {
            if (board[row-2][col]->getCandy() == middle->getCandy()) {
                same.push_back(board[row-1][col]);
                same.push_back(board[row-2][col]);
            }
        }
    }

    return same;
}
