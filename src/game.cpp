#include "include/game.h"

#include <QDebug>
#include <sstream>
#include <stdlib.h>
#include <QProcess>
#include <QString>
#include <QByteArray>
void* start_server(void* parent) {
    system("python3 '/mnt/e/Workshops/ROV/Crash Course/Snake/server/server.py'");
}

Game::Game(QWidget *parent)
{
    // init connection
    conn = new Tcp();
    player = 0 ;
    // init direction to right
    pre_dir = 2;
    dir = 1;

    pre_dir2 = 2;
    dir2 = 1;

    // start server
    pthread_t server;
    pthread_create(&server, 0, &start_server,0);

    // set bg
    scene = new QGraphicsScene(0,0,500,500);
    bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/images/background.jpg").scaled(500,500));
    scene->addItem(bg);
    setScene(scene);

    // set button
    btn = new QPushButton();
    btn->setGeometry(QRect(180,220,150,70));
    btn->setText("Start Game");
    QGraphicsProxyWidget *proxy = scene->addWidget(btn);

    // hide btn
    connect(btn, SIGNAL(clicked()), this, SLOT(hide_btn()));

}



void Game::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Right) {
        if(pre_dir != 2 && dir != 1) {
            dir = 1;
            conn->send("1");
            pre_dir = dir;
        }
    }
    else if (event->key() == Qt::Key_Down) {
        if(pre_dir != 4 && dir != 3) {
            dir = 3;
            conn->send("3");
            pre_dir = dir;
        }
    }
    else if (event->key() == Qt::Key_Up) {
        if(pre_dir != 3  && dir != 4) {
            dir = 4;
            conn->send("4");
            pre_dir = dir;
        }
    }
    else if (event->key() == Qt::Key_Left) {
        if(pre_dir != 1 && dir != 2) {
            dir = 2;
            conn->send("2");
            pre_dir = dir;
        }
    }
}

void Game::updatedir()
{

    if(conn->read == "1"){
        if(pre_dir2 != 2 && dir2 != 1) { dir2 = 1; pre_dir2 = dir2;}
    }
    if(conn->read == "2"){
        if(pre_dir2 != 1 && dir2 != 2) {dir2 = 2; pre_dir2 = dir2;}
    }
    if(conn->read == "3"){
        if(pre_dir2 != 4 && dir2 != 3) {dir2 = 3; pre_dir2 = dir2;}
    }
    if(conn->read == "4"){
        if(pre_dir2 != 3 && dir2 != 4) {dir2 = 4; pre_dir2 = dir2;}
    }

}
void Game::start()
{
    fruit = new int[2];

    fruit[0] = rand()% 25;
    fruit[1] = rand()% 25;

    gametimer = new QTimer;
    gametimer->setInterval(300);
    gametimer->start();
    connect(gametimer,SIGNAL(timeout()),this,SLOT(updateGame()));

    snake1 = new Snake(1,1);
    snake2 = new Snake(1,23);
}

Game::~Game()
{
     conn->send("h");
}

void Game::hide_btn() {
    btn->setVisible(false);
    conn->connect_game();
    conn->receive();
        QGraphicsTextItem *text = scene->addText("Wating For Anoter player");
        text->setPos(150, 220);
        QFont font = text->font();
        font.setPointSize(14);
        text->setFont(font);
        qDebug()<< "Wating For Anoter player";
}

void Game::updateGame(){
    updatedir();
    if(player) {
        snake1->update(dir);
        snake2->update(dir2);
    } else {
        snake1->update(dir2);
        snake2->update(dir);
    }
    if(ateFruit(snake1))
        snake1->incLength();
    if(ateFruit(snake2))
        snake2->incLength();
    if(snake1->checkCollision() || snake2->checkCollision())
        endgame();
    draw(scene);
}

bool Game::ateFruit(Snake * snk){
    bool ate = false;
    for(int i = 0; i < snk->length; i++){
        if(snk->snakeBlocks[i][0] == fruit[0] && snk->snakeBlocks[i][1] == fruit[1]){
            ate = true;
            qDebug()<<"Ate Fruit !";
        }
    }
    if(ate){
        fruit[0] = rand()% 25;
        fruit[1] = rand()% 25;
    }
    return ate;
}

void Game::endgame(){
    qDebug()<<"End the game";
    gametimer->stop();
    qDebug()<<"End the game";
    bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/images/background.jpg").scaled(500,500));
    scene->addItem(bg);
    setScene(scene);

    std::ostringstream temp;
    temp << "   Game Over\n    Score_1: " << snake1->length << "\n    Score_2: " << snake2->length ;
    if(snake1->length > snake2->length)
        temp << "\nPlayer_1 is The winner ";
    else
        temp << "\nPlayer_2 is The winner ";

    QGraphicsTextItem *text = scene->addText(temp.str().c_str());
    text->setPos(80, 140);
    QFont font = text->font();
    font.setPointSize(30);
    text->setFont(font);

}

void Game::draw(QGraphicsScene * sence){
//    qDebug()<<"Update graphics\n";
    QPen pen;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    sence->clear();

    // bg
    bg = new QGraphicsPixmapItem();
    bg->setPixmap(QPixmap(":/images/images/background.jpg").scaled(500,500));
    scene->addItem(bg);
    setScene(scene);

    // score
    std::ostringstream temp;
    temp << "Score_1: " << snake1->length <<"\nScore_2: " << snake2->length ;
    QGraphicsTextItem *text = scene->addText(temp.str().c_str());
    text->setPos(380, 20);
    QFont font = text->font();
    font.setPointSize(14);
    text->setFont(font);

    // snake_1
    for(int i = snake1->length; i > 0; i--)
    {
        sence->addRect(snake1->snakeBlocks[i][0]*20, snake1->snakeBlocks[i][1]*20, 20, 20, pen, brush);
//        qDebug()<<snake1->snakeBlocks[i][0]<<"\t";
    }

    // snake_2
    brush.setColor(Qt::gray);
    for(int i = snake2->length; i > 0; i--)
    {
        sence->addRect(snake2->snakeBlocks[i][0]*20, snake2->snakeBlocks[i][1]*20, 20, 20, pen, brush);
//        qDebug()<<snake2->snakeBlocks[i][0]<<"\t";
    }
    // fruit
    brush.setColor(Qt::red);
    sence->addRect(fruit[0]*20, fruit[1]*20, 20, 20, pen, brush);

}


