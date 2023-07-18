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

    // TODO parse request
    Route handler = parseRequest(buffer);

    // call handler function?
    // if (handler == nullptr) {
    //  printf("%s\n", "Route not found!");
    //} else {
    //  handler();
    //}
  }

  return 0;
}

void Server::use(const std::string &path, Route route) {
  std::cout << "Adding a route: " << path << std::endl;

  if (path.size() < 1) {
    std::cout << "Invalid path. Path should be atleast 2 in length? TODO\n";
    return;
  }

  std::string copyPath = path;
  copyPath.erase(0, 1);

  // add it to list
  routes.insert(std::pair<std::string, Route>(copyPath, route));
}

/*
 *
POST /api/users HTTP/1.1
Host: api.example.com
Content-Type: application/json
Authorization: Bearer YOUR_ACCESS_TOKEN

{
  "name": "John Doe",
  "email": "john@example.com",
  "age": 30
}
 *
 */
Route Server::parseRequest(const std::string &request) {
  // search through the route list and return a handler. if not found?
  // search for VERB

  auto it = routes.find(request);
  if (it != routes.end()) {
    return it->second;
  }

  // TODO do something about this
  Route route;
  return route;
}
