#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <webhookposter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString eventName = "sklenitronTest";
    QString webhooksKey = "bEY74TfCAvDG6WFTnTuLP9";
    QString error;

    if(!WebhookPoster::post(eventName, webhooksKey, error))
        qDebug() << "Post failed. Error: " << error;
    else {
        qDebug() << "Post returned true.";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
