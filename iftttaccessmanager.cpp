#include "iftttaccessmanager.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDebug>

IftttAccessManager::IftttAccessManager(QObject *parent) : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
}

void IftttAccessManager::requestPost()
{
    QUrl url("https://maker.ifttt.com/trigger/" + eventName
             + "/with/key/" + webhooksKey);
    QUrlQuery postData;
    QString value1Str = value1();
    if (!value1Str.isEmpty()) {
        postData.addQueryItem("value1", value1Str);
    }
    QString value2Str = value2();
    if (!value2Str.isEmpty()) {
        postData.addQueryItem("value2", value2Str);
    }
    QString value3Str = value3();
    if (!value3Str.isEmpty()) {
        postData.addQueryItem("value3", value3Str);
    }
    url.setQuery(postData);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");
    m_networkReply = m_networkManager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
    connect(m_networkReply, &QNetworkReply::finished, this,
            [=](){
        if (m_networkReply->error()) {
            emit postFinished((m_networkReply->errorString()));
        } else {
            emit postFinished("POST finished");
        }
        m_networkReply->deleteLater();
    });
}

QString IftttAccessManager::value1()
{
    return "";
}

QString IftttAccessManager::value2()
{
    return "";
}

QString IftttAccessManager::value3()
{
    return "";
}

