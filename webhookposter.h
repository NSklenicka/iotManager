#ifndef WEBHOOKPOSTER_H
#define WEBHOOKPOSTER_H

#include <QObject>

class WebhookPoster : public QObject
{
    Q_OBJECT
public:
    explicit WebhookPoster(QObject *parent = nullptr);

    static bool post( QString eventName, QString webhooksKey, QString &error );


public slots:
};

#endif // WEBHOOKPOSTER_H
