#ifndef WEBHOOKPOSTER_H
#define WEBHOOKPOSTER_H

#include <QObject>

class WebhookPoster : public QObject
{
    Q_OBJECT
public:
    explicit WebhookPoster(QObject *parent = nullptr);

    static bool postEvent( QString eventName, QString webhooksKey, QString &error );

    static bool postKeyValue( QString const& eventName, QString const& webhooksKey,
                              QString const& key, QString const& value, QString &error );


public slots:
};

#endif // WEBHOOKPOSTER_H
