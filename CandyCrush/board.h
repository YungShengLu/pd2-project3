#ifndef BOARD
#define BOARD

#include "QHeaderfile.h"
#include "subject.h"

class Candy;

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

class Board : public Subject {
public:
    Board(int dimension);
    Board(const Board &other);
    ~Board();

    void reset();
    void change();
    void swap(Candy *candy1, Candy *candy2);
    void move(Direction dir);
    void judge();
    Candy* getCandy(int i, int j);
    int getDimension() const;
    int getPointsLastRound() const;
    bool isFull() const;
    bool isCrush() const;
    bool isMovePossible() const;

private:
    void initialize();
    void moveHorizontally(int i, int j, Direction dir);
    void moveVertically(int i, int j, Direction dir);
    QVector<Candy*> crush(QVector<Candy*> column);
    void handleCrush();
    void handleNextMove();
    bool isChanged(Board &other) const;

    QVector< QVector<Candy*> > board;
    int dimension;
    int pointsLastRound;
    bool crushLastRound;

};

#endif // BOARD

