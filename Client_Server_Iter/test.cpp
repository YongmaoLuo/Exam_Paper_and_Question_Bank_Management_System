using namespace std;
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

#if __has_include(<format>)
#include <format>
#endif

#define FMT_HEADER_ONLY
#include <fmt/format.h>

int main(int argc , char *argv[]) {

    int opt = TRUE;  
    int master_socket , addrlen , new_socket , client_socket[30] , 
          max_clients = 30 , activity, i , valread , sd;  
    int max_sd;  
    struct sockaddr_in address;  
         
    char buffer[BUFF_LENGTH+1];  //data buffer of 1K 
         
    //set of socket descriptors 
    fd_set readfds; 
     
    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  
         
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
     
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
         
    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
    std::string bulletinText="";
    std::string teacherName="";
    std::string questionText="";
         
    while(TRUE)
    {  
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
             
        //add child sockets to set 
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, 
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d "
                  "\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
                  (address.sin_port));  
                 
            puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                         
                    break;  
                }  
            }  
        }  
             
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
                 
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ( (valread = read( sd , buffer, BUFF_LENGTH)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                    
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';
                    json recvPacket=json::parse(buffer);
                    std::cout<<"recvPacket:"<<recvPacket<<std::endl;
                    
                    // test instance 0: register new admin alvin
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"register user\", \"username\" : \"alvin\", \
                                           \"password\": \"1u839812\", \"identity\": \"admin\"}}"));
                    std::string ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0 );
                    // receive code 200

                    // test instance 1: register user duplicated user fail
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"register user\", \"username\" : \"alvin\", \
                                           \"password\": \"89ue982u\", \"identity\": \"teacher\"}}"));
                    std::string ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0 );
                    // receive code 403
                    
                    
                    // test instance 2: admin alvin login wrong password fail
                    sendPacket=json::parse(fmt::format("{{\"command\": \"login\", \"username\": \"alvin\",
                                                          \"password\": \"hjdajshd2\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 403

                    // test instance 3: admin alvin login successful
                    sendPacket=json::parse(fmt::format("{{\"command\": \"login\", \"username\": \"alvin\",
                                                         \"password\": \"1u839812\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200, identity admin

                    // test instance 4: unknown login fail
                    sendPacket=json::parse(fmt::format("{{\"command\": \"login\", \"username\": \"mingzhe\",
                                                          \"password\": \"bdajsbd\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 403

                    // test instance 5: delete admin alvin success
                    sendPacket=json::parse(fmt::format("{{\"command\": \"delete user\", \"username\": \"alvin\",
                                                          \"password\": \"1u839812\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200

                    // test instance 6: delete removed user fail
                    sendPacket=json::parse(fmt::format("{{\"command\": \"delete user\", \"username\": \"alvin\",
                                                          \"password\": \"1u839812\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 403
                    

                    // test instance 7: register new teacher john success
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"register user\", \"username\" : \"john\", \
                                                               \"password\": \"7yae87hf\", \"identity\": \"teacher\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200

                    // test instance 7: register new teacher hyde success
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"register user\", \"username\" : \"hyde\", \
                                                               \"password\": \"y77ayt7\", \"identity\": \"teacher\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200

                    // test instance 8: get teachers success
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"get teachers\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200, count 2, vector<string> {"john", "hyde"}

                    // test instance 9: register new admin mingzhe success
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"register user\", \"username\" : \"mingzhe\", \
                                                              \"password\": \"77t8dgw\", \"identity\": \"admin\"}}"));
                    std::string ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0 );
                    // receive code 200

                    // test instance 10: get users success
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"get users\"}}"));
                    std::string ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200, count 3, vector<string> {john, hyde, mingzhe}

                    // test instance 11: delete teacher john success
                    sendPacket=json::parse(fmt::format("{{\"command\": \"delete user\", \"username\": \"john\",
                                                          \"password\": \"7yae87hf\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200

                    // test instance 12: delete teacher hyde success
                    sendPacket=json::parse(fmt::format("{{\"command\": \"delete user\", \"username\": \"hyde\",
                                                          \"password\": \"y77ayt7\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200

                    // test instance 13: get teachers fail
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"get teachers\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 403

                    // test instance 14: delete admin mingzhe success
                    sendPacket=json::parse(fmt::format("{{\"command\": \"delete user\", \"username\": \"mingzhe\",
                                                          \"password\": \"77t8dgw\"}}"));
                    ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 200

                    // test instance 15: get users fail
                    json sendPacket=json::parse(fmt::format("{{\"command\": \"get users\"}}"));
                    std::string ret=sendPacket.dump();
                    send(sd , ret.c_str(), strlen(ret.c_str()) , 0);
                    // receive code 403
                }  
            }  
        }  
    }  
         
    return 0;
}