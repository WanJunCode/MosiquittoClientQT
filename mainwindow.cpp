#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mqtt_ = NULL;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete mqtt_;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(mqtt_){
        auto message = ui->messageLine->text().toStdString();
        auto topic = ui->topicLine->text().toStdString();
        int err = mqtt_->publish(topic,message);
        if(err == MOSQ_ERR_SUCCESS){
            qDebug()<<"publih ok"<<endl;
        }
    }
}

void MainWindow::on_linkButton_clicked()
{
    if(mqtt_ == NULL){
        auto ip = ui->ipAddress->text().toStdString();
        auto port = ui->portLine->text().toInt();
        auto id = ui->idLine->text().toStdString();
        mqtt_ = new mosquittop(ip,port,id);
        mqtt_->setWill("this is a will");
        mqtt_->connect();
    }else{
        qDebug()<<"have had a mqtt client"<<endl;
    }
}
