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
    auto msg = ui->messageLine->text();
    qDebug()<<"test"<<endl;

    int messageId = 0;
    const char *message = msg.toLatin1().data();
    if(message != NULL){
        mosquitto_publish(mqtt_,&messageId,"wanjun_topic",strlen(message),message,1,true);
    }
    ui->messageLine->clear();
}
