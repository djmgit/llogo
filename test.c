#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "FD";
    const char *delimiters = " ";
    char *token;

    token = strtok(str, delimiters);

    char *val = strtok(NULL, delimiters);

    printf("%s\n", token);
    if (val == NULL) {
        printf("lsldksldk\n");
    }
    
    //printf("%s\n", val);
}
