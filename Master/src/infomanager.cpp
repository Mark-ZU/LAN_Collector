#include "infomanager.h"
#include "zsplugin.hpp"
#include "general.pb.h"
#include <QUdpSocket>
#include <iostream>
#include <thread>
InfoManager::InfoManager(const std::string& address,const unsigned int port):socket(new QUdpSocket()){
    if(!(socket->bind(QHostAddress::AnyIPv4,port,QUdpSocket::ShareAddress) &&
        socket->joinMulticastGroup(QHostAddress(QString::fromStdString(address))))){
        std::cerr << "ERROR: socket bind error! " << address << " " << port << std::endl;
        delete socket;
        socket = nullptr;
        return;
    }
}
InfoManager::~InfoManager(){
    delete socket;
}
void InfoManager::run(){
    ZSData data;
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (socket->state() == QUdpSocket::BoundState && socket->hasPendingDatagrams()) {
            data.resize(socket->pendingDatagramSize());
            socket->readDatagram((char*)data.ptr(),data.size());
            parse(data.ptr(),data.size());
        }
    }
}
void InfoManager::parse(void * ptr,const unsigned int size){
    static GeneralMsg::JSON packet;
    packet.ParseFromArray(ptr,size);
//    std::cout << "packet : " <<
}
