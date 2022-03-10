#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <webhookposter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString eventName = "nojsonmsg";
    QString webhooksKey = "bEY74TfCAvDG6WFTnTuLP9";
    QString key = "key";
    QString value = "Hello!";
    QString error;

    //if(!WebhookPoster::postKeyValue(eventName, webhooksKey, key, value, error))
    //if(!WebhookPoster::postEvent(eventName, webhooksKey, error))
    if(!WebhookPoster::postString(eventName, webhooksKey, value, error))
        qDebug() << "Post failed. Error: " << error;
    else {
        qDebug() << "We're Good!";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
