#ifndef TCP_H
#define TCP_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QByteArray>
#include <string>

class Tcp : public QObject
{
    Q_OBJECT
public:
    Tcp();
    void send(std::string str);
    void connect_game();
    void close();
    void receive();
    QByteArray read;
   public slots:
       void readyRead();
   private:
       QTcpSocket * sock;

};

#endif // TCP_H
