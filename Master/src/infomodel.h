#ifndef INFOMODEL_H
#define INFOMODEL_H
#include <QAbstractListModel>
#include <QMap>
#include <QString>
#include <iostream>
#include "singleton.hpp"
class InfoModel : public QAbstractListModel{
    Q_OBJECT
public:
    explicit InfoModel(QObject *parent = Q_NULLPTR):QAbstractListModel(parent){
        connect(this,&InfoModel::addNewData,this,&InfoModel::addData);
    }
    virtual ~InfoModel() override{}
    enum Roles {
        Alive_Role = Qt::UserRole + 1,
        Count_Role,
        IP_Role,
        Info_Role
    };
    Q_ENUM(Roles)
    QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> result = QAbstractListModel::roleNames();
        result.insert(Alive_Role, ("mAlive"));
        result.insert(Count_Role, ("mCount"));
        result.insert(IP_Role, ("mIP"));
        result.insert(Info_Role, ("mInfo"));
        return result;
    }
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        return _data.size();
    }
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 3;
    }
    Q_INVOKABLE void checkAlive(){
        for (int i = 0; i < _data.size(); ++i){
//            std::cout << _data[i].ip << ' ' << _data[i].count << std::endl;
            if(_data[i].count < 2){
                _data[i].count = 0;
//                emit dataChanged(createIndex(i,0),createIndex(i,0));
            }
            else
                _data[i].count = 1;
        }
        beginResetModel();
        std::sort(_data.begin(),_data.end(),DeviceData::compareLessThan);
        endResetModel();
    }
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override{
        if(index.isValid()){
            switch(role){
            case Alive_Role:
                return _data[index.row()].count > 0;
            case Count_Role:
                return _data[index.row()].count%2 == 0;
            case IP_Role:
                return _data[index.row()].ip;
            case Info_Role:
                return _data[index.row()].info.c_str();
            }
            return 0;
        }
        return 0;
    }
signals:
    void addNewData(const unsigned int ip,const QString info);
public slots:
    virtual bool addData(const unsigned int ip,const QString info){
        auto index = _data.indexOf(ip);
        if(index != -1){
            _data[index].info = info.toStdString();
            _data[index].count += 1;
            emit dataChanged(createIndex(index,0),createIndex(index,0));
            return true;
        }
        beginResetModel();
        _data.append(DeviceData(ip,info.toStdString()));
        endResetModel();
        return false;
    }
private:
    struct DeviceData{
        DeviceData(const unsigned int ip,const std::string& info=""):ip(ip),count(0),info(info){}
        unsigned int ip;
        unsigned int count;
        std::string info;
        bool operator==(const DeviceData& b) const{
            return this->ip == b.ip;
        }
        bool operator==(const unsigned int ip) const{
            return this->ip == ip;
        }
        static bool compareLessThan(const DeviceData& d1,const DeviceData& d2){
            bool alive1 = (d1.count > 0);
            bool alive2 = (d2.count > 0);
            if (alive1 && !alive2)
                return true;
            if (!alive1 && alive2)
                return false;
            return d1.ip < d2.ip;
        }
    };
    QList<DeviceData> _data;
};
typedef Singleton<InfoModel> SInfoModel;
#endif // INFOMODEL_H
