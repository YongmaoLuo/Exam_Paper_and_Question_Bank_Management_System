#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <string>
#include <netinet/in.h>
#include <nlohmann/json.hpp>
using json=nlohmann::json;

#define BUFF_LENGTH 4096

class TCPClientSocket
{
    int fd;
    struct sockaddr_in sAddr;
    char recvBuff[BUFF_LENGTH+1];

public:
    TCPClientSocket();
    ~TCPClientSocket();
    int updateServerAddress(std::string, int port=4995);
    int connectToServer();
    int sendToServer(json);
    int receive(json &);
};

#endif // TCPCLIENTSOCKET_H
