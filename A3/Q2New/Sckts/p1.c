#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int current_idx;
int main(int argc, char *argv[]) {
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd < 0) {
    printf("Socket Not Found");
    exit(EXIT_FAILURE);
    return 1;
  }
  else{
  struct sockaddr_un server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, "SOCKET", sizeof(server_addr.sun_path) - 1);

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("Connecting ...");
    exit(EXIT_FAILURE);
    return 1;
  }

  char strings[50][5];
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 5; j++) {
      strings[i][j] = 'a' + rand() % 26;
    }
  }

  current_idx = 0;
  while (current_idx < 50) {
    for (int i = 0; i < 5; i++) {
      int idx = current_idx + i;
      send(sockfd, &idx, sizeof(idx), 0);
      send(sockfd, strings[idx], 5, 0);
    }
    int acknowledged_id;
    recv(sockfd, &acknowledged_id, sizeof(acknowledged_id), 0);
    current_idx = acknowledged_id + 1;
  }
  close(sockfd);
  }
  return 0;
}
