#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int argc , char *argv[])

{
    //socket的建立
    char inputBuffer[256] = {};
    char inputBuffer2[256] = {};
    char message[] = {"Hi,this is server.\nCommand(double/half):"};
    char message2[] = {"number?"};
    int socket_server;
    socket_server = socket(AF_INET , SOCK_STREAM , 0);

    if (socket_server == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in serverInfo;
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_port = htons(9002);
    serverInfo.sin_addr.s_addr = INADDR_ANY;

    bind(socket_server, (struct sockaddr *) &serverInfo,sizeof(serverInfo));
    
    listen(socket_server, 5);

    int socket_client;

    socket_client = accept(socket_server, NULL, NULL);
    
    send(socket_client, message, sizeof(message), 0);
    recv(socket_client,inputBuffer,sizeof(inputBuffer),0);
    printf("Get:%s\n",inputBuffer);


    send(socket_client, message2, sizeof(message2), 0);
    recv(socket_client,inputBuffer2,sizeof(inputBuffer2),0);
    printf("Get:%s\n",inputBuffer2);

    if(inputBuffer[0] == 'd'){
        char double_message[] = {"I don't give a shit.\n"};
        send(socket_client, double_message, sizeof(double_message), 0);
    }
    else if(inputBuffer[0] == 'h'){
        char half_message[] = {"I don't give a shit, either.\n"};
        send(socket_client, half_message, sizeof(half_message), 0);
    }
    else{
        char error_message[] = {"Wrong command!\n"};
        send(socket_client, error_message, sizeof(error_message), 0);
    }


    close(socket_server);

    return 0;
}