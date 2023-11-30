#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

long strtol_err(char* string) {
        long ret_var = strtol(string, NULL, 10);
        if(ret_var == 0 && errno != 0) {
                fprintf(stderr, "Error in converting %s into a number", (string));
                exit(-1);
        }
        return ret_var;
} 

int main(int argc, char** argv) {
        long timeout, n_iter, i;
       
        /* error checking*/
        if(argc != 3) {
                fprintf(stderr, "Error: too many/not enough arguments\n");
                exit(-1);
        }
        
        timeout = strtol_err(argv[1]);
        n_iter = strtol_err(argv[2]);
        
        alarm(timeout);

        for(i = 0; i < n_iter; i++);

        return 0;
}







