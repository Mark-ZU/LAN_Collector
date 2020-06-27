#include "infomanager.h"
#include "zsplugin.hpp"
#include "message_slave_device.pb.h"
#include <QUdpSocket>
#include <iostream>
#include <thread>
InfoManager::InfoManager(const std::string& address,const unsigned int port):socket(new QUdpSocket()),udpThread(nullptr){
    if(!(socket->bind(QHostAddress::AnyIPv4,port,QUdpSocket::ShareAddress) &&
        socket->joinMulticastGroup(QHostAddress(QString::fromStdString(address))))){
        std::cerr << "ERROR: socket bind error! " << address << " " << port << std::endl;
        delete socket;
        socket = nullptr;
        return;
    }
    udpThread = new std::thread([=]{run();});
    udpThread->detach();
}
InfoManager::~InfoManager(){
    delete socket;
    delete udpThread;
}
void InfoManager::run(){
    ZSData data;
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "inside run" << std::endl;
        while (socket->state() == QUdpSocket::BoundState && socket->hasPendingDatagrams()) {
            data.resize(socket->pendingDatagramSize());
            socket->readDatagram((char*)data.ptr(),data.size());
            parse(data.ptr(),data.size());
        }
    }
}
void InfoManager::parse(void * ptr,const unsigned int size){
    static ZSMsg::SlaveDeviceMsg packet;
    packet.ParseFromArray(ptr,size);
    std::cout << "packet : " << packet.ShortDebugString();
}
