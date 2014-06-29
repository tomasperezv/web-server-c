/*
 * configuration.c
 * Handles the access to configuration files
 *
 * @author Tomas Perez <tom@0x101.com>
 */

#include "base.h"
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
