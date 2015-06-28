#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    playList = new QMediaPlaylist;
    playList->addMedia(QUrl("qrc:/Sound/Main1.mp3"));
    playList->addMedia(QUrl("qrc:/Sound/Main2.mp3"));
    playList->setCurrentIndex(1);
    playList->setPlaybackMode(QMediaPlaylist::Loop);

    player = new QMediaPlayer();
    player->setPlaylist(playList);
    player->setVolume(200);
    player->play();

    game = new Game(10);
    game->registerObs(this);

    score = 0;
    ui->record2->setText(QString::number(score));

    ruleAnimation();

    qBoard.resize(game->getBoard()->getDimension());
    for (int i = 0; i < game->getBoard()->getDimension(); i++)
        qBoard[i].resize(game->getBoard()->getDimension());

    for (int i = 0; i < game->getBoard()->getDimension(); i++) {
        for (int j = 0; j < game->getBoard()->getDimension(); j++)
            qBoard[i][j] = NULL;
    }

    setBoard();
    gameAnimation();

    // Points
    ui->record2->setText("0");

    // Timer
    setTime();

    connect(ui->button1, SIGNAL(clicked(bool)), this, SLOT(pauseGame()));
    connect(ui->button2, SIGNAL(clicked(bool)), this, SLOT(resetGame()));
    connect(ui->button3, SIGNAL(clicked(bool)), this, SLOT(exitGame()));
}

void MainWindow::notify() {
    // Define gameOver and window.

    // Define winning and window.
    setBoard();
}

void MainWindow::setBoard() {
    while (1) {
        for (int i = 0; i < game->getBoard()->getDimension(); i++) {
            for (int j = 0; j < game->getBoard()->getDimension(); j++) {
                delete qBoard[i][j];
                qBoard[i][j] = new QCandy(game->getBoard()->getCandy(i, j));
                qBoard[i][j]->setCandy(i, j);
            }
        }

        bool isShuffle = detect();
        if (!isShuffle)
            break;
    }

    for (int i = 0; i < game->getBoard()->getDimension(); i++) {
        for (int j = 0; j < game->getBoard()->getDimension(); j++) {
            qBoard[i][j]->installEventFilter(this);
            qBoard[i][j]->setFixedSize(70, 70);
            ui->gridLayout->addWidget(qBoard[i][j], i, j, 1, 1);
        }
    }
}

bool MainWindow::detect() {
    int count = 1;

    for (int i = 0; i < game->getBoard()->getDimension(); i++) {
        count = 1;
        int cursor = qBoard[i][0]->getType();

        for (int j = 1; j < game->getBoard()->getDimension(); j++) {
            if (cursor == qBoard[i][j]->getType())
                count++;
            else {
                count = 1;
                cursor = qBoard[i][j]->getType();
            }

            if (count == 3)
                return true;
        }
    }


    for (int i = 0; i < game->getBoard()->getDimension(); i++) {
        count = 1;
        int cursor = qBoard[0][i]->getType();

        for (int j = 1; j < game->getBoard()->getDimension(); j++) {
            if (cursor == qBoard[j][i]->getType())
                count++;
            else {
                count = 1;
                cursor = qBoard[j][i]->getType();
            }

            if (count == 3)
                return true;
        }
    }

    return false;
}

void MainWindow::swap(QCandy *candy1, QCandy *candy2) {
    int r1 = candy1->getRow(), c1 = candy1->getCol();
    int r2 = candy2->getRow(), c2 = candy2->getCol();
    int t1 = candy1->getType(), e1 = candy1->getEffect();
    int t2 = candy2->getType(), e2 = candy2->getEffect();

    //cout << "c1: " << candy1->getType() << " " << candy1->getEffect() << endl;
    //cout << "c2: " << candy2->getType() << " " << candy2->getEffect() << endl;

    game->swap(candy2->getCandy(), candy1->getCandy());
    candy2->setType(t1, e1);
    candy2->setRow(r2);
    candy2->setCol(c2);

    candy1->setType(t2, e2);
    candy1->setRow(r1);
    candy1->setCol(c1);

    //cout << "c1: " << candy1->getType() << " " << candy1->getEffect() << endl;
    //cout << "c2: " << candy2->getType() << " " << candy2->getEffect() << endl;

    bool flag1 = isCrush(candy1->getRow(), candy1->getCol());
    bool flag2 = isCrush(candy2->getRow(), candy2->getCol());

    if (flag1 == false && flag2 == false) {
        swapAnimation2(candy1, candy2);

        game->swap(candy2->getCandy(), candy1->getCandy());
        candy1->setType(t1, e1);
        candy1->setRow(r1);
        candy1->setCol(c1);

        candy2->setType(t2, e2);
        candy2->setRow(r2);
        candy2->setCol(c2);
    }
}

bool MainWindow::isCrush(int x, int y) {
    int color = qBoard[x][y]->getType();
    int countRow = 1, countCol = 1;

    for (int i = 0; i < 2; i++) {
        if (y - (i+1) >= 0) {
            if (qBoard[x][y-(i+1)]->getType() == color)
                countRow++;
            else
                break;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (y + (i+1) < 10) {
            if (qBoard[x][y+(i+1)]->getType() == color)
                countRow++;
            else
                break;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (x - (i+1) >= 0) {
            if(qBoard[x-(i+1)][y]->getType() == color)
                countCol++;
            else
                break;
        }
    }

    for (int i = 0; i < 2; i++) {
        if (x + (i+1) < 10) {
            if (qBoard[x+(i+1)][y]->getType() == color)
                countCol++;
            else
                break;
        }
    }

    if (countRow == 5 || countCol == 5) {
        qBoard[x][y]->setType(7, 0);

        for (int i = 0; i < 2; i++) {
            if (y - (i+1) >= 0) {
                if (qBoard[x][y-(i+1)]->getType() == color)
                    eliminate(x, y-(i+1));
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (y + (i+1) < 10) {
                if (qBoard[x][y+(i+1)]->getType() == color)
                    eliminate(x, y+(i+1));
                else
                    break;
            }
        }


        for (int i = 0; i < 2; i++) {
            if (x - (i+1) >= 0) {
                if (qBoard[x-(i+1)][y]->getType() == color)
                    eliminate(x-(i+1), y);
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (x + (i+1) < 10) {
                if (qBoard[x+(i+1)][y]->getType() == color)
                    eliminate(x+(i+1), y);
                else
                    break;
            }
        }

        return true;
    }
    else if (countRow >= 3 && countCol >= 3) {
        qBoard[x][y]->setEffect(3);
        qBoard[x][y]->setType(color, 3);

        for (int i = 0; i < 2; i++) {
            if (y - (i+1) >= 0) {
                if (qBoard[x][y-(i+1)]->getType() == color)
                    eliminate(x, y-(i+1));
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (y + (i+1) < 10) {
                if (qBoard[x][y+(i+1)]->getType() == color)
                    eliminate(x, y+(i+1));
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (x - (i+1) >= 0) {
                if (qBoard[x-(i+1)][y]->getType() == color)
                    eliminate(x-(i+1), y);
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (x + (i+1) < 10) {
                if (qBoard[x+(i+1)][y]->getType() == color)
                    eliminate(x+(i+1), y);
                else
                    break;
            }
        }

        return true;
    }
    else if (countRow == 4) {
        qBoard[x][y]->setEffect(2);
        qBoard[x][y]->setType(color, 2);

        for (int i = 0; i < 2; i++) {
            if (y - (i+1) >= 0) {
                if (qBoard[x][y-(i+1)]->getType() == color)
                    eliminate(x, y-(i+1));
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (y + (i+1) < 10) {
                if (qBoard[x][y+(i+1)]->getType() == color)
                    eliminate(x, y+(i+1));
                else
                    break;
            }
        }

        return true;
    }
    else if (countCol == 4) {
        qBoard[x][y]->setEffect(1);
        qBoard[x][y]->setType(color, 1);

        for (int i = 0; i < 2; i++) {
            if (x - (i+1) >= 0) {
                if (qBoard[x-(i+1)][y]->getType() == color)
                    eliminate(x-(i+1),y);
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (x + (i+1) < 10) {
                if (qBoard[x+(i+1)][y]->getType() == color)
                    eliminate(x+(i+1), y);
                else
                    break;
            }
        }

        return true;
    }
    else if (countRow == 3) {
        eliminate(x, y);

        for (int i = 0; i < 2; i++) {
            if (y - (i+1) >= 0) {
                if (qBoard[x][y-(i+1)]->getType() == color)
                    eliminate(x,y-(i+1));
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (y + (i+1) < 10) {
                if (qBoard[x][y+(i+1)]->getType() == color)
                    eliminate(x, y+(i+1));
                else
                    break;
            }
        }

        return true;
    }
    else if (countCol == 3) {
        eliminate(x, y);

        for (int i = 0; i < 2; i++) {
            if (x - (i+1) >= 0) {
                if(qBoard[x-(i+1)][y]->getType() == color)
                    eliminate(x-(i+1), y);
                else
                    break;
            }
        }

        for (int i = 0; i < 2; i++) {
            if (x + (i+1) < 10) {
                if (qBoard[x+(i+1)][y]->getType() == color)
                    eliminate(x+(i+1), y);
                else
                    break;
            }
        }

        return true;
    }
    else
        return false;
}

void MainWindow::eliminate(int x, int y) {
    qBoard[x][y]->setType(0, 0);

    if (qBoard[x][y]->getEffect() == 1) {
        for (int i = 0; i < game->getBoard()->getDimension(); i++) {
            if (i != y) {
                eliminate(x, i);
                qBoard[x][y]->setEffect(0);
            }
        }


        score += 60;
        ui->record2->setText(QString::number(score));
    }
    else if (qBoard[x][y]->getEffect() == 2) {
        for (int i = 0; i < game->getBoard()->getDimension(); i++) {
            if (i != x) {
                eliminate(i, y);
                qBoard[x][y]->setEffect(0);
            }
        }

        score += 60;
        ui->record2->setText(QString::number(score));
    }
    else if (qBoard[x][y]->getEffect() == 3) {
        if (x-1 >= 0 && y-1 >= 0)
            eliminate(x-1, y-1);
        if (x-1 >= 0)
            eliminate(x-1, y);

        if (x-1 >= 0 && y+1 <= game->getBoard()->getDimension()-1)
            eliminate(x-1, y+1);
        if (y-1 >= 0)
            eliminate(x, y-1);
        if (y+1 <= game->getBoard()->getDimension()-1)
            eliminate(x, y+1);

        if (x+1 <= game->getBoard()->getDimension()-1 && y-1 >= 0)
            eliminate(x+1, y-1);
        if (x+1 <= game->getBoard()->getDimension()-1)
            eliminate(x+1, y);
        if (x+1 <= game->getBoard()->getDimension()-1 && y+1 <= game->getBoard()->getDimension()-1)
            eliminate(x+1, y+1);

        qBoard[x][y]->setEffect(0);

        score += 120;
        ui->record2->setText(QString::number(score));
    }

    score += 30;
    ui->record2->setText(QString::number(score));
}

QVector<QCandy*> MainWindow::fall(QVector<QCandy*> column) {
    QVector<QCandy*> temp;

    for (int i = game->getBoard()->getDimension()-1; i >= 0; i--) {
        if (column[i]->getType() != 0)
            temp.push_back(column[i]);
    }

    for (int i = temp.size(); i < game->getBoard()->getDimension(); i++) {
        Candy *candy = new Candy(0);
        QCandy *empty = new QCandy(candy);
        empty->setType(rand() % 6 + 1, 0);
        temp.push_back(empty);
    }

    return temp;
}

void MainWindow::handleFall() {
    QVector<QCandy*> before;
    QVector<QCandy*> after;

    for (int j = 0; j < game->getBoard()->getDimension(); j++) {
        for (int i = 0; i < game->getBoard()->getDimension(); i++)
            before.push_back(qBoard[i][j]);

        after = fall(before);

        for (int i = game->getBoard()->getDimension()-1, k = 0; i >= 0 && k < 10; i--, k++)
            qBoard[i][j]->setType(after[k]->getType(), after[k]->getEffect());

        before.clear();
    }

    for (int x = 0; x < game->getBoard()->getDimension(); x++) {
        for (int y = 0; y < game->getBoard()->getDimension(); y++)
            isCrush(x, y);
    }

    for (int i = 0; i < game->getBoard()->getDimension(); i++) {
        for (int j = 0; j < game->getBoard()->getDimension(); j++) {
            if (qBoard[i][j]->getType() == 0) {
                handleFall();
            }
        }
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    QCandy *candy = qobject_cast<QCandy*>(watched);

    QGraphicsDropShadowEffect *DSE = new QGraphicsDropShadowEffect();
    DSE->setBlurRadius(50);
    DSE->setOffset(-1);
    DSE->setColor(candy->getColor());

    if (candy && event->type() == QEvent::MouseButtonPress) {
        if (select.isEmpty()) {
            candy->setGraphicsEffect(DSE);
            select.push_back(candy);
        }
        else if (select[0]->getRow() == candy->getRow()) {
            if (select[0]->getCol() == candy->getCol()) {
                select[0]->setGraphicsEffect(NULL);
                select[0]->setPress(false);
                select.clear();
            }
            else if (abs(select[0]->getCol() - candy->getCol()) == 1) {
                select.push_back(candy);

                swapAnimation1(select[1], select[0]);

                select[0]->setGraphicsEffect(NULL);
                select[0]->setPress(false);
                select[1]->setGraphicsEffect(NULL);
                select[1]->setPress(false);

                swap(select[0], select[1]);

                if (select[0]->getType() != 7 && select[1]->getType() == 7) {
                    int type = select[0]->getType();

                    eliminate(select[1]->getRow(), select[1]->getCol());
                    for (int i = 0; i < game->getBoard()->getDimension(); i++) {
                        for (int j = 0; j < game->getBoard()->getDimension(); j++) {
                            if (qBoard[i][j]->getType() == type)
                                eliminate(i, j);
                        }
                    }

                    score += 300;
                }
                else if (select[0]->getType() == 7 && select[1]->getType() != 7) {
                    int type = select[1]->getType();

                    eliminate(select[0]->getRow(), select[0]->getCol());
                    for (int i = 0; i < game->getBoard()->getDimension(); i++) {
                        for (int j = 0; j < game->getBoard()->getDimension(); j++) {
                            if (qBoard[i][j]->getType() == type)
                                eliminate(i, j);
                        }
                    }

                    score += 300;
                }

                select.clear();
            }

            handleFall();
        }
        else if (select[0]->getCol() == candy->getCol() && abs(select[0]->getRow() - candy->getRow()) == 1) {
            select.push_back(candy);

            swapAnimation1(select[1], select[0]);

            select[0]->setGraphicsEffect(NULL);
            select[0]->setPress(false);
            select[1]->setGraphicsEffect(NULL);
            select[1]->setPress(false);

            swap(select[0], select[1]);

            if (select[0]->getType() != 7 && select[1]->getType() == 7) {
                int type = select[0]->getType();

                eliminate(select[1]->getRow(), select[1]->getCol());
                for (int i = 0; i < game->getBoard()->getDimension(); i++) {
                    for (int j = 0; j < game->getBoard()->getDimension(); j++) {
                        if (qBoard[i][j]->getType() == type)
                            eliminate(i, j);
                    }
                }

                score +=  300;
                ui->record2->setText(QString::number(score));
            }
            else if (select[0]->getType() == 7 && select[1]->getType() != 7) {
                int type = select[1]->getType();

                eliminate(select[0]->getRow(), select[0]->getCol());
                for (int i = 0; i < game->getBoard()->getDimension(); i++) {
                    for (int j = 0; j < game->getBoard()->getDimension(); j++) {
                        if (qBoard[i][j]->getType() == type)
                            eliminate(i, j);
                    }
                }

                score += 300;
                ui->record2->setText(QString::number(score));
            }

            select.clear();

            handleFall();
        }
        else {
            select[0]->setGraphicsEffect(NULL);
            select[0]->setPress(false);
            select.clear();

            candy->setGraphicsEffect(DSE);
            select.push_back(candy);
        }
    }

    return QObject::eventFilter(watched, event);
}

void MainWindow::setTime() {
    timer = new QTimer(this);
    time = new QTime(0, 0, 3);

    currTime = time->toString("mm : ss");
    ui->record3->setText(currTime);

    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
}

// Animation
void MainWindow::ruleAnimation() {
    QPoint p1(10, 900), p2(10, 290), p3(10, 310);

    QPropertyAnimation *s1 = new QPropertyAnimation(ui->widget, "pos");
    s1->setDuration(500);
    s1->setStartValue(p1);
    s1->setEndValue(p2);

    QPropertyAnimation *s2 = new QPropertyAnimation(ui->widget, "pos");
    s2->setDuration(250);
    s2->setStartValue(p2);
    s2->setEndValue(p3);

    QPropertyAnimation *s3 = new QPropertyAnimation(ui->widget, "pos");
    s3->setDuration(500);
    s3->setStartValue(p3);
    s3->setEndValue(p1);

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    group->addAnimation(s1);
    group->addAnimation(s2);
    group->addPause(1000);
    group->addAnimation(s3);
    group->start();
}

void MainWindow::endAnimation() {
    QPoint p1(10, 900), p2(10, 290), p3(10, 310);

    QPropertyAnimation *s1 = new QPropertyAnimation(ui->widget, "pos");
    s1->setDuration(500);
    s1->setStartValue(p1);
    s1->setEndValue(p2);

    QPropertyAnimation *s2 = new QPropertyAnimation(ui->widget, "pos");
    s2->setDuration(250);
    s2->setStartValue(p2);
    s2->setEndValue(p3);

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    group->addAnimation(s1);
    group->addAnimation(s2);
    group->start();
}

void MainWindow::gameAnimation() {
    QPoint p1(950, 20), p2(150, 20), p3(190, 20);

    QPropertyAnimation *s1 = new QPropertyAnimation(ui->QBoard, "pos");
    s1->setDuration(600);
    s1->setStartValue(p1);
    s1->setEndValue(p2);

    QPropertyAnimation *s2 = new QPropertyAnimation(ui->QBoard, "pos");
    s2->setDuration(250);
    s2->setStartValue(p2);
    s2->setEndValue(p3);

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    group->addAnimation(s1);
    group->addAnimation(s2);
    group->start();
}

void MainWindow::swapAnimation1(QCandy *candy1, QCandy *candy2) {
    QPoint p1(candy2->x(), candy2->y());
    QPoint p2(candy1->x(), candy1->y());

    QPropertyAnimation *s1 = new QPropertyAnimation(candy1, "pos");
    s1->setDuration(50);
    s1->setStartValue(p1);
    s1->setEndValue(p2);

    QPropertyAnimation *s2 = new QPropertyAnimation(candy2, "pos");
    s2->setDuration(50);
    s2->setStartValue(p2);
    s2->setEndValue(p1);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(s1);
    group->addAnimation(s2);
    group->start();
}

void MainWindow::swapAnimation2(QCandy *candy1, QCandy *candy2) {
    QPoint p1(candy1->x(), candy1->y());
    QPoint p2(candy2->x(), candy2->y());

    QPropertyAnimation *s1 = new QPropertyAnimation(candy1, "pos");
    s1->setDuration(50);
    s1->setStartValue(p1);
    s1->setEndValue(p2);

    QPropertyAnimation *s2 = new QPropertyAnimation(candy2, "pos");
    s2->setDuration(50);
    s2->setStartValue(p2);
    s2->setEndValue(p1);

    QPropertyAnimation *s3 = new QPropertyAnimation(candy1, "pos");
    s3->setDuration(50);
    s3->setStartValue(p2);
    s3->setEndValue(p1);

    QPropertyAnimation *s4 = new QPropertyAnimation(candy2, "pos");
    s4->setDuration(50);
    s4->setStartValue(p1);
    s4->setEndValue(p2);

    QParallelAnimationGroup *group1 = new QParallelAnimationGroup;
    group1->addAnimation(s1);
    group1->addAnimation(s2);

    QParallelAnimationGroup *group2 = new QParallelAnimationGroup;
    group2->addAnimation(s3);
    group2->addAnimation(s4);

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    group->addAnimation(group1);
    group->addAnimation(group2);

    group->start();
}

// SLOTS
void MainWindow::showTime() {
    currTime = time->toString("mm : ss");

    time->setHMS(0, time->addSecs(-1).minute(), time->addSecs(-1).second());
    if ((time->second() % 2) == 0)
        currTime[3] = ' ';

    ui->record3->setText(currTime);

    if (time->minute() == 0 && time->second() <= 10) {
        if (time->second() % 2 == 0)
            ui->record3->setStyleSheet("QLabel { \
                                            border-radius: 5px; \
                                            border-width: 4px; \
                                            border-color: beige; \
                                            background-color: rgb(127, 255, 189); \
                                            color: red; \
                                            font-size: 20px; \
                                        }");
        else
            ui->record3->setStyleSheet("QLabel { \
                                            border-radius: 5px; \
                                            border-width: 4px; \
                                            border-color: beige; \
                                            background-color: rgb(127, 255, 189); \
                                            color: black; \
                                            font-size: 20px; \
                                        }");
    }

    if (time->minute() == 59 && time->second() == 59) {
        timer->stop();
        if (score < 10000) {
            player->stop();
            ui->QBoard->setWindowOpacity(1);
            ui->QOption->setWindowOpacity(1);
            ui->QLevel->setWindowOpacity(1);
            ui->QPoints->setWindowOpacity(1);
            ui->button1->setMouseTracking(false);
            ui->button2->setMouseTracking(false);
            ui->button3->setMouseTracking(false);

            ui->label_2->setText("Failed");
            ui->label_3->setText(QString("POINTS: %1").arg(score));

            playList = new QMediaPlaylist;
            playList->addMedia(QUrl("qrc:/Sound/Fail.mp3"));
            playList->setCurrentIndex(1);
            playList->setPlaybackMode(QMediaPlaylist::Loop);

            player->setPlaylist(playList);
            player->setVolume(200);
            player->play();
        }
        else {
            player->stop();

            ui->QBoard->setWindowOpacity(1);
            ui->QOption->setWindowOpacity(1);
            ui->QLevel->setWindowOpacity(1);
            ui->QPoints->setWindowOpacity(1);
            ui->button1->setMouseTracking(false);
            ui->button2->setMouseTracking(false);
            ui->button3->setMouseTracking(false);

            ui->label_2->setText("Candy Crush!");
            ui->label_3->setText(QString("POINTS: %1").arg(score));

            playList = new QMediaPlaylist;
            playList->addMedia(QUrl("qrc:/Sound/Victory.mp3"));
            playList->setCurrentIndex(1);
            playList->setPlaybackMode(QMediaPlaylist::Loop);

            player->setPlaylist(playList);
            player->setVolume(200);
            player->play();
        }

        endAnimation();
    }
}

void MainWindow::pauseGame() {
    timer->stop();
    player->stop();
    ui->button1->setText("Resume");
    connect(ui->button1, SIGNAL(clicked(bool)), this, SLOT(resumeGame()));
}

void MainWindow::resumeGame() {
    timer->start();
    player->play();
    ui->button1->setText("Pause");
    connect(ui->button1, SIGNAL(clicked(bool)), this, SLOT(pauseGame()));
}

void MainWindow::resetGame() {
    delete timer, time;

    ui->record2->setText("0");
    setTime();

    game->restart();
    setBoard();
}

void MainWindow::exitGame() {
    close();
}

MainWindow::~MainWindow() {
    delete ui;
}
