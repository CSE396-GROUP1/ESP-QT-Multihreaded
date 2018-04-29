#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include "mythread.h"
#include "game_state.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer();

    GAME_STATE gameState;
signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // MYSERVER_H
