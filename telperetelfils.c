#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	char idul[11] = "111 124 564";
	pid_t childID = fork();
	if (childID == 0)
	{
		printf("Merci papa! Je prends note, je suis le processus %d et notre createur est %s\n", getpid(), idul);
		sleep(90);
		exit(0);
	}
	else
	{
		printf("Fils! Voici ton numero de processus: %d. Notre createur est %s\n", childID, idul);
		wait(0);
		return 0;
	}
}