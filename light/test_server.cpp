#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc , char *argv[]){
    
    // json to_send = 
    // {
    //     {"cmd", "play"},
    //     {"payload", 24}
    // };
    
    // const char* js_to_message = (const char*)to_send;
    
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
    
    int send_message = 4;

    for(int i=1;i<=send_message;i++){
        sleep(6);
        printf("send %d\n", i);
        // send(socket_client, message, sizeof(message), 0);
        switch(i){
            case 1:
                {
                char message[] = {"one"};
                send(socket_client, message, sizeof(message), 0);
                }
                break;
            case 2:
                {
                char message[] = {"two"};
                send(socket_client, message, sizeof(message), 0);
                }
                break;
            case 3:
                {
                char message[] = {"three"};
                send(socket_client, message, sizeof(message), 0);
                }
                break;
            case 4:
                {
                char message[] = {"last"};
                send(socket_client, message, sizeof(message), 0);
                }
                break;
        }
        // send(socket_client, message, sizeof(message), 0);
    }
    
    close(socket_server);

    return 0;
}