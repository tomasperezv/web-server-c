/*
 * server.c
 * Basic web-server.
 *
 * @author Tomas Perez <tom@0x101.com>
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#define FILENAME "bin/config/server.conf"
#define MAX_LEN 256
#define DELIM "="

/*
 * @method read_config
 */
char** read_config(char *filename, char **configuration) {

  int index = 0;

  FILE *file = fopen (filename, "r");
  if (file != NULL) {
    char current_line[MAX_LEN];

    while(fgets(current_line, sizeof(current_line), file) != NULL) {
      char *cfline;
      char *pos = strchr(current_line, '#');
      if (pos == NULL && strlen(current_line) > 1) {
        cfline = strstr((char *)current_line,DELIM);
        cfline = cfline + strlen(DELIM);
        configuration[index] = malloc(MAX_LEN);
        memcpy(configuration[index], cfline, strlen(cfline));
        index++;
      }

    }

    fclose(file);

  }

}

/*
 * @method main
 */
int main(int argc, char *argv[]) {
  char *configuration[255];
  read_config(FILENAME, configuration);
  printf("Hello world %s", configuration[0]);
}
