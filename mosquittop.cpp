#include "mosquittop.h"
#include <QDebug>

int mosquittop::mid = 0;

mosquittop::mosquittop(std::string ip,int port,std::string id,bool clean,int keep,int qos,bool retain)
    :ipAddress_(ip),
      port_(port),
      id_(id),
      cleanSession_(clean),
      keepAlive_(keep),
      qos_(0),
      retain_(false),
      useful_(false)
{
    mqtt_ = mosquitto_new(id_.data(),cleanSession_,NULL);
    if(mqtt_ != NULL){
        useful_ = true;
        qDebug()<<"new successful"<<endl;
    }
}

mosquittop::~mosquittop(){
    qDebug()<<"destruct"<<endl;
}

int
mosquittop::connect(){
   return mosquitto_connect(mqtt_,ipAddress_.data(),port_,keepAlive_);
}

int
mosquittop::disconnect(){
    return mosquitto_disconnect(mqtt_);
}

int
mosquittop::publish(std::string topic,std::string message){
    if(useful_){
        return mosquitto_publish(mqtt_,&mid,topic.data(),message.length(),message.data(),qos_,retain_);
    }
    return MOSQ_ERR_ERRNO;
}
