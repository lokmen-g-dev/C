#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char* argv[]) {
    char input[256];
    char* token;
    char* command[256];
    int i;
    int status;
    int interactive = 1;
    FILE* file;

    if (argc > 1) {
        file = fopen(argv[1], "r");
        interactive = 0;
    }

    while (1) {
 
        if (interactive) {
            printf("%s%% ", getcwd(NULL, 0));
            fgets(input, 256, stdin);
        } else {
            if (fgets(input, 256, file) == NULL) {
                break;
            }
            printf("%s", input);
        }
//    char *buf= input;
  //  if (strlen(buf) != 0) {
    //    add_history(buf);
      ////  strcpy(str, buf);
      //  return 0;
    //} 
        // remove newline character
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0) {
            break;
        }

        // tokenize input
        i = 0;
        token = strtok(input, " ");
        while (token != NULL) {
            command[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        command[i] = NULL;

        // execute command
        pid_t pid = fork();
        if (pid == 0) {
            execvp(command[0], command);
            exit(0);
        } else {
            wait(&status);
        }
    }

    if (!interactive) {
        fclose(file);
    }

    return 0;
}

