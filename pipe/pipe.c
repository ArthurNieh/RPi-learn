#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

    int pipe_fd[2][2];
    pipe(pipefd[0]) // parent weite to child read
    pipe(pipefd[1]) // child weite to parent read

    pid_t pid = fork();

    // child process
    if(pid == 0){
		close(pipe_fd[0][1]); // close child write on pipe[0]
		close(pipe_fd[1][0]); // close child read on pipe[1]

		
		exit(0);
	}

    // parent process
    close(pipe_fd[0][0]); // close parent read on pipe[0]
	close(pipe_fd[1][1]); // close parent write on pipe[1]


    int status;
    wait(&status);

    printf("%d\n", status);


    return 0;
}
