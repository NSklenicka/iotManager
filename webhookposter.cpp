#include "webhookposter.h"
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QApplication>

WebhookPoster::WebhookPoster(QObject *parent) : QObject(parent)
{

}

bool WebhookPoster::post( QString eventName, QString webhooksKey, QString &error)
{
    QUrl url("https://maker.ifttt.com/trigger/" + eventName
             + "/with/key/" + webhooksKey);
    QUrlQuery postData;
    url.setQuery(postData);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");
    QNetworkAccessManager networkManager;
    QNetworkReply *networkReply = networkManager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
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
