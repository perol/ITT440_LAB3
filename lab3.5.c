#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <math.h>

int main(void) 
	{
	void sigint_handler(int sig);

	if(signal(SIGINT, sigint_handler) == SIG_ERR) 
	{
		perror("Signal");
		exit(EXIT_SUCCESS);
	}
	
	int num;
	int buffer;
	int pipefds[2];
	pipe(pipefds);
	pid_t pid = fork();
	
	if(pid == 0) 
	{
		printf("Enter a number : \n");
		scanf("%d", &num);
		close(pipefds[0]);
		write(pipefds[1], &num, sizeof(num));
		exit(EXIT_SUCCESS);
	}

	else if(pid > 0) 
	{
		
		wait(NULL);
		close(pipefds[1]);
		read(pipefds[0], &buffer, sizeof(int));
		close(pipefds[0]);

		if(buffer <= 3) {
			if(buffer == 1) {
				printf("%d is not a prime number.\n", buffer);
			}
			else {
				printf("%d is a prime number.\n", buffer);
			}
			exit(EXIT_SUCCESS);
		}

		if(buffer > 3) {
			for(int i = 2; i <= buffer/2; i++) {
				if(buffer % i == 0) {
					printf("%d is not a prime number.\n", buffer);
					exit(1);
				}
				else {
					printf("%d is a prime number.\n", buffer);
					exit(1);
				}
			}
		}

		printf("DONE!!!\n");
	}
	else {
		perror("ERROR");
	}

	return 0;
}

void sigint_handler(int sig)
 {
	printf("This is a special signal handler for INT \n");

 }
