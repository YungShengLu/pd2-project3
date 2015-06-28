#ifndef GAME
#define GAME

#include "QHeaderfile.h"
#include "subject.h"
#include "board.h"

class Board;

class Game : public Subject {

public:
    Game(int dimension);
    ~Game();

    void restart();
    void swap(Candy *candy1, Candy *candy2);
    void setBoard(Board other);
    Board* getBoard() const;
    int getScore() const;

private:
    Board *board;
    int score;
    bool gameOver;

};

#endif // GAME

