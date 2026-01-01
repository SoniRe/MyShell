#include "myShellHeader.h"

void executeEcho(char **);
void executeEnv(char **);
void executeBuiltin(char **);
void executeExit(char **);

builtin arrayBuiltin[] = {
    {.builtin_name = "echo", .ptr = executeEcho},
    {.builtin_name = "env", .ptr = executeEnv},
    {.builtin_name = "exit", .ptr = executeExit},
    {.builtin_name = "builtin", .ptr = executeBuiltin},
    {.builtin_name = NULL},
};

void executeEcho(char **args) {
    for(int i = 1;args[i];i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void executeEnv(char **args) {
    extern char **environ;

    for(int i = 0;environ[i];i++) {
        printf("%s\n", environ[i]);
    }
}

void executeBuiltin(char **args) {
    char *cur;
    int i = 0;

    while(cur = arrayBuiltin[i].builtin_name) {
        printf("%s\n", cur);
        i++;
    }
}

void executeExit(char **args) {
    exit(EXIT_SUCCESS);
}

void executeCommand(char **args) {
    char *cur;
    int i = 0;

    while(cur = arrayBuiltin[i].builtin_name) {
        if(strcmp(cur, args[0]) == 0) {
            (arrayBuiltin[i].ptr)(args);
            return;
        }
        i++;
    }
    
    //Not the Builtin Functions
    int status;

    if(fork() == 0) {
        int ret = execvp(args[0], args); 
        if(ret == -1) {
            printf(RED "MyShell Failed" RESET": No such file or Directory\n");
        }
    }
    else 
        wait(&status);
}

char **splitIntoTokens(char *line) {
    char **tokenList;
    tokenList = malloc(512 * sizeof(*tokenList));
    int argc = 0;

    for(char *token = strtok(line, DELIMETER); token; token = strtok(NULL, DELIMETER)) {
        tokenList[argc++] = token;
    }

    tokenList[argc] = NULL;

    return tokenList;
}

char *myReadLine() {
    char *buff = NULL;
    size_t size;

    char cwd[512];
    if(getcwd(cwd, sizeof(cwd)) == NULL) {
        perror(RED "getcwd Failed\n" RESET);
    }

    printf(CYAN"☣️ %s>"RESET, cwd);

    int nread = getline(&buff, &size, stdin);

    if(nread > 0 && buff[nread - 1] == '\n') buff[nread - 1] = '\0';

    if(nread == -1) {
        free(buff);
        buff = NULL;

        if(feof(stdin) == 1)
        printf(RED"End Of File\n"RESET); 
        else 
        printf(RED"Getline Failed\n"RESET);
    }

    return buff;
}

int main(int argc, char **argvc) {
    char *line = NULL;
    char **args = NULL;
    int len = 0;
    printf("\n" VIOLET 
         "  ██╗    ███╗   ███╗██╗   ██╗███████╗██╗  ██╗███████╗██╗     ██╗         ██╗\n"      
         " ██╔╝    ████╗ ████║╚██╗ ██╔╝██╔════╝██║  ██║██╔════╝██║     ██║         ╚██╗\n"     
         "██╔╝     ██╔████╔██║ ╚████╔╝ ███████╗███████║█████╗  ██║     ██║          ╚██╗\n"    
         "╚██╗     ██║╚██╔╝██║  ╚██╔╝  ╚════██║██╔══██║██╔══╝  ██║     ██║          ██╔╝\n"    
         " ╚██╗    ██║ ╚═╝ ██║   ██║   ███████║██║  ██║███████╗███████╗███████╗    ██╔╝\n"     
         "  ╚═╝    ╚═╝     ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝    ╚═╝\n\n" RESET);      
                                                                                            

    //REPL - Read Evaluate Print Loop
    // 1) get line
    while(line = myReadLine()) {
        // 2) get tokens
        // lexing -> parsing -> evaluating
        args = splitIntoTokens(line);
        
        // 3) exec
        executeCommand(args);

        // 4) free
        free(line);
        free(args);
    }

    return EXIT_SUCCESS;
}