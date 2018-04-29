#ifndef MyTHREAD_H
#define MyTHREAD_H

#include <QDebug>
#include <QThread>
#include <QTcpSocket>
#include <QObject>
#include <QMutex>

#include "game_state.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int ID, GAME_STATE &gameState, QObject *parent = 0);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    int socketDesriptor;

    GAME_STATE* gameState;
    GAME_STATE  playerState;

    QMutex mutex;
};

#endif // MyTHREAD_H
