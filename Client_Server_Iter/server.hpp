#ifndef SERVER_HPP
#define SERVER_HPP


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr, socklen_t
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

#define INPUT_BUFFER_SIZE 1024 //test: 1024 bytes of buffer
#define DEFAULT_PORT 9999

#if __has_include(<format>)
#include <format>
#endif

#define FMT_HEADER_ONLY
#include <fmt/format.h>


void ShowCerts(SSL *ssl){
    X509 *cert;
    char* line;
    cert = SSL_get_peer_certificate(ssl);
    if(SSL_get_verify_result(ssl) == X509_V_OK){
        cout<<"Authentication passed."<<endl;
    }
    if(cert) {
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        cout<<"Certificate info: "<<line<<endl;
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        cout<<"Provider: "<<line<<endl;
        free(line);
        X509_free(cert);
    }
    else cout<<"No certificate provided."<<endl;
}

class Server
{
public:
    Server(string, string);
    Server(string, string, int port);
    Server(const Server& orig);
    virtual ~Server();
    
    struct Connector {
        uint16_t source_fd;
    };

    struct UserInfo {
        string account;
        string password;
        string identity;
        string status;
    };
    
    void shutdown();
    void init();
    void loop();

    //callback setters
    void onConnect(void (*ncc)(uint16_t fd));
    void onInput(void (*rc)(uint16_t fd, char *buffer));
    void onDisconnect(void (*dc)(uint16_t fd));

    uint16_t sendMessage(Connector conn, const char *messageBuffer);
    uint16_t sendMessage(Connector conn, char *messageBuffer);
    uint16_t recvMessage(Connector conn, char *messageBuffer);
    uint16_t sendMessageSSL(SSL *ssl, char *messageBuffer);
    uint16_t sendMessageSSL(SSL *ssl, const char *messageBuffer);
    uint16_t recvMessageSSL(SSL *ssl, char *messageBuffer);

private:
    //fd_set file descriptor sets for use with FD_ macros
    fd_set masterfds;
    fd_set tempfds;

    //unsigned integer to keep track of maximum fd value, required for select()
    uint16_t maxfd;

    //socket file descriptors
    int mastersocket_fd; //master socket which receives new connections
    int tempsocket_fd; //temporary socket file descriptor which holds new clients

    //client connection data
    struct sockaddr_storage client_addr;
    //server socket details
    struct sockaddr_in servaddr;
    //input buffer
    char input_buffer[INPUT_BUFFER_SIZE];

    char remote_ip[INET6_ADDRSTRLEN];
    //int numbytes;
    SSL_CTX* ctx;
    SSL* ssl;
    map<int, SSL*> ssl_map;

    void (*newConnectionCallback) (uint16_t fd);
    void (*receiveCallback) (uint16_t fd, char *buffer);
    void (*disconnectCallback) (uint16_t fd);


    //function prototypes
    void setup(int, string, string);
    void initializeSocket();
    void bindSocket();
    void startListen();
    void handleNewConnection();
    void recvInputFromExisting(int fd);
    // void authenticateUser(Connector conn, string account, string password, string status);
    void authenticateUser(SSL* ssl, string annount, string password, string status);

    //void *getInetAddr(struct sockaddr *saddr);
};

#endif /* SERVER_HPP */