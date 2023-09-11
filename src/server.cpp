#include "server.h"
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
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

  // use select/poll
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

    // parse the request
    // 1. VERB
    // 2. path
    // 3. body
    // 4. other stuff
    std::string response = parseRequestAndRespond(buffer);

    std::cout << "Server::listen sending response: " << response << std::endl;

    char responseBuffer[1024] = {0};
    std::string responseFirst = "HTTP/1.1 200 OK\r\n"
                                "Content-Type: application/json\r\n\r\n";

    std::string finalResponse = responseFirst + response;

    strcpy(responseBuffer, finalResponse.c_str());

    std::cout << "Server::listen sendingResponse: " << responseBuffer
              << std::endl;

    std::cout << "Server::listen processed request" << std::endl;

    ssize_t valsend =
        send(client_socket, responseBuffer, finalResponse.length(), 0);

    close(client_socket); // Close the client socket after sending the response
  }

  return 0;
}

void Server::use(const std::string &path, Route route) {

  std::cout << "Server::use BEGIN path: " << path << std::endl;

  if (path.size() < 1) {
    std::cout << "Invalid path. Path should be atleast 2 in length? TODO THROW "
                 "ERROR?\n";
    return;
  }

  std::string copyPath = path;
  copyPath.erase(0, 1);

  std::cout << "Adding route: " << copyPath << std::endl;
  std::cout << "This has below controllers: " << std::endl;

  route.prettyPrint();

  // add it to list
  routes.insert(std::pair<std::string, Route>(copyPath, route));

  std::cout << "Server::use END" << std::endl;
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
std::string Server::parseRequestAndRespond(const std::string &request) {

  // search through the route list and return a handler. TODO if not found?
  // search for VERB
  std::string tempRequest = request;
  bool isGet = false; // TODO make this enum

  // TODO very unoptimised currently
  // GET/POST/PUT/DELETE/PATCH

  if (request.size() < 1) {
    return Route::return404();
  }

  if (request[0] == 'G') {
    // TODO match entire GET first
    std::cout << "Considering it a get request" << std::endl;

    // consume "GET "
    if (request.length() > 4) {
      tempRequest = tempRequest.substr(4);
    } else {
      return Route::return404();
    }

    isGet = true;

  } else if (request[0] == 'P' && request[1] == 'O') {
    std::cout << "Considering it a port request" << std::endl;
  } else if (request[0] == 'P' && request[1] == 'U') {
    std::cout << "Considering it a put request" << std::endl;
  } else if (request[0] == 'D') {
    std::cout << "Considering it a delete request" << std::endl;
  } else {
    std::cout << "Considering it a patch request" << std::endl;
  }

  std::cout << "Finding request: " << tempRequest << std::endl;

  // Next, getting path from the request

  // removing the slash in the beginning
  tempRequest = tempRequest.substr(1);

  size_t spacePos = tempRequest.find(" ");
  size_t nextSlashPos = tempRequest.find("/");
  std::string routePath = "";
  std::string subPath = ""; // contains the rest of the path

  // if it's a nested path: /hello/asdf or /hello/olala, we need to search till first / only
  // if there's a / before a space, get till before that string
  if(nextSlashPos != std::string::npos && nextSlashPos < spacePos) {

      std::cout << "has a slash" << std::endl;
      routePath = tempRequest.substr(0, nextSlashPos);
      subPath = tempRequest.substr(nextSlashPos, spacePos);
  }
  else if (spacePos != std::string::npos) {

    std::cout << "Without a slash!" << std::endl;
    routePath = tempRequest.substr(0, spacePos);
  } else {
    std::cout << "ERR: INVALID REQUEST TODO" << std::endl;
    return Route::return404();
  }

  // Finding path from registered routes

  auto it = routes.find(routePath); // TODO this should search till first /
  std::cout << "Searching for routePath :" << routePath << ": subPath :" << subPath << ":" << std::endl;

  std::cout << "\nExisting routes:\n";
  for(auto temp : routes) {
      std::cout << temp.first << "\n";
  }
  std::cout << "\n\n";
  if (it != routes.end()) {

    // Found route. Now returning it's routeHandler
    std::cout << "Found route!" << std::endl;

    // TODO pass the body to the routeHandler which will give me the std::string
    // response
    Route route = it->second;
    // TODO fix below
    Request request;
    Response response;
    std::string resp = route.execute(request, response, routePath, subPath);
    std::cout << "Returning response " << std::endl;
    return resp;
  } else {

    // Not found path. Returning 404 response
    std::cout << "Not found it->second" << std::endl;
  }

  // TODO do something about this
  return Route::return404();
}
