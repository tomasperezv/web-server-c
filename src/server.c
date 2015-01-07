/*
 * server.c
 * Basic web-server.
 *
 * @author Tomas Perez <tom@0x101.com>
 */

#include "base.h"
#include "server.h"
#include "hash_map.h"
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
#include <unistd.h>
#include <signal.h>

int listenfd;

/*
 * @method interruption_handler
 */
void interruption_handler(int signal) {
  shutdown(listenfd, 2);
  exit(1);
}

/*
 * @method main
 */
int main(int argc, char *argv[]) {

  read_config(FILENAME);

  int connfd = 0;
  struct sockaddr_in serv_addr;

  char sendBuff[1025];

  signal(SIGINT, interruption_handler);

  char *port = config_get("port");
  if (port == NULL) {
    printf("Error: Invalid port number, check the configuration");
    exit(1);
  }

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(port));

  if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
    close(listenfd);
    return -1;
  }

  listen(listenfd, 10);

  printf("Server listening on %s", port);

  while(1) {
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    int i;
    char buffer[2048];
    read(connfd, buffer, 2048);

    char current_line[MAX_LEN];
    for (i = 0; i < 5; i++) {
      write(connfd, connection_headers[i], strlen(connection_headers[i]));
    }

    FILE *file = fopen ("www/404.html", "r");
    if (file != NULL) {
      while(fgets(current_line, sizeof(current_line), file) != NULL) {
        write(connfd, current_line, strlen(current_line));
      }
    }

    fclose(file);
    close(connfd);
    sleep(1);
  }

  close(listenfd);

}
