#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>


int main(int argc, char *argv[]) {
  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (!(sockfd >= 0)) {
    perror("Socket Cannot be Created");
    exit(EXIT_FAILURE);
    return 1;
  }
  else{
  struct sockaddr_un server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, "SOCKET", sizeof(server_addr.sun_path) - 1);
  if (!(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) >= 0)) {
    printf("bind");
    exit(EXIT_FAILURE);
    return 1;
  }
  if (!(listen(sockfd, 5) >= 0)) {
    printf("Listening....");
    exit(EXIT_FAILURE);
    return 1;
  }
  int clientfd = accept(sockfd, NULL, NULL);
  if (!(clientfd >= 0)) {
    perror("Error in Accepting");
    exit(EXIT_FAILURE);
    return 1;
  }
  int count = 0;
  clock_t start_time = clock();
  while (count < 50) {
    int id;
    recv(clientfd, &id, sizeof(id), 0);
    char string[5];
    recv(clientfd, string, 5, 0);
    printf("ID: %d, String: %s\n", id, string);
    count++;
    send(clientfd, &id, sizeof(id), 0);
  }
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);
  close(clientfd);
  close(sockfd);
  }
  return 0;
}
