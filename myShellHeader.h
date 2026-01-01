#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define RED "\033[31m" 
#define VIOLET "\033[35m" 
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

#define DELIMETER " "

typedef struct BuiltIn {
    char *builtin_name;
    void (*ptr)(char **);
} builtin;