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
    ~Game();

public slots:
    void hide_btn();

    /**
     * @brief main function triggered from timer
     */
    void updateGame();

    /**
     * @brief check if any snake->snakeBlock collides with any fruit
     */
    bool ateFruit(Snake *snk);

    /**
     * @brief close the game
     */
    void endgame();

    /**
     * @brief update graphics
     */
    void draw(QGraphicsScene * sence);

    void updatedir();

    friend void* start_server(void* null);

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
