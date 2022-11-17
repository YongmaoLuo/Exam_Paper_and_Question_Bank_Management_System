#include "server.hpp"
// #include "db.cpp"

Server::Server(string digital_certificate_path, string privateKey_path)
{
    setup(DEFAULT_PORT, digital_certificate_path, privateKey_path);
}

Server::Server(string digital_certificate_path, string privateKey_path, int port)
{
    setup(port, digital_certificate_path, privateKey_path);
}

Server::Server(const Server& orig)
{
    masterfds = orig.masterfds;
    tempfds = orig.tempfds;
    maxfd = orig.maxfd;
    mastersocket_fd = orig.mastersocket_fd;
    tempsocket_fd = orig.tempsocket_fd;

    char input_buffer[INPUT_BUFFER_SIZE];
    strcpy(input_buffer, orig.input_buffer);
    char remote_ip[INET6_ADDRSTRLEN];
    strcpy(remote_ip, orig.remote_ip);
}

Server::~Server()
{
	#ifdef SERVER_DEBUG
	std::cout << "[SERVER] [DESTRUCTOR] Destroying Server...\n";
	#endif
	for(map<int, SSL*>::iterator iter=ssl_map.begin(); iter != ssl_map.end(); iter++){
        SSL_shutdown(iter->second);
        SSL_free(iter->second);
    }
    ssl_map.clear();
    int close_ret = close(mastersocket_fd);
    SSL_CTX_free(ctx);
}

void Server::setup(int port, string digital_certificate_path, string privateKey_path)
{
    mastersocket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (mastersocket_fd < 0) {
        perror("Socket creation failed");
    }

    FD_ZERO(&masterfds);
    FD_ZERO(&tempfds);

    memset(&servaddr, 0, sizeof (servaddr)); //bzero
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port);

    bzero(input_buffer,INPUT_BUFFER_SIZE); //zero the input buffer before use to avoid random data appearing in first receives

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    ctx = SSL_CTX_new(SSLv23_server_method());
    if(ctx == NULL){
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    // Load certificate
    if(SSL_CTX_load_verify_locations(ctx, strcat(getenv("HOME"), "/ssl_server_client/ca/ca.crt"), NULL)<=0){
        ERR_print_errors_fp(stdout);
        exit(1);
    }
                
    if (SSL_CTX_use_certificate_file(ctx, digital_certificate_path.c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, privateKey_path.c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    if (!SSL_CTX_check_private_key(ctx)) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
}

void Server::initializeSocket()
{
	#ifdef SERVER_DEBUG
	std::cout << "[SERVER] initializing socket\n";
	#endif
	int opt_value = 1;
	int ret_test = setsockopt(mastersocket_fd, SOL_SOCKET, SO_REUSEADDR, (char *) &opt_value, sizeof (int));
	#ifdef SERVER_DEBUG
	printf("[SERVER] setsockopt() ret %d\n", ret_test);
    #endif
	if (ret_test < 0) {
        perror("[SERVER] [ERROR] setsockopt() failed");
		shutdown();
    }
}

void Server::bindSocket()
{
	#ifdef SERVER_DEBUG
	std::cout << "[SERVER] binding...\n";
	#endif
	int bind_ret = bind(mastersocket_fd, (struct sockaddr*) &servaddr, sizeof (servaddr));
	#ifdef SERVER_DEBUG
	printf("[SERVER] bind() ret %d\n", bind_ret);
	#endif
	if (bind_ret < 0) {
		perror("[SERVER] [ERROR] bind() failed");
	}
	FD_SET(mastersocket_fd, &masterfds); //insert the master socket file-descriptor into the master fd-set
	maxfd = mastersocket_fd; //set the current known maximum file descriptor count
}

void Server::startListen()
{
	#ifdef SERVER_DEBUG
	std::cout << "[SERVER] listen starting...\n";
	#endif
	int listen_ret = listen(mastersocket_fd, 3);
	#ifdef SERVER_DEBUG
	printf("[SERVER] listen() ret %d\n", listen_ret);
	#endif
	if (listen_ret < 0) {
		perror("[SERVER] [ERROR] listen() failed");
	}

}

void Server::shutdown()
{
    for(map<int, SSL*>::iterator iter=ssl_map.begin(); iter != ssl_map.end(); iter++){
        SSL_shutdown(iter->second);
        SSL_free(iter->second);
    }
    ssl_map.clear();
    int close_ret = close(mastersocket_fd);
	#ifdef SERVER_DEBUG
	printf("[SERVER] [DEBUG] [SHUTDOWN] closing master fd..  ret '%d'.\n",close_ret);
	#endif
    SSL_CTX_free(ctx);
}

void Server::handleNewConnection()
{
	#ifdef SERVER_DEBUG
  	std::cout << "[SERVER] [CONNECTION] handling new connection\n";
    #endif
    socklen_t addrlen = sizeof (client_addr);
    tempsocket_fd = accept(mastersocket_fd, (struct sockaddr*) &client_addr, &addrlen);
    	
	if (tempsocket_fd < 0) {
        	perror("[SERVER] [ERROR] accept() failed");
	} else {
        	FD_SET(tempsocket_fd, &masterfds);
		    //increment the maximum known file descriptor (select() needs it)
        	if (tempsocket_fd > maxfd) {
            		maxfd = tempsocket_fd;
			#ifdef SERVER_DEBUG
            		std::cout << "[SERVER] incrementing maxfd to " << maxfd << std::endl;
			#endif
        	}
        	#ifdef SERVER_DEBUG
        	printf("[SERVER] [CONNECTION] New connection on socket fd '%d'.\n",tempsocket_fd);
		    #endif
            
    }
    cout<<"maxfd: "<<maxfd<<endl;
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, tempsocket_fd);
    if(SSL_accept(ssl) == -1){
        perror("accept");
        close(tempsocket_fd);
    }
    ssl_map[tempsocket_fd] = ssl;
    ShowCerts(ssl);

    cout<<"Successfully connected!"<<endl;
    // // newConnectionCallback(tempsocket_fd); //call the callback
    // string message = "Successfully connected!";
    // struct Connector connect_fd = Connector();
    // connect_fd.source_fd = tempsocket_fd;
    // // sendMessage(connect_fd, message.c_str());
    // sendMessageSSL(ssl, message.c_str());
}

void Server::recvInputFromExisting(int fd)
{
    struct Connector connect_fd = Connector();
    connect_fd.source_fd = fd;

    // int nbytesrecv = recvMessage(connect_fd, input_buffer);
    ssl = ssl_map[fd];
    int nbytesrecv = recvMessageSSL(ssl, input_buffer);
    // int nbytesrecv = recv(fd, input_buffer, INPUT_BUFFER_SIZE, 0);
    cout<<"Received bytes: "<<nbytesrecv<<endl;
    if (nbytesrecv <= 0)
    {
        //problem
        if (0 == nbytesrecv)
	    {
        	//disconnectCallback((uint16_t)fd);
		    close(fd); //well then, bye bye.
        	FD_CLR(fd, &masterfds);
        	return;
        } else 
	    {
        	perror("[SERVER] [ERROR] recv() failed");
        }
        close(fd); //close connection to client
        FD_CLR(fd, &masterfds); //clear the client fd from fd set
        return;
    }
    #ifdef SERVER_DEBUG
    printf("[SERVER] [RECV] Received '%s' from client!\n", input_buffer);
    #endif
    // receiveCallback(fd,input_buffer);
    // authenticate the identity of the user
    json message = json::parse(input_buffer);
    cout<<message.dump()<<endl;
    auto command = message["command"];
    string username = "";
    string password = "";
    // string status = "";
    
    if(command == "login"){
        if(message.contains("account")) username = message["username"].get<std::string>();
        else{
            perror("No account.\n");
            exit(1);
            }
        if(message.contains("password")) password = message["password"].get<std::string>();
        else{
            perror("No password.\n");
            exit(1);
        }
        // if(message.contains("status")) status = message["status"].get<std::string>();
        // else{
        //     perror("No status.\n");
        //     exit(1);
        // }
        // authenticateUser(connect_fd, account, password, status);
        authenticateUser(ssl, username, password);
    }
    //memset(&input_buffer, 0, INPUT_BUFFER_SIZE); //zero buffer //bzero
    bzero(&input_buffer,INPUT_BUFFER_SIZE); //clear input buffer
}

// void Server::authenticateUser(Connector connect_fd, string account, string password, string status){
void Server::authenticateUser(SSL *cur_ssl, string username, string password){
    string message;
    int status_code;
    // with database logic
    status_code = 200;
    string identity = "admin";
    #ifdef __cpp_lib_format
    message = std::format("{\"status\": \"{}\", \"identity\": \"{}\"}", status_code, identity);
    #else
    message = fmt::format("{{\"status\": \"{}\", \"identity\": \"{}\"}}", status_code, identity);
    #endif
    
    //int bytes = sendMessage(connect_fd, message.c_str());
    int bytes = sendMessageSSL(cur_ssl, message.c_str());
    while(bytes < 0){
        //bytes = sendMessage(connect_fd, message.c_str());
        bytes = sendMessageSSL(cur_ssl, message.c_str());
    }
}

void Server::loop()
{
    tempfds = masterfds; //copy fd_set for select()
    #ifdef SERVER_DEBUG
    printf("[SERVER] [MISC] max fd = '%hu' \n", maxfd);
    std::cout << "[SERVER] [MISC] calling select()\n";
    #endif
    int sel = select(maxfd + 1, &tempfds, NULL, NULL, NULL); //blocks until activity
    //printf("[SERVER] [MISC] select() ret %d, processing...\n", sel);
    if (sel < 0) {
        perror("[SERVER] [ERROR] select() failed");
        shutdown();
    }
    cout<<"sel: "<<sel<<endl;

    //no problems, we're all set

    //loop the fd_set and check which socket has interactions available
    for (int i = 0; i <= maxfd; i++) {
        if (FD_ISSET(i, &tempfds)) { //if the socket has activity pending
            if (mastersocket_fd == i) {
                //new connection on master socket
                handleNewConnection();
            } else {
                //exisiting connection has new data
                recvInputFromExisting(i);
            }
        } //loop on to see if there is more
    }
}

void Server::init()
{
    initializeSocket();
    bindSocket();
    startListen();
}

void Server::onInput(void (*rc)(uint16_t fd, char *buffer))
{
    receiveCallback = rc;
}

void Server::onConnect(void(*ncc)(uint16_t))
{
    newConnectionCallback = ncc;
}

void Server::onDisconnect(void(*dc)(uint16_t))
{
    disconnectCallback = dc;
}

uint16_t Server::sendMessage(Connector conn, char *messageBuffer) {
    return send(conn.source_fd, messageBuffer, strlen(messageBuffer), 0);
}

uint16_t Server::sendMessageSSL(SSL *ssl, char *messageBuffer){
    return SSL_write(ssl, messageBuffer, strlen(messageBuffer));
}

uint16_t Server::sendMessage(Connector conn, const char *messageBuffer) {
    return send(conn.source_fd, messageBuffer, strlen(messageBuffer), 0);
}

uint16_t Server::sendMessageSSL(SSL *ssl, const char *messageBuffer){
    return SSL_write(ssl, messageBuffer, strlen(messageBuffer));
}

uint16_t Server::recvMessage(Connector conn, char *messageBuffer){
    return recv(conn.source_fd, messageBuffer, INPUT_BUFFER_SIZE, 0);
}

uint16_t Server::recvMessageSSL(SSL *ssl, char *messageBuffer){
    return SSL_read(ssl, messageBuffer, INPUT_BUFFER_SIZE);
}



int main(int argc, char *argv[]){
    string digital_certificate_path = argv[1];
    string privateKey_path = argv[2];

    /*******************/
    // db_user user = db_user();
    // user.create();
    /*****************/

    Server server_object = Server(digital_certificate_path, privateKey_path);
    server_object.init();
    while(true)
        server_object.loop();
    return 0;
}