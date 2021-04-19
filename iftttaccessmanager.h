#ifndef IFTTTACCESSMANAGER_H
#define IFTTTACCESSMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
//class QNetworkAccessManager;
//class QNetworkReply;

class IftttAccessManager : public QObject
{
    Q_OBJECT

public:
    IftttAccessManager(QObject *parent = nullptr);
    void requestPost();
signals:
    void postFinished(const QString &result);
protected:
    virtual QString value1();
    virtual QString value2();
    virtual QString value3();
    QString webhooksKey = "bEY74TfCAvDG6WFTnTuLP9";
    QString eventName = "sklenitronTest";
private:
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_networkReply;
};

#endif // IFTTTACCESSMANAGER_H
