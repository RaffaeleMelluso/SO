#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#define BUFFER 50

struct child {
        pid_t pid;
        long iter;
        int rerun;
};

long strtol_err(char* string);

void run_child(long timeout, long n_iter);
int lookup_arr(struct child*, int size, pid_t pid);

int main(int argc, char** argv) {
        long timeout, n_iter, n_kids;
        int i, exit_status;
        struct child* children_data;
        pid_t pid;
        
        /* error checking*/
        if(argc != 4) {
                fprintf(stderr, "Error: too many/not enough arguments\n");
                exit(-1);
        }
  
        timeout = strtol_err(argv[1]);
        n_iter = strtol_err(argv[2]);
        n_kids = strtol_err(argv[3]);
        
        children_data = malloc(sizeof(*children_data) * n_kids);
        
        for(i = 0; i < n_kids; i++) {
                children_data[i].iter = n_iter;
                children_data[i].pid = fork();
                children_data[i].rerun = 0;

		/* Inside run_child, execve is invoked:
		 * the child process does not continue the loop
		 */
                if(children_data[i].pid == 0)
                        run_child(timeout, n_iter);
        }
        
        while((pid = wait(&exit_status)) != -1) {
                if(WIFSIGNALED(exit_status)) {
                        /*printf("Child %d was killed by signal, ", pid);*/
                        i = lookup_arr(children_data, n_kids, pid);
                        
                        /* Dividing the iterations by 2 */
                        children_data[i].iter >>= 1;
                        children_data[i].pid = fork();
                        ++children_data[i].rerun;

                        if(children_data[i].pid == 0)
                                run_child(timeout, children_data[i].iter);
                        
                        /*printf("now it's %d and will run for %ld iterations\n", children_data[i].pid, children_data[i].iter);*/
                }
        }
        
        for(i = 0; i < n_kids; i++) {
                printf("Child %d, iterations: %ld iterations, rerun: %d times\n", children_data[i].pid, children_data[i].iter, children_data[i].rerun);
        }
        

        return 0;
}

void run_child(long timeout, long n_iter) {
        char timeout_str[BUFFER];
        char n_iter_str[BUFFER];
        char* args[4];
        args[0] = "";
        args[1] = timeout_str;
        args[2] = n_iter_str;
        args[3] = NULL;
        
        snprintf(timeout_str, BUFFER-1, "%ld", timeout);
        snprintf(n_iter_str, BUFFER-1, "%ld", n_iter);
        
        execve("count-loop", args, NULL);
        
        perror("");
        
        exit(-2);
}

int lookup_arr(struct child* children, int size, pid_t pid) {
        int i = 0;
        for(i = 0; i < size; i++) {
                if(children[i].pid == pid)
                        return i;
        }
        return -1;
}

long strtol_err(char* string) {
        long ret_var = strtol(string, NULL, 10);
        if(ret_var == 0 && errno != 0) {
                fprintf(stderr, "Error in converting %s into a number", string);
                exit(-1);
        }
        return ret_var;
} 





