#ifndef HTTP_SERV
#define HTTP_SERV

#include <string>
#include <map>

typedef void (*routeHandler)();

class Server {
private:
  const int PORT = 8080;
  std::map<std::string, routeHandler> routes;

public:
  /*
   * Connect to a socker and listen to requests
   *
   */
  int listen();

  /*
   * Add a route
   *
   */
  void addRoute(const std::string &path, routeHandler handler);

  /*
   * Parse a new request. 
   * Input: Whole request as a string
   * Output: routeHandler
   *
   */
  routeHandler parseRequest(const std::string &request);
};

#endif
