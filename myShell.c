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

int checkAddRedirection(char **args) {
    int redirectType = -1; // -1: none, 0: input, 1: output, 2: stderr

    for(int i = 0;args[i]; i++) {
        if(strcmp(args[i], "<") == 0) {
            redirectType = 0;
            args[i] = NULL;
            int file = open(args[i + 1], O_RDONLY, 0777);
            dup2(file, STDIN_FILENO);
            close(file);
            break;
        }
        else if(strcmp(args[i], ">") == 0) {
            redirectType = 1;
            args[i] = NULL;
            int file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
            dup2(file, STDOUT_FILENO);
            close(file);
            break;
        }
        else if(strcmp(args[i], ">>") == 0) {
            redirectType = 2;
            args[i] = NULL;
            int file = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
            dup2(file, STDOUT_FILENO);
            close(file);
            break;
        }
    }

    return redirectType;
}

void executeCommand(char **args) {
    //For I/O Redirects
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDIN_FILENO);

    int redirectType = checkAddRedirection(args);

    char *cur;
    int i = 0;

    while(cur = arrayBuiltin[i].builtin_name) {
        if(strcmp(cur, args[0]) == 0) {
            (arrayBuiltin[i].ptr)(args);
            
            dup2(saved_stdin, STDIN_FILENO);
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdin);
            close(saved_stdout);
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
    else {
        wait(&status);
        dup2(saved_stdin, STDIN_FILENO);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdin);
        close(saved_stdout);
    }
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

    char cwd[512];
    if(getcwd(cwd, sizeof(cwd)) == NULL) {
        perror(RED "getcwd Failed\n" RESET);
    }

    char prompt[1024];
    snprintf(prompt, sizeof(prompt), "%s☣️ %s>%s", CYAN, cwd, RESET);

    buff = readline(prompt);

    if(buff && *buff) {
        add_history(buff);
    }

    if(buff == NULL) {
        printf(RED"End Of File (or) Error Occurred\n"RESET); 
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