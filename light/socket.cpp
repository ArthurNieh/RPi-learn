#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <poll.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;


int main() {
    
    char input[256] = {};
    // json input;

    //socket的建立
    int socket_client;
    socket_client = socket(AF_INET , SOCK_STREAM , 0);

    if (socket_client == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;

    server_info.sin_port = htons(9002);
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");


    int connection_status = connect(socket_client, (struct sockaddr *) &server_info, sizeof(server_info));
    if(connection_status == -1){
        printf("Connection Error");
    }

    struct pollfd pollfds;  
    int timeout;  
    
    timeout = 5000;  
    pollfds.fd = socket_client;
    pollfds.events = POLLIN|POLLPRI;

    while(1){  
        bool quit = 0;
        switch(poll(&pollfds,1,timeout)){  
        case -1: 
            printf("poll error \r\n");  
        break;  
        case 0:  
            printf("time out \r\n");  
        break;  
        default: 
            printf("sockfd have some event \r\n");  
            //printf("event value is 0x%x",pollfds.revents);

            recv(socket_client, &input, sizeof(input),0);
            cout<<"message from server:\n"<<input<<endl;
            quit = 1;

            auto j3 = json::parse(input);
            auto command = j3["command"].get<std::string>();
            cout<<command<<endl;

            ofstream o("payload.json");
            o << std::setw(4) << j3 << std::endl;
            // pid_t pid_c=fork();
            // if(pid_c==0){
            //     execl(input, input, NULL);
            // }
            // int status;
            // waitpid(pid_c, &status, 0);
            // printf("Child return : %d\n\n", status);

        break;  
        }
        if(quit) break;
    }
    
    close(socket_client);
    
    return 0;
}