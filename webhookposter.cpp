#include "webhookposter.h"
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QApplication>

WebhookPoster::WebhookPoster(QObject *parent) : QObject(parent)
{

}

bool WebhookPoster::postEvent(QString eventName, QString webhooksKey, QString &error)
{
    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/with/key/" +webhooksKey);
    //QByteArray data = QString("{\"%1\":\"%2\"}").arg(key).arg(value).toLatin1();
    //postData.setQuery(json);
    //url.setQuery(postData);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager networkManager;
    QNetworkReply *networkReply = networkManager.post(request, QByteArray());
    qDebug() << "networkManager.post started";

    // Start a timeout timer.
    QTime timer;
    timer.start();

    QNetworkReply::NetworkError networkError;
    while( !networkReply->isFinished() )
    {
        if( timer.elapsed() >= ( 3 * 1000 ) )
        {
            networkReply->abort();
            networkError = QNetworkReply::TimeoutError;
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
//nojsonmsg
bool WebhookPoster::postString(QString eventName, QString webhooksKey, QString value1, QString &error)
{
    QString data = QString("?value1=%1").arg(value1);
    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/with/key/" +webhooksKey +data);
    //QByteArray data = QString("{\"%1\":\"%2\"}").arg(key).arg(value).toLatin1();
    //postData.setQuery(json);
    //url.setQuery(postData);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkAccessManager networkManager;
    QNetworkReply *networkReply = networkManager.post(request, QByteArray());
    qDebug() << "networkManager.post started";

    // Start a timeout timer.
    QTime timer;
    timer.start();

    QNetworkReply::NetworkError networkError;
    while( !networkReply->isFinished() )
    {
        if( timer.elapsed() >= ( 3 * 1000 ) )
        {
            networkReply->abort();
            networkError = QNetworkReply::TimeoutError;
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

bool WebhookPoster::postKeyValue( QString const& eventName, QString const& webhooksKey,
                                  QString const& key, QString const& value, QString &error )
{

    QUrl url("https://maker.ifttt.com/trigger/" +eventName+ "/json/with/key/" +webhooksKey);
    //QUrlQuery postData;
    QByteArray data = QString("{\"%1\":\"%2\"}").arg(key).arg(value).toLatin1();
    //QByteArray json{"{\"Error\":\"a bad thing happened!\"}"};
    //QByteArray str{"{\"Hello\"}"};//bad request
    //postData.setQuery(json);
    //url.setQuery(postData);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager networkManager;
    QNetworkReply *networkReply = networkManager.post(request, data);
    qDebug() << "networkManager.post started";

    // Start a timeout timer.
    QTime timer;
    timer.start();

    QNetworkReply::NetworkError networkError;
    while( !networkReply->isFinished() )
    {
        if( timer.elapsed() >= ( 3 * 1000 ) )
        {
            networkReply->abort();
            networkError = QNetworkReply::TimeoutError;
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
