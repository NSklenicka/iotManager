#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <webhookposter.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    m_iftttAccessManager = new IftttAccessManager(this);

//    connect(m_iftttAccessManager, &IftttAccessManager::postFinished, this,
//             [](const QString &result){
//       qDebug() << result;
//    });

//    m_iftttAccessManager->requestPost();
//    qDebug() << "POST Started";

    WebhookPoster *iot = new WebhookPoster;
    iot->post();

}

MainWindow::~MainWindow()
{
    delete ui;
}
