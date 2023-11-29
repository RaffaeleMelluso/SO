#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define BUFF_SIZE 100
#define ASSERT_PRINT_ERROR(assert, string) \
        if( (assert) ) {\
                fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, string); exit(-1);}

/* function works only assuming csv file contains at least one row and one column */
/* reads a single line of a csv file and returns the number of commas + 1, aka the number of columns */
int count_columns(char * buffer) {
        int columns = 1;
        int i = 0;

        while(i < BUFF_SIZE && buffer[i] != '\0') {
                if(buffer[i++] == ',') {
                        columns++;
                }
        }

        return columns;
}

int* double_array_size(int* array, int* size) {
        int* ret;

        if(*size == 0) {
                ++(*size);

                ret = (int*) malloc(sizeof(int) * (*size));
                return ret;
        }

        (*size) <<= 1;  /* doubling *size */

        ret = (int*) realloc(array, sizeof(int) * (*size));
        ASSERT_PRINT_ERROR(
                (ret == NULL),
                "Error while allocating memory: "
        );

        return ret;
}

int** generate_arrays(int* n_columns, int* n_rows, FILE* csv_file_stream) {
        int** arrays;
        int i;
        char buffer[BUFF_SIZE];
        int allocated_rows;

        /* inserting first line of file in buffer */
        ASSERT_PRINT_ERROR((fgets(buffer, BUFF_SIZE, csv_file_stream) == NULL),
                "Error while reading file: ");

        *n_columns = count_columns(buffer);
        *n_rows = 1;
        allocated_rows = 0;

        arrays = (int**) malloc(sizeof(int*) * (*n_columns));
        ASSERT_PRINT_ERROR((arrays == NULL),
                "Error while allocating memory: ");

        do {
                char* temp = buffer;
		
		/* Reallocating the arrays if needed */
                if(*n_rows > allocated_rows) {
                        for(i = 0; i < *n_columns; i++) {
                                arrays[i] = double_array_size(arrays[i], &allocated_rows);
                        }
                }

		/* Split the row in single values */
                for(i = 0; i < *n_columns; i++) {
                        temp = strtok(temp, ",\0\n"); /* split a row with delimiters. Check man strtok */
                        arrays[i][*n_rows - 1] = strtol(temp, NULL, 10);
                        temp = NULL;
                }

                (*n_rows)++;

                ASSERT_PRINT_ERROR(
                        (fgets(buffer, BUFF_SIZE, csv_file_stream) == NULL && errno != 0),
                        "Error while reading file: "
                );
        } while(!feof(csv_file_stream));

        --(*n_rows); /* Necessary because we incremented in the last iteration */

        return arrays;
}

void data_column_process(int * data, int length, int * min, int * max, double * avg) {
        int i;
        double _avg;

        *min = INT_MAX;
        *max = INT_MIN;
        _avg = 0;

        for(i = 0; i < length; i++) {
                if(*min > data[i])
                        *min = data[i];
                if(*max < data[i])
                        *max = data[i];
                _avg += data[i];  /* accumulating on a (double) variable */
        }

        *avg = _avg / length;
}

int main(int argc, char** argv) {
        int n_columns, n_rows, i, j;
        int** arrays;
        FILE* csv_file_stream;

        if(argc != 2) {
                fprintf(stderr, "Error: too many/not enough arguments\n");
                return -1;
        }

        csv_file_stream = fopen(argv[1], "r");
        ASSERT_PRINT_ERROR((csv_file_stream == NULL), "Error while opening file: "); 

        arrays = generate_arrays(&n_columns, &n_rows, csv_file_stream);


        for(i = 0; i < n_columns; i++) {
                int max, min;
                double avg;

                data_column_process(arrays[i], n_rows, &min, &max, &avg);

                printf("Column %d: min=%d, max=%d, avg=%f\n", i, min, max, avg);
        }

        /*termination*/
        for(i = 0; i < n_columns; i++) {
                free(arrays[i]);
        }

        free(arrays);
        fclose(csv_file_stream);
        return 0;
}
