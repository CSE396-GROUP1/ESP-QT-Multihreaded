#include "myserver.h"

MyServer::MyServer(QObject *parent):
    QTcpServer(parent)
{
    gameState = Start;
}


void MyServer::startServer(){

    if(!this->listen(QHostAddress::Any,8081)){
        qDebug() << "Could not start server";
    }
    else{
        qDebug() << "Listening...";
    }

}

void MyServer::incomingConnection(qintptr socketDescriptor){

    qDebug() << socketDescriptor << "Connecting...";

    MyThread *thread = new MyThread(socketDescriptor, gameState, this);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}

