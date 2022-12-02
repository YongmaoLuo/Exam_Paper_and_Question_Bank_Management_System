#ifndef SERVER_HPP
#define SERVER_HPP


#include <set>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //sockaddr, socklen_t
#include <arpa/inet.h>
#include <netdb.h>
#include <cassert>
#include <iostream>
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

// #include "db.hpp"

class question_bank;
class Server
{
public:
    Server();
    Server(int port);
    Server(const Server& orig);
    virtual ~Server();
    
    struct Connector {
        uint16_t source_fd;
    };
    
    void shutdown();
    void init();
    void loop(db_user&);

    //callback setters
    void onConnect(void (*ncc)(uint16_t fd));
    void onInput(void (*rc)(uint16_t fd, char *buffer));
    void onDisconnect(void (*dc)(uint16_t fd));

    uint16_t sendMessage(Connector conn, const char *messageBuffer);
    uint16_t sendMessage(Connector conn, char *messageBuffer);
    uint16_t recvMessage(Connector conn, char *messageBuffer);

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

    string message;
    map<int, string> bindIdentity;
    map<int, string> bindUsername;
    set<string> usernameSet;
    map<string, int> logined_users;

    void (*newConnectionCallback) (uint16_t fd);
    void (*receiveCallback) (uint16_t fd, char *buffer);
    void (*disconnectCallback) (uint16_t fd);


    //function prototypes
    void setup(int port);
    void initializeSocket();
    void bindSocket();
    void startListen();
    void handleNewConnection();
    vector<string> recvInputFromExisting(Connector&);
    void sendMsgToExisting(Connector&, vector<string>&);
    vector<string> registerUser(Connector& connect_fd, string username, auto password, string identity);
    vector<string> authenticateUser(Connector& conn, string username, auto password);
    vector<string> logout(Connector&);
    int logout(string); // function overload
    vector<string> deleteUser(Connector&, string username);
    vector<string> deleteUserSelf(Connector&, auto password);
    vector<string> getUser(Connector& connect_fd);
    
    vector<string> getSubjects(Connector&);
    vector<string> getChapters(Connector&, auto subject);
    vector<string> getQuestions(Connector&, auto subject, auto chapter);
    vector<string> readQuestion(Connector&, auto subject, auto chapter, auto question);
    vector<string> writeQuestion(Connector& connect_fd, auto subject, auto chapter, auto question, string text);
    vector<string> deleteQuestion(Connector& connect_fd, auto subject, auto chapter, auto question);
    
    vector<string> getTeachers(Connector&);
    
    //void *getInetAddr(struct sockaddr *saddr);
};

#endif /* SERVER_HPP */