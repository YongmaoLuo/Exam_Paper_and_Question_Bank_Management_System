#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

#if __has_include(<format>)
#include <format>
#endif

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#define INPUT_BUFFER_SIZE 256 //test: 256 bytes of buffer
#define PORT 9999

class Client{
    private:
        int socket_fd, num_bytes;
        struct sockaddr_in serv_addr;
        char buffer[256];
        struct hostent *server;

        int read_iterative(char* ptr, int size);
        int write_iterative(char* ptr, int size);
        int recv_iterative(char* ptr, int size, int flag);
        int send_iterative(char* otr, int size, int flag);
        void error(const char *msg);
        
    public:
        struct UserInfo{
            string account;
            string password;
            string identity;
            string status;
        };
        struct Connector{
            uint16_t source_fd;
        };
        Client();
        Client(int port);
        Client(const Client& orig);
        virtual ~Client();
        void setup(int port);
        void loop();
        void initConnect(hostent *server);

        uint16_t sendMessage(Connector conn, const char *messageBuffer);
        uint16_t sendMessage(Connector conn, char *messageBuffer);
        uint16_t recvMessage(Connector conn, char *messageBuffer);
};
#endif /* CLIENT_HPP */