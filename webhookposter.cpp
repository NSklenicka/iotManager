#include "webhookposter.h"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QDebug>

#define TIMEOUT_SEC 3

#ifdef QT_WIDGETS_LIB
   #include <QApplication>
   #define PROCESS_EVENTS QApplication::processEvents()
#else
    #include <QCoreApplication>
    #define PROCESS_EVENTS QCoreApplication::processEvents()
#endif


bool WebhookPoster::postEvent(QString eventName, QString webhooksKey, QString &error)
{
    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/with/key/" +webhooksKey);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return PostRequest(error, request);
}


bool WebhookPoster::postString(QString eventName, QString webhooksKey, QString value1, QString &error)
{
    QString data = QString("?value1=%1").arg(value1);
    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/with/key/" +webhooksKey +data);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    return PostRequest(error, request);
}

bool WebhookPoster::PostStringList(QString eventName, QString webhooksKey, QStringList list, QString &error)
{
    QString data;
    if(!list.isEmpty())
        data.append("?");

    for(int i = 0; i < list.size() && i < 3; ++i)
    {
        data.append(QString("value%2=%1&").arg(list[i]).arg(i+1));
    }
    data.chop(1);//remove last &
    qDebug() << "data: " << data;

    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/with/key/" +webhooksKey +data);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    return PostRequest(error, request);
}


bool WebhookPoster::postKeyValue( QString const& eventName, QString const& webhooksKey,
                                  QString const& key, QString const& value, QString &error )
{

    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/json/with/key/" +webhooksKey);
    QByteArray data = QString("{\"%1\":\"%2\"}").arg(key).arg(value).toLatin1();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    return PostRequest(error, request, data);
}

bool WebhookPoster::PostRequest(QString &error, QNetworkRequest request, QByteArray const& data)
{
    QNetworkAccessManager networkManager;
    QNetworkReply *networkReply = networkManager.post(request, data);
    qDebug() << "post started";

    // Start a timeout timer.
    QTime timer;
    timer.start();

    QNetworkReply::NetworkError networkError;
    while( !networkReply->isFinished() )
    {
        if( timer.elapsed() >= ( TIMEOUT_SEC * 1000 ) )
        {
            networkReply->abort();
            error = QString("timeout after %1 seconds waiting for network reply").arg(TIMEOUT_SEC);
            return false;
        }
        PROCESS_EVENTS;
    }
    qDebug() << "post finished";
    networkError = networkReply->error();
    error = networkReply->errorString();
    networkReply->deleteLater();
    return networkError == QNetworkReply::NoError;
}
