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
    printf("a prompt ");
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
            printf("Token: \"%s\"\n", token);
        } while ((token = strtok(NULL, " \t\n\r")) != NULL);
    }
    words[count] = "/0";

    
    printf("\n\n\n");
    for (int i = 0; i < count; i++) {
      printf("%s\n", words[i]);
    }
    
  }
/*
  char buf[2048];
  int count = read(fd, buf, sizeof buf);
  count = write(1, buf, count);
  close(fd);
 */

  return 0;
}
