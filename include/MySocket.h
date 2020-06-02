#ifndef __MYSOCKET_H__
#define __MYSOCKET_H__
#include"Myconf.h"
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<string>
#include<netinet/in.h>

class MySocket
{
public:
    MySocket(MyConf&conf):conf_(conf)
    {
            std::cout<<conf._mapConf["my_ip"]<<std::endl;
            peerfd_ = socket(AF_INET,SOCK_DGRAM,0);
            if(peerfd_ ==-1)
            {
                std::cout<<__DATE__<<" "<<__TIME__<<" "<<
                __FILE__<<" "<<__LINE__<<":"<<"cosket err"<<std::endl;
                exit(-1);
            } 
            addrLen_ = sizeof(addr_);
            addr_.sin_family=AF_INET;
            addr_.sin_port=htons(atoi(conf_._mapConf["my_port"].c_str()));
            addr_.sin_addr.s_addr = inet_addr(conf_._mapConf["my_ip"].c_str());
            if(-1==bind(peerfd_,(struct sockaddr*)&addr_,addrLen_))
            {
                std::cout<<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<":"<<"bind"<<std::endl;;
                exit(-1);
            }
    }

    int send_message(void *buf,int len)
    {
        return sendto(peerfd_,buf,len,0,(struct sockaddr*)&addr_,sizeof(addr_));
    }

    int recv_message(void *buf,int len)
    {
        std::cout<<"socket::recv..."<<std::endl;
        return recvfrom(peerfd_,buf,len,0,(struct sockaddr*)&addr_,&addrLen_);
    }

    const struct sockaddr_in get_addr()const
    {
        return addr_;
    }
    ~MySocket()
    {
       close(peerfd_);
    }



private:
    int peerfd_;
    struct sockaddr_in addr_;
    socklen_t addrLen_;
    MyConf&conf_;

};

#endif