#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'twoArrays' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 *  3. INTEGER_ARRAY B
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* twoArrays(int k, int A_count, int* A, int B_count, int* B) {
    /*Find the smallest possible element in array B that, when added to the
    current index of array A, will be greater than or equal to k.*/
    for(int i = 0; i < A_count; i++)
    {
      /*Variable to hold the index of B containing the smallest element that
      when added to A[i], will be greater than or equal to k. Defaulted to -1
      until set.*/
      int indexOfLeast = -1;
      //Match the current index of A with all the elements of B
      for(int j = 0; j < B_count; j++)
      {
        /*If the current element of B plus the current element of A at least
        equals k, and hasn't been used yet...*/
        if(A[i] + B[j] >= k && B[j] >= 0)
        {
          /*...and if the indexOfLeast hasn't been set yet, or if the current
          element of B is smaller than the previously selected element...*/
          if(indexOfLeast == -1 || B[j] < B[indexOfLeast])
          {
            //...set the indexOfLeast to the current index of B .
            indexOfLeast = j;
          }
        }
        /*If the current index is the last index of B, and indexOfLeast hasn't
        been set yet, the passed arrays can't be successfully permutated.*/
        else if(indexOfLeast == -1 && j + 1 == B_count)
        {
          return "NO";
        }
      }
      /*Set the selected index of B to -1, so that it can't be used again when
      matching the next element of A.*/
      B[indexOfLeast] = -1;
    }

    /*If all of array A has been iterated through without a "NO" returned, then
    the arrays can be successfully permutated. Return "YES".*/
    return "YES";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int k = parse_int(*(first_multiple_input + 1));

        char** A_temp = split_string(rtrim(readline()));

        int* A = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int A_item = parse_int(*(A_temp + i));

            *(A + i) = A_item;
        }

        char** B_temp = split_string(rtrim(readline()));

        int* B = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int B_item = parse_int(*(B_temp + i));

            *(B + i) = B_item;
        }

        char* result = twoArrays(k, n, A, n, B);

        fprintf(fptr, "%s\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
