#ifndef QCANDY
#define QCANDY

#include "QHeaderfile.h"
#include "candy.h"

class Candy;

class QCandy : public QLabel {
    Q_OBJECT

public:
    explicit QCandy(const QPixmap &img);
    QCandy(Candy *candy);

    void setType(int cat, int eff);
    int getType();
    void setEffect(int eff);
    int getEffect();
    Candy* getCandy();
    void setCandy(int i, int j);
    int getRow();
    void setRow(int row);
    int getCol();
    void setCol(int col);
    bool getPress();
    void setPress(bool isPress);
    bool getEntity();
    void setEntity(bool isCandy);
    QString getColor();
    void swap(QCandy *candy1, QCandy *candy2);

    Candy *candy;

signals:
    void clicked();

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QString color, type;
    int row, col, cat, eff;
    bool isPress, isCandy;

};

#endif // QCANDY

