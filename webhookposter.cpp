#include "webhookposter.h"

#include <QUrlQuery>
#include <QNetworkReply>
#include <QDebug>
#include <QApplication>

#define TIMEOUT_SEC 3

bool WebhookPoster::postEvent(QString eventName, QString webhooksKey, QString &error)
{
    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/with/key/" +webhooksKey);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");//maybe don't need this
    QNetworkAccessManager networkManager;
    QNetworkReply *networkReply = networkManager.post(request, QByteArray());
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
        QApplication::processEvents();
    }
    qDebug() << "post finished";
    networkError = networkReply->error();
    error = networkReply->errorString();
    networkReply->deleteLater();
    return networkError == QNetworkReply::NoError;
}


bool WebhookPoster::postString(QString eventName, QString webhooksKey, QString value1, QString &error)
{
    QString data = QString("?value1=%1").arg(value1);
    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/with/key/" +webhooksKey +data);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    return PostRequest(error, request);
}

bool WebhookPoster::PostStringList(QString eventName, QString webhooksKey, QString value1, QString &error)
{
    return true;
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
        QApplication::processEvents();
    }
    qDebug() << "post finished";
    networkError = networkReply->error();
    error = networkReply->errorString();
    networkReply->deleteLater();
    return networkError == QNetworkReply::NoError;
}
