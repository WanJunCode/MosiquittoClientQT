#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    isConnect(false)
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
    if(activePublish()){
        auto message = ui->messageLine->text().toStdString();
        auto topic = ui->topicLine->text().toStdString();
        int err = mqtt_->publish(topic,message);
        if(err == MOSQ_ERR_SUCCESS){
            qDebug()<<"publih ok"<<endl;
        }
    }else{
        qDebug()<<"active publish is false"<<endl;
    }
}

void MainWindow::on_linkButton_clicked()
{
    if( !isConnect ){
        auto ip = ui->ipAddress->text().toStdString();
        auto port = ui->portLine->text().toInt();
        auto id = ui->idLine->text().toStdString();
        if(mqtt_ == NULL)
            mqtt_ = new mosquittop(ip,port,id);
        // must be called before connect
        mqtt_->setWill(ui->willLine->text().toStdString(),"wanjun/will");

        if(ip != mqtt_->getAddress() || port != mqtt_->getPort()){
            // 新的连接,更新 ip port
            mqtt_->setAddress(ip);
            mqtt_->setPort(port);
        }
        if(mqtt_->connect() == MOSQ_ERR_SUCCESS){
            isConnect = true;
            ui->statusLable->setText("已连接");
            ui->linkButton->setText("disconnect");
        }else{
            qDebug()<<"connect failure..."<<endl;
        }
    }else{
//        disconnect
        qDebug()<<"disconnect"<<endl;
        mqtt_->disconnect();
        isConnect = false;
        ui->linkButton->setText("connect");
        ui->statusLable->setText("未连接");
    }
}


bool MainWindow::activePublish() const{
    if(ui->topicLine->text().isEmpty() || ui->messageLine->text().isEmpty() || mqtt_ == NULL || isConnect == false)
        return false;
    return true;
}
