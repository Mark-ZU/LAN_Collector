#ifndef INFOMANAGER_H
#define INFOMANAGER_H
#include <string>

class QUdpSocket;
class InfoManager
{
public:
    InfoManager(const std::string&,const unsigned int);
    ~InfoManager();
    void run();
    void parse(void*,const unsigned int);
private:
    QUdpSocket * socket;
};

#endif // INFOMANAGER_H
