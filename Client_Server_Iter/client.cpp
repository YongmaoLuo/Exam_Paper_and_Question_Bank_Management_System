#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;

#define PORT 9999

int read_iterative(int sd, char* ptr, int size){
    int left_bytes, read_bytes;
    left_bytes = size;
    while(left_bytes > 0){
        read_bytes = read(sd, ptr, left_bytes);
        if(read_bytes < 0) return (read_bytes);
        if(read_bytes == 0) break;
        left_bytes -= read_bytes;
        ptr += read_bytes;
    }
    // everything in the buffer zone has been read into the ptr
    return (size - left_bytes);
}

int write_iterative(int sd, char* ptr, int size){
    int left_bytes, written_bytes;
    left_bytes = size;
    while(left_bytes > 0){
        written_bytes = write(sd, ptr, left_bytes);
        if(written_bytes < 0) return (written_bytes);
        if(written_bytes == 0) break;
        left_bytes -= written_bytes;
        ptr += written_bytes;
    }
    return (size - left_bytes);
}

int recv_iterative(int sd, char* ptr, int size, int flag){
    int left_bytes, recv_bytes;
    left_bytes = size;
    while(left_bytes > 0){
        recv_bytes = recv(sd, ptr, left_bytes, flag);
        if(recv_bytes < 0) return (recv_bytes);
        if(recv_bytes == 0) break;
        left_bytes -= recv_bytes;
        ptr += recv_bytes;
    }
    // everything in the buffer zone has been read into the ptr
    return (size - left_bytes);
}

int send_iterative(int sd, char* ptr, int size, int flag){
    int left_bytes, sent_bytes;
    left_bytes = size;
    while(left_bytes > 0){
        sent_bytes = send(sd, ptr, left_bytes, flag);
        printf("in send %s", ptr);
        if(sent_bytes < 0) return (sent_bytes);
        if(sent_bytes == 0) break;
        left_bytes -= sent_bytes;
        ptr += sent_bytes;
    }
    return (size - left_bytes);
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 2) {
       fprintf(stderr,"usage %s hostname\n", argv[0]);
       exit(0);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]); // 34.139.226.174
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    n = recv(sockfd, buffer, 255, 0);
    printf("%s \n", buffer);
    if (n < 0) 
         error("ERROR reading from socket");
    bzero(buffer,256);

    char login_msg[] = "{\"command\": \"login\",\"name\": \"admin\",\"password\": \"123456\"}";
    login_msg[strlen(login_msg)] = '\0';
    for(int i=0; i< static_cast<int> (strlen(login_msg)); i++){
        buffer[i] = login_msg[i];
    }
    n = send(sockfd, buffer, 255, 0);
    if (n < 0) 
         error("ERROR writing to socket");
    
    bzero(buffer, 256);
    recv(sockfd, buffer, 255, 0);
    printf("%s \n", buffer);
    
    close(sockfd);
    return 0;
}