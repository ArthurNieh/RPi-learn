#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <sys/wait.h>
#include <unistd.h>

int main(int argc , char *argv[])

{
    //socket的建立
    char inputBuffer[256] = {};
    
    char message1[] = {"Hi,this is server.\nUser name?"};
    char message2[] = {"Command(e/d):"};
    char message3[] = {"What's your message?"};

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
    
    //get user name
    send(socket_client, message1, sizeof(message1), 0);
    recv(socket_client,inputBuffer,sizeof(inputBuffer),0);
    printf("User:%s\n",inputBuffer);

    while(1){
        char command[256] = {};

        send(socket_client, message2, sizeof(message2), 0);
        recv(socket_client,command,sizeof(command),0);
        printf("Get command:%s\n",command);

        if(strcmp(command,"exit") == 0){
            char message4[] = {"Byebye!"};
            send(socket_client, message4, sizeof(message4), 0);
            break;
        }

        char message_got[256] = {};

        send(socket_client, message3, sizeof(message3), 0);
        recv(socket_client,message_got,sizeof(message_got),0);
        printf("Get message:%s\n",message_got);

        //message to encode/decode got

        int pipe_fd[2][2];
        pipe(pipe_fd[0]); // parent weite to child read
        pipe(pipe_fd[1]); // child weite to parent read

        pid_t pid = fork();

        // child process
        if(pid == 0){
            close(pipe_fd[0][1]); // close child write on pipe[0]
            close(pipe_fd[1][0]); // close child read on pipe[1]

            char output_from_child[sizeof(message_got)];

            if(strcmp(command,"e") == 0){
                for(int i=0;i<sizeof(message_got);i++){
                    if(message_got[i]>123 || message_got[i]<63) break;
                    output_from_child[i] = message_got[i]+1;
                }
            }
            else if(strcmp(command,"d") == 0){
                for(int i=0;i<sizeof(message_got);i++){
                    if(message_got[i]>123 || message_got[i]<63) break;
                    output_from_child[i] = message_got[i]-1;
                }
            }
            else{
                strcpy(output_from_child, "error command");
            }
            write(pipe_fd[1][1],output_from_child,sizeof(output_from_child));
            
            exit(0);
        }

        // parent process
        close(pipe_fd[0][0]); // close parent read on pipe[0]
        close(pipe_fd[1][1]); // close parent write on pipe[1]

        char message_from_child[sizeof(message_got)];
        read(pipe_fd[1][0],message_from_child,sizeof(message_from_child));

        int status;
        wait(&status);

        printf("Get message from child process by pipe\n%s\n", message_from_child);

        send(socket_client, message_from_child, sizeof(message_from_child), 0);

    }

    



    close(socket_server);

    return 0;
}