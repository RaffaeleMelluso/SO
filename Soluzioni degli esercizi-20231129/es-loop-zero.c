#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <strings.h>
#include <string.h>
#include <errno.h>

/* Useful macro to debug errors */
#define TEST_ERROR    if (errno) {fprintf(stderr, \
					   "%s:%d: PID=%5d: Error %d (%s)\n",\
					   __FILE__,\
					   __LINE__,\
					   getpid(),\
					   errno,\
					   strerror(errno));}


/* Global variables: if used in both the handler and main */
int n_kids, var=0;
pid_t * children; /* array of child processes */

/*
 * Handler of SIGUSR1 of both parent and child processes. However, only the
 * parent may receive SIGUSR1
 */
void handle_SIGUSR1(int signal)
{
	int target;
	
	/* Condition to terminate random child */
	if (var == 0) {
		/* Index of child process to be killed */
		target = rand() % n_kids;
		
		/* Killing and filling the hole in array of hild PIDs */
		if (kill(children[target], SIGTERM) != -1) {
			if (waitpid(children[target], NULL, 0) == -1) {
				TEST_ERROR;
			}
			children[target] = children[n_kids-1];
			n_kids--;
			printf("PARENT: just killed %d, kids left %d\n",
				children[target], n_kids);
		} else {
			TEST_ERROR;
		}
	}
	if (n_kids == 0)
		exit(0);
}

int main(int argc, char const *argv[])
{
	int n_max, i;
	struct sigaction sa;
	
	/* Getting the parameters */
	if (argc < 3) {
		printf("Too few parameters. Usage:\n<num_kids> <n_max>\n");
		return 1;
	}

	n_kids = atoi(argv[1]);
	n_max = atoi(argv[2]);

	/* Array of child processes and init rand */
	children = calloc(n_kids, sizeof(pid_t));
	srand(time(NULL));

	/* Ignoring SIGUSR1 until all child processes are created */
	bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN; /* SIG_IGN: handler to ignore signal (man sigaction) */
	sigaction(SIGUSR1, &sa, NULL);

	/* Forking kids */
	for (i = 0; i < n_kids; i++) {
		children[i] = fork();
		if (children[i] == 0) {
			free(children);     /* Freeing useless array in child*/
			n_kids = 0;   /* Used to distinguish child processes */
			break;             /* Exit for loop if child process */
		}
	}

	/* Now the parent can properly handle SIGUSR1 */
	if (n_kids) {
		sa.sa_handler = handle_SIGUSR1;
		sigaction(SIGUSR1, &sa, NULL);
	}

	/* Now all processes increment var forever */
	for (var = 0; 1; var++) {
		if (var > n_max) {
			var = 0;
			/* If child, send SIGUSR1 to parent */
			if (!n_kids)
				kill(getppid(), SIGUSR1);
		}
	}
}
