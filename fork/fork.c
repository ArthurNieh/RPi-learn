#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

	while(1){

		char input[] = {};
		scanf(" %s", input);
		//printf("%s\n", input);
		if(strcmp(input, "exit") == 0){
			break;
		}

		pid_t pid = fork();

		if(pid == 0){
			execlp("/bin/sh", "ls", "-l", NULL);
			printf("delete");
			exit(0);
		}

		int status;
		wait(&status);

		printf("%d\n", status);
	}

	printf("program end.\n");

	return 0;
}
