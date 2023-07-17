#include "server.h"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int Server::connect() {

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

  if (listen(fd, 5) == -1) {
    std::cerr << "Could not listen" << std::endl;
    return -1;
  }

  if (accept(fd, (struct sockaddr *)&addr, (socklen_t *)&addrLen) == -1) {
    std::cerr << "Could not accept" << std::endl;
    return -1;
  }

  return 0;
}
