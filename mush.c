#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  if (argc == 0)
  {
    return -1;
  }
  while (1) {
    printf("> ");
    char s[2048];
    fgets(s, 2048, stdin);

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

    if (strcmp(words[0], "exit") == 0) {
      exit(0);
    }

    if (strcmp(words[0], "cd") == 0) {
      int status = chdir(words[1]);
      if (status == -1) {
        perror("Error");
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


