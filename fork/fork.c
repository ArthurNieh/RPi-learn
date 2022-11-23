#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

	pid_t pid = fork();

	if(pid == 0){
		execl("/bin/sh", NULL);
	}

	int status;
	wait(&status);

	printf("%d\n", status);

	return 0;
}
