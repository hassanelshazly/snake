#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>

class Snake {
public:
    Snake(int sx, int sy);
    void update(int dir);
    void incLength();
    bool checkCollision();

    int length;
    int **snakeBlocks;
};

#endif SNAKE_H
