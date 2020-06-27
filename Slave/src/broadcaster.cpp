#include "broadcaster.h"
#include <QUdpSocket>
#include <QTimer>
#include <QNetworkInterface>
#include <QByteArray>
#include "message_slave_device.pb.h"
BroadCaster::BroadCaster(QObject *parent) : QObject(parent),socket(new QUdpSocket()),timer(new QTimer(this)){
    connect(timer,SIGNAL(timeout()),this,SLOT(send()));
    timer->start(1000);
}
BroadCaster::~BroadCaster(){
    delete timer;
    delete socket;
}
void BroadCaster::send(){
    QStringList ipList;
    QByteArray buffer;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){
             ipList << address.toString();
        }
    }
    if(ipList.size()<=0)
        return;

    ZSMsg::SlaveDeviceMsg msg;
    unsigned int ip = ipList[0].split('.',QString::SkipEmptyParts).last().toUInt();
    msg.set_ip(ip);
    auto info = msg.mutable_info();
    auto ipField = info->add_field();
    ipField->set_key("ip");
    auto value = ipField->mutable_value();
    value->set_type(Value_Type_STRING);
    value->set_v_string(ipList.join("/").toStdString());
    int size = msg.ByteSize();
    buffer.resize(size);
    msg.SerializeToArray(buffer.data(),size);
    socket->writeDatagram(buffer.data(),buffer.size(),QHostAddress("233.233.233.233"), 23233);
    qDebug() << "debug : " << QString::fromStdString(msg.ShortDebugString());
}
