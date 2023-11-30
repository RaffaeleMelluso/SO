#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define NAME_EXEC "./char-loop"
#define CHAR_START "a" /* come stringa perche' deve essere terminata da zero */

/*
 * Need to be global variables to be accessed by both the main and the
 * signal handler.
 */
pid_t *all_kids;
int num_proc;
char * args[] = {NAME_EXEC, CHAR_START, NULL};

void signal_handler(int);

int main (int argc, char * argv[]) {
	int  i, status;
	char * s;
	unsigned int s_size=4; /* initial lenght to grow if needed */
	unsigned char cur_sum = 0;
	struct sigaction sa;

	/* If passed an argument to the executable */
	if (argc <= 1) {
		fprintf(stderr,"Please specify argv[1] equal to the kids to fork\n");
		exit(1);
	}
	num_proc = atoi(argv[1]);
	if (num_proc == 0) {
		fprintf(stderr,"Please specify argv[1] equal to the kids to fork\n");
		exit(1);
	}

	/* Setting the handler of SIGALRM */
	bzero(&sa, sizeof(sa));
	sa.sa_handler = signal_handler;
	/* if SIGALRM is delivered in wait need to restart */
	sa.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &sa, NULL);
	
	/* vector of kids PIDs */
	all_kids = malloc(num_proc*sizeof(*all_kids));
	for (i=0; i<num_proc; i++) {
		switch (all_kids[i] = fork()) {
		case -1:
			/* Handle error */
			fprintf(stderr, "%s, %d: Errore (%d) nella fork\n",
				__FILE__, __LINE__, errno);
			exit(EXIT_FAILURE);
		case 0:
			/* CHILD CODE */
			/* "Jumping" to the child executable */
			execve(NAME_EXEC, args, NULL);
			fprintf(stderr, "%s, %d: Errore (%d) nella execve\n",
				__FILE__, __LINE__, errno);
			exit(EXIT_FAILURE);
			break;
		default:
			/* PARENT CODE: nothing here */
			break;
		}
	}


	/* stringa per gli exit value dei figli */
	s = malloc(s_size);

	alarm(1);
	/* Reset dell'indice */
	i = 0;
	while (wait(&status) != -1) {
		if (WIFEXITED(status)) {
			/* store the char in the string */
			s[i] = WEXITSTATUS(status);
			/* cur_sum is char: (%256) is implicit in the
			 * assignment */
			cur_sum += s[i];
			s[++i] = 0;
			if (cur_sum == 0) {
				break;
			}
			/* Need another SIGALRM */
			alarm(1);
			printf("%s\ncur_sum = %d\n", s, cur_sum);
			if (i+1 >= s_size) {
				/* The string must grow */
				s_size <<= 1;
				s = realloc(s,s_size);
			}
		} else {
			fprintf(stderr,"Process terminated without exit. status=0x%04X\n",status);
			exit(1);
		}
	}
	printf("FINITO\n%s\ncur_sum = %d\n", s, cur_sum);
	free(s);
	
	/* 
	 * Invio del segnale SIGINT (equivalente a Ctrl+C) a tutti i
	 * processi figlio. Questo segnale verra` gestito dal figlio
	 * che eseguira` una semplice exit
	 */
	for (i=0; i<num_proc; i++) {
		kill(all_kids[i], SIGINT);
	}
	free(all_kids);
	
	printf("CARATTERI DEI FIGLI ANCORA VIVI\n");
	/* Waiting the just terminated kids */
	while (wait(&status) != -1) {
		if (WIFEXITED(status)) {
			printf("%c", WEXITSTATUS(status));
		}
	}
	printf("\n");
	exit(EXIT_SUCCESS);
}


void signal_handler(int signum) {
	int i_killed;

	i_killed = rand() % num_proc;
	kill(all_kids[i_killed], SIGINT);
	/* Fork a new child. Feasible in the signal handler */
	if (!(all_kids[i_killed] = fork())) {
		execve(NAME_EXEC, args, NULL);
		fprintf(stderr, "%s, %d: Errore (%d) nella execve\n",
			__FILE__, __LINE__, errno);
		exit(EXIT_FAILURE);
	}
}
