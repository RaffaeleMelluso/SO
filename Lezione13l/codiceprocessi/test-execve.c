#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define BUF_LEN		100

int main (void)
{
	pid_t child_pid;
	int status;
	char command[BUF_LEN];
	
	/* Preparing environment variables for invoking execve */
	char* env_vars[] = {
		"VAR1=variabile1",
		"HOME=boh",
		"questa_senza_uguale",
		NULL
	};
	
	/* Preparing command-line arguments for invoking execve */
	char* args[] = {
		"name_command",   /* */
		"VAR1",
		"AAAAAAAAAAAAAAAA",
		"BBBBBBBBBBBBBBBB",		
		NULL
	};

	printf("%s: My PID is %d and my parent's PID is %d\n",
	       __FILE__, getpid(), getppid());

	/* Read the command to replace this executable */
	printf("Enter the command to be executed\n");
	fgets(command, BUF_LEN, stdin);
	/* Erasing the last new line character '\n' */
	command[strlen(command)-1] = 0;
	/* Try with: wjhjfhkjf, test-env, test-command-line, test-getpid */	

	/* Now replacing this process with the executable with name in command */
	execve(command, args, env_vars);
	
	/* don't need to check success. If here not success */
	fprintf(stderr, "%s: %d. Error #%03d: %s\n",
		__FILE__, __LINE__, errno, strerror(errno));
	
	exit(-1);
}
