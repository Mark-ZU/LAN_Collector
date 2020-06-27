#include <QCoreApplication>
#include <broadcaster.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BroadCaster _bc;
    return a.exec();
}
