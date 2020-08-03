#include "include/tcp.h"
#include "include/game.h"

extern Game *w;

Tcp::Tcp()
{
    sock = new QTcpSocket();
}

void Tcp::send(std::__cxx11::string str)
{
    sock->write(str.c_str());
    qDebug()<<"Writing.. " << str.c_str()  ;
}

void Tcp::connect_game()
{
    sock->connectToHost("127.0.0.1",9999);
    if(sock->waitForConnected(500))
        qDebug()<<"Conneted" ;
    else
        qDebug()<<"Not Conneted .." ;
}

void Tcp::close()
{
    qDebug()<<"Close Connection";
    sock->close();
}

void Tcp::receive()
{
     connect(sock, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Tcp::readyRead()
{
    read = sock->read(1) ;
    qDebug()<<"Recevieing.. " << read;
    if(read == "s") {
        w->player = 1;
        w->start();
    } else if(read == "v") {
        w->start();
    }
}
