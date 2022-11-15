
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc , char *argv[])
{

    //socket的建立
    int socket_clent;
    socket_clent = socket(AF_INET , SOCK_STREAM , 0);

    if (socket_clent == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;

    server_info.sin_port = htons(9002);
    server_info.sin_addr.s_addr = INADDR_ANY;


    int connection_status = connect(socket_clent, (struct sockaddr *) &server_info, sizeof(server_info));
    if(connection_status == -1){
        printf("Connection Error");
    }

    //Send a message to server
    char command[100] = {};
    char receiveMessage[100] = {};

    recv(socket_clent, &receiveMessage, sizeof(receiveMessage),0);
    printf("%s", receiveMessage);
    
    scanf("%s", command);
    send(socket_clent, command, sizeof(command), 0);
    
    recv(socket_clent, &receiveMessage, sizeof(receiveMessage),0);
    printf("%s", receiveMessage);

    char number[100] = {};
    scanf("%s", number);
    send(socket_clent, number, sizeof(number), 0);
    
    recv(socket_clent, &receiveMessage, sizeof(receiveMessage),0);
    printf("%s", receiveMessage);
    
    close(socket_clent);
    return 0;
}