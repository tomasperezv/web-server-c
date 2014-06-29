/*
 * configuration.c
 * Handles the access to configuration files
 *
 * @author Tomas Perez <tom@0x101.com>
 */

#include "base.h"
#include "hash_map.h"
#define DELIM "="
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * @method config_key
 */
char *config_key(char *p) {
  char *result = malloc(strlen(p) * sizeof(char));
  int i = 0;
  for (i = 0; i < strlen(p); i++) {
    result[i] = tolower(p[i]);
  }
  return result;
}

/*
 * @method config_get
 */
char *config_get(char *key) {
  struct nlist *port = lookup(key);
  if (port != NULL) {
    return port->defn;
  } else {
    return NULL;
  }
}

/*
 * @method read_config
 */
void read_config(char *filename) {

  FILE *file = fopen (filename, "r");
  if (file != NULL) {
    char current_line[MAX_LEN];

    while(fgets(current_line, sizeof(current_line), file) != NULL) {

      char *key;
      char *value;
      char *pos = strchr(current_line, '#');
      if (pos == NULL && strlen(current_line) > 1) {
        key = strtok(current_line, DELIM);
        key = config_key(key);
        value = strtok(NULL, DELIM);
        install(key, value);
      }

    }

    fclose(file);

  }

}
