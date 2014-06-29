/*
 * server.c
 * Basic web-server.
 *
 * @author Tomas Perez <tom@0x101.com>
 */

#include "base.h"
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

/*
 * @method main
 */
int main(int argc, char *argv[]) {

  read_config(FILENAME);

  int listenfd = 0, connfd = 0;
  struct sockaddr_in serv_addr;

  char sendBuff[1025];
  time_t ticks;

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

  bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  listen(listenfd, 10);

  printf("Server listening on %s", port);

  while(1) {
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    ticks = time(NULL);
    snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
    write(connfd, sendBuff, strlen(sendBuff));

    close(connfd);
    sleep(1);
  }

}
