#ifndef WEBHOOKPOSTER_H
#define WEBHOOKPOSTER_H

#include <QString>
#include <QNetworkRequest>

class WebhookPoster
{

public:

    /*
     * Post a simple event IFTTT webhook
     *
     */
    static bool postEvent( QString eventName, QString webhooksKey, QString &error );


    /*
     * Post a simple event IFTTT webhook with a string message (ingredient = value1)
     * x-www-form-urlencoded, will not work with 'json payload'
     */
    static bool postString( QString eventName, QString webhooksKey, QString value1, QString &error );


    /*
     * Post a simple event IFTTT webhook with multiple strings
     * x-www-form-urlencoded, will not work with 'json payload'
     */
    static bool PostStringList( QString eventName, QString webhooksKey, QStringList stringList, QString &error );


    /*
     * Post an IFTTT webhook with one key:value pair as json payload
     *
     */
    static bool postKeyValue( QString const& eventName, QString const& webhooksKey,
                              QString const& key, QString const& value, QString &error );

private:

    static bool PostRequest(QString &error, QNetworkRequest request, QByteArray const& data = QByteArray());

};

#endif // WEBHOOKPOSTER_H
