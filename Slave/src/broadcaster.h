#ifndef BROADCASTER_H
#define BROADCASTER_H
#include <QObject>
class QUdpSocket;
class QTimer;
class BroadCaster : public QObject{
    Q_OBJECT
public:
    explicit BroadCaster(QObject *parent = nullptr);
    virtual ~BroadCaster();
public slots:
    void send();
private:
    QUdpSocket* socket;
    QTimer* timer;
};

#endif // BROADCASTER_H
