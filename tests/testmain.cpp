#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <thread>
#include <unistd.h>

// library header files
#include "cappuccin.h"

using namespace std;

void dummyClient();
void runServer();

// Controllers
std::string getData(Request request, Response response) 
{ 
    //response.setStatusCode(200);
    //response.setHeader("Content-Type", "text/html");
    //response.setJson("{\"message\": \"Hello World\"}");
    //response.send();
    return "TODO getData";
}

std::string getDataAsdf(Request request, Response response) 
{ 
    //response.setStatusCode(200);
    //response.setHeader("Content-Type", "text/html");
    //response.setJson("{\"message\": \"Hello World\"}");
    //response.send();
    return "New response!";
}
// ------------------

Route testRoutes() {
  // TODO library calls to generate response in a good way

  Route route = Cappuccin::getInstance().createRoute();

  route.get("/", getData);
  route.get("/asdf", getDataAsdf);

  return route;
}

int main() {
  std::thread server(runServer);
  std::thread client(dummyClient);

  server.join();
  client.join();
}

void runServer() {
  std::cout << "Starting server\n";

  // create server object
  Server server = Cappuccin::getInstance().createApplication();

  // add routes
  server.use("/hello", testRoutes());

  cout << server.listen();
}

void dummyClient() {
  std::cout << "Start client\n";

  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    std::cerr << "Error creating socket." << std::endl;
    return;
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

  if (connect(client_socket, (struct sockaddr *)&server_address,
              sizeof(server_address)) == -1) {
    std::cerr << "Error connecting to the server." << std::endl;
    close(client_socket);
    return;
  }

  const char *message = "GET /hello HTTP/1.1\r\n"
                        "Host: www.example.com\r\n"
                        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; "
                        "x64) AppleWebKit/537.36 (KHTML, like Gecko) "
                        "Chrome/58.0.3029.110 Safari/537.36\r\n"
                        "Accept: text/html,application/xhtml+xml\r\n";

  int message_len = strlen(message);
  int bytes_sent = send(client_socket, message, message_len, 0);

  if (bytes_sent == -1) {
    std::cerr << "Error sending data to the server." << std::endl;
  } else {
    std::cout << "Sent " << bytes_sent << " bytes to the server." << std::endl;
  }

  std::cout << "DONE" << std::endl;

  close(client_socket);
}
