#include "candy.h"

Candy::Candy(int i, int j) {
    type = rand() % 6 + 1;
    row = i;
    col = j;
    effect = 0;
    isMove = false;
}

Candy::Candy(const Candy &other) {
    this->type = other.type;
}

Candy::Candy(int type) {
    this->type = type;
}

void Candy::setCandy(int type) {
    this->type = type;
}

int Candy::getCandy() {
    return type;
}

void Candy::setEffect(int effect) {
    this->effect = effect;
}

int Candy::getEffect() {
    return effect;
}

void Candy::setRow(int row) {
    this->row = row;
}

int Candy::getRow() {
    return row;
}

void Candy::setCol(int col) {
    this->col = col;
}

int Candy::getCol() {
    return col;
}

void Candy::upgrade() {
    // upgrade
}

void Candy::setMove(bool isMove) {
    this->isMove = isMove;
}

bool Candy::getMove() {
    return isMove;
}

