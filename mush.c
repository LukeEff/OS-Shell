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
    int f = fork();
    if (f == 0) {
      execvp(words[0], words);
      perror("Error: execvp returned a value!");
    }
    else {
      wait(NULL);
    }
  }
  return 0;
}
