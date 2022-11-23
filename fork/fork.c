#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

	while(1){

		char input[256];
		scanf(" %s", input);
		//printf("%s\n", input);
		if(strcmp(input, "exit") == 0){
			break;
		}

		pid_t pid = fork();

		if(pid == 0){
			//execl("/bin/ls", "ls", "-l", NULL);
			if(strcmp(input, "one") == 0){
				execl("./one", "one", NULL);
			}
			else if(strcmp(input, "two") == 0){
				execl("./two", "two", NULL);
			}
			else{
				execl("./three", "three", NULL);
			}

			exit(0);
		}

		int status;
		wait(&status);

		printf("%d\n", status);
	}

	printf("program end.\n");

	return 0;
}
