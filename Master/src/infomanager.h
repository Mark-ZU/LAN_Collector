#ifndef INFOMANAGER_H
#define INFOMANAGER_H
#include <string>
namespace std{
class thread;
}
class QUdpSocket;
class InfoManager
{
public:
    InfoManager(const std::string&,const unsigned int);
    ~InfoManager();
    void run();
    void parse(void*,const unsigned int);
    void manualAdd(const unsigned int,const std::string&);
private:
    QUdpSocket * socket;
    std::thread * udpThread;
};
#endif // INFOMANAGER_H
