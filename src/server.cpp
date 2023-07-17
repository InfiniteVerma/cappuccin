#include "server.h"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int Server::listen() {

  int fd = socket(AF_INET, SOCK_STREAM, 0);

  if (fd == -1) {
    std::cerr << "Could not create socket" << std::endl;
    return -1;
  }

  int opt = 1;

  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    return -1;
  }

  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
  int addrLen = sizeof(addr);

  int rv = bind(fd, (struct sockaddr *)&addr, sizeof(addr));

  if (rv == -1) {
    std::cerr << "Could not bind" << std::endl;
    return -1;
  }

  if (::listen(fd, 5) == -1) {
    std::cerr << "Could not listen" << std::endl;
    return -1;
  }

  while (true) {

    int client_socket =
        accept(fd, (struct sockaddr *)&addr, (socklen_t *)&addrLen);

    if (client_socket == -1) {
      std::cerr << "Could not accept" << std::endl;
      return -1;
    }

    // handle connection
    char buffer[1024] = {0};
    ssize_t valread = read(client_socket, buffer, 1024);
    printf("%s\n", buffer);
  }

  return 0;
}
