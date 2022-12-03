#include "tcpclientsocket.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

TCPClientSocket::TCPClientSocket()
{
    if((this->fd=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("create socket");
        this->fd=-1;
    }
    memset(&this->sAddr,0,sizeof(this->sAddr));
    this->sAddr.sin_len=sizeof(this->sAddr);
    this->sAddr.sin_family = AF_INET;
}

TCPClientSocket::~TCPClientSocket()
{
    close(this->fd);
}


int TCPClientSocket::updateServerAddress(std::string ip, int port){
    this->sAddr.sin_port = htons(port);
    if(inet_aton(ip.c_str(),&this->sAddr.sin_addr)==0){
        perror("set destination ip address failed");
        return -1;
    }
    return 0;
}

int TCPClientSocket::connectToServer(){
    if(this->fd==-1){
        perror("fd invalid");
        return -1;
    }
    return connect(this->fd,(struct sockaddr*)&this->sAddr,sizeof(this->sAddr));
}

int TCPClientSocket::sendToServer(json sendJson){
    if(this->fd==-1){
        perror("fd invalid");
        return -1;
    }

    int length=strlen(sendJson.dump().c_str());
    if(length>BUFF_LENGTH){
        perror("message to be sent is too long");
        return -1;
    }
    int n = send(this->fd, sendJson.dump().c_str(), length, 0);
    if(n==-1){
        perror("fail to send to server");
        return -1;
    }
    return 0;
}

int TCPClientSocket::receive(json &receivedJson){
    if(this->fd==-1){
        perror("fd invalid");
        return -1;
    }
    memset(this->recvBuff,0,sizeof(this->recvBuff));
    int n=recv(this->fd,this->recvBuff,BUFF_LENGTH,0);
    if(n==-1){
        perror("fail to receive bytes from server");
        return -1;
    }
    if(this->recvBuff[BUFF_LENGTH]!=0){
        perror("receiving message too long");
        return -1;
    }
    std::cout<<"recv message: "<<recvBuff<<std::endl;
    receivedJson=json::parse(recvBuff);
    return 0;
}
