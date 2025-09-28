#ifndef TLISTITEM_H
#define TLISTITEM_H

#include <QListWidgetItem>
#include <QPixmap>
#include <QString>
#include <QStringList>

class TListItem : public QListWidgetItem,public QObject
{
public:
    TListItem(QListWidget *p=0);

    void setSN(QString SN){
        this->SN=SN;
    };

    void setAddress(QString Address){
        this->Address=Address;
    };

    void setInitialPorts(QStringList InitialPorts){
        this->InitialPorts=InitialPorts;
    };

    QString getSN(){
        return this->SN;
    };

    QString getAddress(){
        return this->Address;
    };

    QStringList getInitialPorts(){
        return this->InitialPorts;
    };
    void setSkipConnect(bool skip) { m_skipConnect = skip; }
    bool skipConnect() const { return m_skipConnect; }
private:
    QString SN;
    QString Address;
    QStringList InitialPorts;
    bool m_skipConnect = false;
};

#endif // TLISTITEM_H
