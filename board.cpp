#include "QHeaderfile.h"
#include "board.h"
#include "candy.h"
#include "judgeLined.h"
#include "judgestriped.h"
#include "judgeWrapped.h"
#include "judgecolourbomb.h"

using namespace std;

Board::Board(int dimension) {
    this->dimension = dimension;
    pointsLastRound = 0;
    crushLastRound = false;

    initialize();
}

Board::Board(const Board &other) {
    dimension = other.dimension;
    initialize();

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (other.board[i][j] == NULL)
                board[i][j] = NULL;
            else
                board[i][j] = new Candy(*(other.board[i][j]));
        }
    }
}

Board::~Board() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++)
            delete board[i][j];
    }
}

void Board::initialize() {
    board.resize(dimension);

    for (int i = 0; i < dimension; i++)
        board[i].resize(dimension);

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++)
            board[i][j] = NULL;
    }
}

void Board::reset() {
    pointsLastRound = 0;
    crushLastRound = false;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            delete board[i][j];
            board[i][j] = new Candy(i, j);
        }
    }
}

void Board::swap(Candy *candy1, Candy *candy2) {
    int type = candy1->getCandy();
    int effect = candy1->getEffect();
    candy1->setCandy(candy2->getCandy());
    candy1->setEffect(candy2->getEffect());
    candy2->setCandy(type);
    candy2->setEffect(effect);
}

Candy* Board::getCandy(int i, int j) {
    return board[i][j];
}

int Board::getDimension() const {
    return dimension;
}

int Board::getPointsLastRound() const {
    return pointsLastRound;
}

void Board::judge() {
    cout << "..." << endl;
    checkHColour(board, dimension);cout << "..." << endl;
    checkVColour(board, dimension);

    checkLWrapped(board, dimension);
    checkTWrapped(board, dimension);
    checkXWrapped(board, dimension);

    checkHStriped(board, dimension);
    checkVStriped(board, dimension);

    checkHLined(board, dimension);
    checkVLined(board, dimension);
}

void Board::move(Direction dir) {
    switch (dir) {
    case UP:
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++)
                moveVertically(i, j, UP);
        }
        break;
    case DOWN:
        for (int i = dimension-1; i >= 0; i--) {
            for (int j = 0; j < dimension; j++)
                moveVertically(i, j, DOWN);
        }
        break;
    case LEFT:
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++)
                moveHorizontally(i, j, LEFT);
        }
        break;
    case RIGHT:
        for (int i = 0; i < dimension; i++) {
            for (int j = dimension-1; j >= 0; j--)
                moveHorizontally(i, j, RIGHT);
        }
        break;
    }

    notifyObs();
}

void Board::handleNextMove() {
    pointsLastRound = 0;
    crushLastRound = false;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (board[i][j] != NULL)
                board[i][j]->setMove(false);
        }
    }
}

bool Board::isMovePossible() const {
    if (isFull()) {
        Board newBoard(*this);

        newBoard.move(UP);
        if (isChanged(newBoard))
            return true;

        newBoard.move(DOWN);
        if (isChanged(newBoard))
            return true;

        newBoard.move(LEFT);
        if (isChanged(newBoard))
            return true;

        newBoard.move(RIGHT);
        if (isChanged(newBoard))
            return true;

        return false;
    }
    else
        return true;
}

void Board::moveHorizontally(int i, int j, Direction dir) {
    if (board[i][j] != NULL) {
        int newj;

        if (dir == RIGHT)
            newj = j + 1;
        else
            newj = j - 1;
    }

    judge();
    handleCrush();
}

void Board::moveVertically(int i, int j, Direction dir) {
    if (board[i][j] != NULL) {
        int newi;

        if (dir == UP)
            newi = i - 1;
        else
            newi = i + 1;
    }

    judge();
    handleCrush();
}

QVector<Candy*> Board::crush(QVector<Candy*> column) {
    QVector<Candy*> temp;

    Candy *zero = new Candy(0);

    for (int i = dimension-1; i >= 0; i--) {
        if (column[i]->getCandy() != 0)
            temp.push_back(column[i]);
    }

    for (int i = temp.size(); i < dimension; i++)
        temp.push_back(zero);

    return temp;
}

void Board::handleCrush() {
    QVector<Candy*> column;

    for (int j = 0; j < dimension; j++) {
        for (int i = 0; i < dimension; i++)
            column.push_back(board[i].at(j));

        column = crush(column);

        for (int i = 0, k = dimension-1; i < dimension && k >= 0; i++, k--)
            board[i][j] = column[k];

        column.clear();
    }
}

bool Board::isChanged(Board &other) const {
    if (dimension != other.dimension)
        return false;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (((board[i][j] == NULL && other.board[i][j] != NULL) ||
                 (board[i][j] != NULL && other.board[i][j] == NULL)) ||
                 ((board[i][j] != NULL && other.board[i][j] != NULL) &&
                  board[i][j]->getCandy() != other.board[i][j]->getCandy()))
                return true;
        }
    }
    return false;
}

bool Board::isFull() const {
    bool full = true;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (board[i][j] == NULL)
                full = false;
        }
    }

    return full;
}
