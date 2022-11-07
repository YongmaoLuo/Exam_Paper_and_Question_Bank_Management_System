#include "client.hpp"

int Client::read_iterative(char* ptr, int size){
    int left_bytes, read_bytes;
    left_bytes = size;
    while(left_bytes > 0){
        read_bytes = read(socket_fd, ptr, left_bytes);
        if(read_bytes < 0) return (read_bytes);
        if(read_bytes == 0) break;
        left_bytes -= read_bytes;
        ptr += read_bytes;
    }
    // everything in the buffer zone has been read into the ptr
    return (size - left_bytes);
}

int Client::write_iterative(char* ptr, int size){
    int left_bytes, written_bytes;
    left_bytes = size;
    while(left_bytes > 0){
        written_bytes = write(socket_fd, ptr, left_bytes);
        if(written_bytes < 0) return (written_bytes);
        if(written_bytes == 0) break;
        left_bytes -= written_bytes;
        ptr += written_bytes;
    }
    return (size - left_bytes);
}

int Client::recv_iterative(char* ptr, int size, int flag){
    int left_bytes, recv_bytes;
    left_bytes = size;
    while(left_bytes > 0){
        recv_bytes = recv(socket_fd, ptr, left_bytes, flag);
        if(recv_bytes < 0) return (recv_bytes);
        if(recv_bytes == 0) break;
        left_bytes -= recv_bytes;
        ptr += recv_bytes;
    }
    // everything in the buffer zone has been read into the ptr
    return (size - left_bytes);
}

int Client::send_iterative(char* ptr, int size, int flag){
    int left_bytes, sent_bytes;
    left_bytes = size;
    while(left_bytes > 0){
        sent_bytes = send(socket_fd, ptr, left_bytes, flag);
        printf("in send %s", ptr);
        if(sent_bytes < 0) return (sent_bytes);
        if(sent_bytes == 0) break;
        left_bytes -= sent_bytes;
        ptr += sent_bytes;
    }
    return (size - left_bytes);
}

Client::Client(){
    setup(PORT);
}

Client::~Client(){
    #ifdef SERVER_DEBUG
	std::cout << "[SERVER] [DESTRUCTOR] Destroying Server...\n";
	#endif
	close(socket_fd);
}

Client::Client(int port){
    setup(port);
}

Client::Client(const Client& org){
}

void Client::setup(int port){
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
}

uint16_t Client::sendMessage(Connector conn, const char *messageBuffer){
    return send(conn.source_fd, messageBuffer, strlen(messageBuffer), 0);
}

uint16_t Client::sendMessage(Connector conn, char *messageBuffer){
    return send(conn.source_fd, messageBuffer, strlen(messageBuffer), 0);
}

uint16_t Client::recvMessage(Connector conn, char *messageBuffer){
    return recv(conn.source_fd, messageBuffer, INPUT_BUFFER_SIZE, 0);
}

void Client::error(const char *msg)
{
    perror(msg);
    exit(0);
}

void Client::initConnect(hostent* server){
    if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
    }
    cout<<"Start connecting!"<<endl;

    bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
    serv_addr.sin_port = htons(PORT);
    if (connect(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
}

void Client::loop(){
    
    struct Connector connect_fd = Connector();
    connect_fd.source_fd = socket_fd;
    
    num_bytes = recvMessage(connect_fd, buffer);
    printf("%s \n", buffer);
    if (num_bytes < 0) 
         error("ERROR reading from socket");
    bzero(buffer,256);

    string account = "\"admin\"";
    string password = "\"123456\"";
    string status = "\"valid\"";
    string identity = "\"admin\"";
    struct UserInfo user = UserInfo();
    user.account = account;
    user.password = password;
    user.status = status;
    user.identity = identity;

    string login_msg = fmt::format("{{\"command\": \"login\",\"account\": {},\"password\": {}, \"status\": {}, \"identity\": {}}}", 
    user.account, user.password, user.status, user.identity);
    cout<<"login msg"<<login_msg<<endl;
    // login_msg[strlen(login_msg)] = '\0';

    num_bytes = sendMessage(connect_fd, login_msg.c_str());
    if (num_bytes < 0) 
         error("ERROR writing to socket");
    cout<<"Sent a login command!"<<endl;
    
    bzero(buffer, 256);
    num_bytes = recv(socket_fd, buffer, 255, 0);
    buffer[num_bytes] = '\0';
    cout<<"buffer: "<<buffer<<endl;

    json response = json::parse(buffer);
    auto response_code = response["status"];
    cout<<"Response code: "<<response_code<<endl;
    
}
int main(int argc, char *argv[])
{   
    Client client = Client();
    struct hostent *server = gethostbyname(argv[1]); // 34.139.226.174
    client.initConnect(server);
    client.loop();
    return 0;
}