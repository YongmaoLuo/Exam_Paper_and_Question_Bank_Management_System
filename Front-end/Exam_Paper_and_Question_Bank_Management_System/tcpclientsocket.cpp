#include "tcpclientsocket.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

TCPClientSocket::TCPClientSocket()
{
    if((this->fd=socket(AF_INET,SOCK_STREAM,0)<0)){
        std::cout<<"Create socket error"<<std::endl;
        this->fd=-1;
    }
    this->sAddr.sin_family = AF_INET;
}

int TCPClientSocket::updateServerAddress(std::string ip, int port){
    this->sAddr.sin_port = htons(port);
    if(inet_aton(ip.c_str(),&this->sAddr.sin_addr)==0){
        std::cout<<"set destination ip address failed"<<std::endl;
        return -1;
    }
    return 0;
}

int TCPClientSocket::connectToServer(){
    if(this->fd==-1){
        std::cout<<"fd invalid"<<std::endl;
        return -1;
    }
    return connect(this->fd,(struct sockaddr*)&this->sAddr,sizeof(this->sAddr));
}

int TCPClientSocket::sendToServer(json sendJson){
    if(this->fd==-1){
        std::cout<<"fd invalid"<<std::endl;
        return -1;
    }

    int length=strlen(sendJson.dump().c_str());
    if(length>BUFF_LENGTH){
        std::cout<<"message to be sent is too long"<<std::endl;
        return -1;
    }
    int n = send(this->fd, sendJson.dump().c_str(), length, 0);
    if(n==-1){
        std::cout<<"fail to send to server"<<std::endl;
        return -1;
    }
    return -1;
}

int TCPClientSocket::receive(json &receivedJson){
    if(this->fd==-1){
        std::cout<<"fd invalid"<<std::endl;
        return -1;
    }
    memset(this->recvBuff,0,sizeof(this->recvBuff));
    int n=recv(this->fd,this->recvBuff,BUFF_LENGTH,0);
    if(n==-1){
        std::cout<<"fail to receive bytes from server"<<std::endl;
        return -1;
    }
    if(this->recvBuff[BUFF_LENGTH]!=0){
        std::cout<<"receiving message too long"<<std::endl;
        return -1;
    }
    receivedJson=json::parse(recvBuff);
    return 0;
}
