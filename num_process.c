# include <unistd.h>
# include <stdio.h>
int main() {
	printf(" Bonjour! Le numero de l'utilisateur est %d\n", getuid());
	printf(" Le numero de ce processus est %d\n", getpid());
	printf(" Le numero de papa est %d\n", getppid());
	printf(" - Mon IDUL est 111 124 564\n");
	return 0;
}