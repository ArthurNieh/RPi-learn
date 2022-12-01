
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
    char user_name[100] = {};
    char welcomeMessage[256] = {};
    
    recv(socket_clent, &welcomeMessage, sizeof(welcomeMessage),0);
    printf("%s", welcomeMessage);
    
    scanf("%s", user_name);
    send(socket_clent, user_name, sizeof(user_name), 0);
    
    while(1){

        char receiveMessage[256] = {};

        recv(socket_clent, &receiveMessage, sizeof(receiveMessage),0);
        printf("%s", receiveMessage);

        char command[256] = {};
        scanf("%s", command);
        send(socket_clent, command, sizeof(command), 0);

        recv(socket_clent, &receiveMessage, sizeof(receiveMessage),0);
        printf("%s\n", receiveMessage);

        if(strcmp(receiveMessage,"Byebye!") == 0){
            break;
        }

        char message1[256] = {};
        scanf("%s", message1);
        send(socket_clent, message1, sizeof(message1), 0);

        // message to encode/decode sent

        char result_from_server[256] = {};
        recv(socket_clent, &result_from_server, sizeof(result_from_server),0);
        printf("%s\n", result_from_server);
    }
    
    
    
    
    close(socket_clent);
    return 0;
}