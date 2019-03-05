#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QHeaderfile.h"
#include "observer.h"
#include "game.h"
#include "board.h"
#include "QCandy.h"
#include "candy.h"

namespace Ui {
class MainWindow;
}

class Game;
class QCandy;

class MainWindow : public QMainWindow, public Observer {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void notify();
    void setTime();
    bool detect();
    void swap(QCandy *candy1, QCandy *candy2);
    bool isCrush(int row, int col);
    void eliminate(int row, int col);

    QVector<QCandy*> fall(QVector<QCandy*> column);
    void handleFall();

    // Animation
    void ruleAnimation();
    void endAnimation();
    void gameAnimation();
    void swapAnimation1(QCandy *candy1, QCandy *candy2);
    void swapAnimation2(QCandy *candy1, QCandy *candy2);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
    void setBoard();

    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playList;
    Game *game;
    QTimer *timer;
    QTime *time;
    QString currTime;
    QVector< QVector<QCandy*> > qBoard;
    QVector<QCandy*> select;

    int minute, second;
    int score;
    int top[10];

private slots:
    void showTime();
    void pauseGame();
    void resumeGame();
    void resetGame();
    void exitGame();

signals:
    void clicked();

};

#endif // MAINWINDOW_H
