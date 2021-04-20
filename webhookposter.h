#ifndef WEBHOOKPOSTER_H
#define WEBHOOKPOSTER_H

#include <QObject>

class WebhookPoster : public QObject
{
    Q_OBJECT
public:
    explicit WebhookPoster(QObject *parent = nullptr);

    static bool post( QString eventName, QString webhooksKey, QString &error );

signals:

private:

    //QString _eventName = "sklenitronTest";
    //QString _webhooksKey = "bEY74TfCAvDG6WFTnTuLP9";

public slots:
};

#endif // WEBHOOKPOSTER_H
