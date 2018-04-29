#include "mythread.h"

MyThread::MyThread(int ID, GAME_STATE &gameState, QObject *parent) : QThread(parent) , socketDesriptor(ID)
{
    this->gameState = &gameState;
    this->socketDesriptor = ID;
    this->playerState = Start;
}

void MyThread::run()
{
    qDebug() << socketDesriptor <<  " Starting thread";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDesriptor))
    {
        emit socket->error(); // emit error(socket->error);
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socketDesriptor <<  " Client connected ";

    exec();
}


void MyThread::readyRead()
{
    QByteArray data;
    mutex.lock();
    if(*gameState == Start && playerState == Start){
        data = "0";
    }
    mutex.unlock();

    data.append(socket->readAll());

    qDebug() << socketDesriptor << "Data in : " << data;

    socket->write(data);
}

void MyThread::disconnected()
{
    qDebug() << socketDesriptor <<  " Client disconnected ";
    socket->deleteLater();
    exit(0);
}
