#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  while (1) {
    printf("mush$ ");
    char s[2048];
    fgets(s, 2048, stdin);

    if (feof(stdin)) {
      exit(0);
    }

    char* words[128];
    int count = 0;
    char* token;

    if ((token = strtok(s, " \t\n\r")) != NULL) {
        do {
          words[count] = malloc(sizeof(token));
          strcpy(words[count], token);
          count = count + 1;
        } while ((token = strtok(NULL, " \t\n\r")) != NULL);
    }
    words[count] = NULL;
    if (count == 0) continue;
    if (strcmp(words[0], "exit") == 0) {
      if (count == 1) {
        exit(0);
      }
      int value = atoi(words[1]);
      exit(value);
    }

    if (strcmp(words[0], "cd") == 0) {
      if (count != 2) {
        fprintf(stderr, "usage: cd directory\n");
      }
      else {
        int status = chdir(words[1]);
        if (status == -1) {
          perror(words[1]);
        }
      }
      continue;
    }

    int f = fork();
    if (f == 0) {
      execvp(words[0], words);
      perror("Error");
      exit(1);
    }
    wait(NULL);
  }
  return 0;
}


