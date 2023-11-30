#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

/* Type for the message */
struct msg {
	long mtype;	/* message type, must be > 0 */
	int data;	/* message data */
};


int main(int argc, char * argv[])
{
	int i, i_snd, n_kids, number, q_id, status;
	pid_t child_pid;

	struct msg my_msg;	/* struct for the message */

	/* Parsing command-line arguments */
	if (argc < 3) {
		fprintf(stderr, "Please provde at least <num_procs> and <init_range>\n");
		exit(1);
	}
	if ((n_kids = strtol(argv[1], NULL, 10)) <= 0) {
		fprintf(stderr, "Unable to read <num_procs> from argv[1]\n");
		exit(1);
	}
	if ((number = strtol(argv[2], NULL, 10)) <= 0) {
		fprintf(stderr, "Unable to read <init_range> from argv[2]\n");
		exit(1);
	}

	/* No need to set the handler of SIGLARM: the default action (Term) is fine */

	/* Create the MSG queue */
	q_id = msgget(IPC_PRIVATE, 0600);
	
	/* Now forking kids */
	for (i=1; i<=n_kids; i++) {
		if (fork() == 0) {
			srand(getpid()); /* Initialize a different seed per child */
			i_snd = (i==n_kids ? 1 : i+1);	/* this process is sending a message to process i_snd */
			while (1) {	/* Loop forever: terminated by SIGALRM */
				alarm(1);	/* start the timer: kill the process upon expiration */
				msgrcv(q_id, &my_msg, sizeof(my_msg)-sizeof(long), i, 0);
				if (my_msg.data == 0) {
					/* Got zero, then terminating */
					printf("PID=%d (CHILD %d): received 0, TERMINATING\n", getpid(), i);
					exit(i);
				}
				printf("PID=%d (CHILD %d): received %d, ", getpid(), i, my_msg.data);
				if (rand() % 2) {
					my_msg.data--;
				}
				my_msg.mtype = i_snd;
				printf("sent %d\n", my_msg.data);
				msgsnd(q_id, &my_msg, sizeof(my_msg)-sizeof(long), 0);
			}
		}
	}
	
	/* Init the sequence */
	srand(getpid());
	my_msg.mtype = 1;
	my_msg.data = rand() % number + 1;
	msgsnd(q_id, &my_msg, sizeof(my_msg)-sizeof(long), 0);
	
	/* Wait for the child processes termination */
	while ((child_pid = wait(&status)) != -1) {
		printf("PID= %5d (PARENT): Child with PID=%d terminated with status 0x%04X\n",
		       getpid(), child_pid, status);
	}
	if (errno != ECHILD) {
		fprintf(stderr,"wait returned -1, but NOT ECHILD... Need to be investigated\n");
	}
	msgctl(q_id, IPC_RMID, 0);
}

