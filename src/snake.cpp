#include "include/snake.h"

Snake::Snake(int sx, int sy)
{
    snakeBlocks = new int*[650];
    for(int i = 0; i < 650; i++)snakeBlocks[i] = new int[2];
    for(int i = 0; i < 650; i++)snakeBlocks[i][0] = -1;
    for(int i = 0; i < 650; i++)snakeBlocks[i][1] = -1;
    snakeBlocks[0][0] = sx;
    snakeBlocks[0][1] = sy;
    length = 1;
}

void Snake::update(int dir){
    for(int i = 649; i > 0; i--)snakeBlocks[i][1] = snakeBlocks[i-1][1];
    for(int i = 649; i > 0; i--)snakeBlocks[i][0] = snakeBlocks[i-1][0];
    if(dir == 1)snakeBlocks[0][0]++; //right
    if(dir == 2)snakeBlocks[0][0]--; //left
    if(dir == 3)snakeBlocks[0][1]++; //down
    if(dir == 4)snakeBlocks[0][1]--; //up
    if(snakeBlocks[0][0] > 24)snakeBlocks[0][0] = 0;
    if(snakeBlocks[0][0] < 0)snakeBlocks[0][0] = 24;
    if(snakeBlocks[0][1] > 24)snakeBlocks[0][1] = 0;
    if(snakeBlocks[0][1] < 0)snakeBlocks[0][1] = 24;
}

void Snake::incLength(){
    length++;
}

bool Snake::checkCollision(){
    bool coll = false;
    for(int i = 0; i<length; i++){
        for(int j = 0; j < length; j++){
            if(i != j)
            if(snakeBlocks[i][0] == snakeBlocks[j][0] && snakeBlocks[i][1] == snakeBlocks[j][1])coll = true;
        }
    }
    return coll;
}
