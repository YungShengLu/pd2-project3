#include "game.h"
#include "candy.h"

Game::Game(int dimension) {
    score = 0;
    board = new Board(dimension);
    restart();
}

Game::~Game() {
    delete board;
}

void Game::restart() {
    board->reset();
    gameOver = false;
    score = 0;
}

void Game::swap(Candy *candy1, Candy *candy2) {
    board->swap(candy1, candy2);
}

void Game::setBoard(Board other) {
    board = new Board(other);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            cout << board->getCandy(i, j)->getCandy() << " ";
        cout << endl;
    }
}

Board* Game::getBoard() const {
    return board;
}

int Game::getScore() const {
    return score;
}
