#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_iftttAccessManager = new IftttAccessManager(this);

    connect(m_iftttAccessManager, &IftttAccessManager::postFinished, this,
             [](const QString &result){
       qDebug() << result;
    });

    m_iftttAccessManager->requestPost();
    qDebug() << "POST Started";
}

MainWindow::~MainWindow()
{
    delete ui;
}
