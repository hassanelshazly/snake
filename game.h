#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "tcp.h"
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QTimer>
#include <QDebug>

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void start();
    QGraphicsScene* scene;
    int player;

public slots:
    void hide_btn();
    void updateGame(); //main function triggered from timer
    bool ateFruit(Snake *snk); //check if any snake->snakeBlock collides with any fruit
    void endgame(); //close the game
    void draw(QGraphicsScene * sence); //update graphics
    void updatedir();

private:
    int pre_dir;
    int dir;
    int pre_dir2;
    int dir2;
    QPushButton *btn;
    Snake *snake1;
    Snake *snake2;
    QTimer *gametimer;
    int *fruit;
    QGraphicsPixmapItem *bg;
    Tcp *conn;
};

#endif // GAME_H
