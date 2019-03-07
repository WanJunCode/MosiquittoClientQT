#ifndef MOSQUITTOP_H
#define MOSQUITTOP_H
#include <mosquitto.h>
#include <string>

class mosquittop
{
public:
    mosquittop(std::string ip,int port,std::string id,bool clean = true,int keep = 60,int qos = 0,bool retain = false);
    ~mosquittop();

    int connect();
    int disconnect();
    int publish(std::string topic,std::string message);

    inline void setAddress(std::string ip){
        ipAddress_ = ip;
    }

    inline void setPort(int port){
        port_ = port;
    }

    inline void setKeep(int keep){
        keepAlive_ = keep;
    }

    inline void setClean(bool clean){
        cleanSession_ = clean;
    }

    inline void setWill(std::string will){
        will_ = will;
        mosquitto_will_clear(will_);
    }

    std::string getWill(){
        return will_;
    }

private:
    struct mosquitto *  mqtt_;
    std::string         ipAddress_;
    int                 port_;
    std::string         id_;
    int                 keepAlive_;
    std::string         will_;
    bool                cleanSession_;
    int                 qos_;
    bool                retain_;
    bool                useful_;

public:
    static int mid;
};

#endif // MOSQUITTOP_H
