#include "QCandy.h"

QCandy::QCandy(Candy *candy) {
    this->candy = candy;
    row = candy->getRow();
    col = candy->getCol();
    isPress = false;
    isCandy = true;
}

void QCandy::setType(int cat, int eff) {
    this->cat = cat;
    this->eff = eff;

    switch (cat) {
    case 0:
        color = " ";
        type = " ";
        isCandy = false;
        break;
    case 1:
        color = "red";
        if (eff == 0)
            type = ":/img/Original/Red.png";
        else if (eff == 1)
            type = ":/img/Striped/Striped_red_h.png";
        else if (eff == 2)
            type = ":/img/Striped/Striped_red_v.png";
        else if (eff == 3)
            type = ":/img/Wrapped/Wrapped_red.png";
        break;
    case 2:
        color = "blue";
        if (eff == 0)
            type = ":/img/Original/Blue.png";
        else if (eff == 1)
            type = ":/img/Striped/Striped_blue_h.png";
        else if (eff == 2)
            type = ":/img/Striped/Striped_blue_v.png";
        else if (eff == 3)
            type = ":/img/Wrapped/Wrapped_blue.png";
        break;
    case 3:
        color = "green";
        if (eff == 0)
            type = ":/img/Original/Green.png";
        else if (eff == 1)
            type = ":/img/Striped/Striped_green_h.png";
        else if (eff == 2)
            type = ":/img/Striped/Striped_green_v.png";
        else if (eff == 3)
            type = ":/img/Wrapped/Wrapped_green.png";
        break;
    case 4:
        color = "yellow";
        if (eff == 0)
            type = ":/img/Original/Yellow.png";
        else if (eff == 1)
            type = ":/img/Striped/Striped_yellow_h.png";
        else if (eff == 2)
            type = ":/img/Striped/Striped_yellow_v.png";
        else if (eff == 3)
            type = ":/img/Wrapped/Wrapped_yellow.png";
        break;
    case 5:
        color = "orange";
        if (eff == 0)
            type = ":/img/Original/Orange.png";
        else if (eff == 1)
            type = ":/img/Striped/Striped_orange_h.png";
        else if (eff == 2)
            type = ":/img/Striped/Striped_orange_v.png";
        else if (eff == 3)
            type = ":/img/Wrapped/Wrapped_orange.png";
        break;
    case 6:
        color = "purple";
        if (eff == 0)
            type = ":/img/Original/Purple.png";
        else if (eff == 1)
            type = ":/img/Striped/Striped_purple_h.png";
        else if (eff == 2)
            type = ":/img/Striped/Striped_purple_v.png";
        else if (eff == 3)
            type = ":/img/Wrapped/Wrapped_purple.png";
        break;
    case 7:
        color = "colour";
        type = ":/img/ColourBomb/ColourBomb.png";
        break;
    }

    QPixmap pixImg(type);
    setPixmap(pixImg);
}

int QCandy::getType() {
    return cat;
}

void QCandy::setEffect(int eff) {
    if (eff == 0)
        this->cat = 0;
    this->eff = eff;
}

int QCandy::getEffect() {
    return eff;
}

Candy* QCandy::getCandy() {
    return candy;
}

void QCandy::setCandy(int i, int j) {
    candy = new Candy(i, j);
    row = i;
    col = j;

    if (candy == NULL) {
        cat = 0;
        eff = 0;
        setType(cat, eff);
    }
    else {
        cat = candy->getCandy();
        eff = 0;
        setType(cat, eff);
    }
}

int QCandy::getRow() {
    return row;
}

void QCandy::setRow(int row) {
    this->row = row;
}

int QCandy::getCol() {
    return col;
}

void QCandy::setCol(int col) {
    this->col = col;
}

bool QCandy::getPress() {
    return isPress;
}

void QCandy::setPress(bool isPress) {
    this->isPress = isPress;
}

bool QCandy::getEntity() {
    return isCandy;
}

void QCandy::setEntity(bool isCandy) {
    this->isCandy = isCandy;
}

QString QCandy::getColor() {
    return color;
}

void QCandy::swap(QCandy *candy1, QCandy *candy2) {
    int type = candy1->getType();
    int effect = candy1->getEffect();

    candy1->setEffect(candy2->getEffect());
    candy1->setType(candy2->getType(), candy2->getEffect());

    candy2->setEffect(effect);
    candy2->setType(type, effect);
}

// Events
void QCandy::enterEvent(QEvent *event) {
    setGeometry(this->x(), this->y(), this->width()*1.2, this->height()*1.2);
}

void QCandy::leaveEvent(QEvent *event) {
    setGeometry(this->x(), this->y(), this->width()/1.2, this->height()/1.2);
}

void QCandy::mousePressEvent(QMouseEvent *event) {
    emit clicked();

    if (isPress == false && event->button() == Qt::LeftButton)
        isPress = true;
    else if (isPress == true && event->button() == Qt::LeftButton)
        isPress = false;
}
