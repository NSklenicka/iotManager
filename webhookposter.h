#ifndef WEBHOOKPOSTER_H
#define WEBHOOKPOSTER_H

#include <QObject>

class WebhookPoster : public QObject
{
    Q_OBJECT
public:
    explicit WebhookPoster(QObject *parent = nullptr);

    static bool postEvent( QString eventName, QString webhooksKey, QString &error );

    //no json payload, value1
    static bool postString( QString eventName, QString webhooksKey, QString value1, QString &error );

    //json payload
    static bool postKeyValue( QString const& eventName, QString const& webhooksKey,
                              QString const& key, QString const& value, QString &error );


public slots:
};

#endif // WEBHOOKPOSTER_H
