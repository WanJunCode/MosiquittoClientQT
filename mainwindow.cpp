#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mosquitto_lib_init();
    mqtt_ = mosquitto_new("wanjun",true,NULL);
    const char *will = "hello this is will";
    int err = mosquitto_will_set(mqtt_,"wanjun_topic",strlen(will),will,1,false);
    err = mosquitto_connect(mqtt_,"localhost",1883,60);
    if(err == MOSQ_ERR_SUCCESS){
        qDebug()<<"mosquitto connect successful"<<endl;
    }
}

MainWindow::~MainWindow()
{
    qDebug()<<"destructure"<<endl;
    mosquitto_disconnect(mqtt_);
    mosquitto_destroy(mqtt_);
    mosquitto_lib_cleanup();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    auto message = ui->messageLine->text().toStdString();
    auto topic = ui->topicLine->text().toStdString();

    int messageId = 0;
    mosquitto_publish(mqtt_,&messageId,topic.data(),message.length(),message.data(),1,true);
    ui->messageLine->clear();
}

void MainWindow::on_linkButton_clicked()
{

}
