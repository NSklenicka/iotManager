#include "webhookposter.h"
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

WebhookPoster::WebhookPoster(QObject *parent) : QObject(parent)
{

}

bool WebhookPoster::post()
{
    QUrl url("https://maker.ifttt.com/trigger/" + _eventName
             + "/with/key/" + _webhooksKey);
    QUrlQuery postData;
//    QString value1Str = value1();
//    if (!value1Str.isEmpty()) {
//        postData.addQueryItem("value1", value1Str);
//    }
//    QString value2Str = value2();
//    if (!value2Str.isEmpty()) {
//        postData.addQueryItem("value2", value2Str);
//    }
//    QString value3Str = value3();
//    if (!value3Str.isEmpty()) {
//        postData.addQueryItem("value3", value3Str);
//    }
    url.setQuery(postData);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");
    QNetworkReply *networkReply;
    QNetworkAccessManager *networkManager = new QNetworkAccessManager;
    networkReply = networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    qDebug() << "networkManager->post started";
    connect(networkReply, &QNetworkReply::finished, this,
            [=](){
        if (networkReply->error())
        {
            //emit postFinished((m_networkReply->errorString()));
            qDebug() << "Error: " << networkReply->errorString();
        }
        else
        {
            //emit postFinished("POST finished");
            qDebug() << "POST finished";
        }
        networkReply->deleteLater();
    });
    return true;
}
