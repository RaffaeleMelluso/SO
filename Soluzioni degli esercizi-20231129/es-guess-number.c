# define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Global variable set in the handler when timer expired */
int expired = 0;

void handle_signal(int signal);

int main(int argc, char * argv[]){
	unsigned int number, guess;
	struct sigaction sa;

	if (argc <= 2) {
		fprintf(stderr,
			"Please speficy\n\targv[1]=max number\n\targv[2]=max time\n");
		exit(-1);
	}

	bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_signal;
	sigaction(SIGALRM, &sa, NULL);

	srand(getpid());  /* Rand seed init with PID */
	number = rand() % (atoi(argv[1])+1);

	alarm(atoi(argv[2]));
	while (!expired) {
		printf("\nEnter your guess: ");
		errno = 0; /* Resetting errno */
		scanf("%u",&guess);
		switch (errno) {
		case 0:     /* No error */
			if (guess == number) {
				printf("Number %d guessed!\n", number);
				exit(0);
			}
			if (guess > number) {
				printf("Your guess %d is too large\n", guess);
			} else {
				printf("Your guess %d is too small\n", guess);
			}
			break;
		case EINTR: /* Time expired while waiting on scanf */
			break;
		}
	}
	printf("Sorry, time expired. Try again.\n");
}

void handle_signal(int signal) {
	if (signal == SIGALRM) {
		expired = 1;
	} else {
		dprintf(2, "Non dovrebbe succedere\n");
	}
}
