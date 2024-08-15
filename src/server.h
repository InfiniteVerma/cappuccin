#ifndef HTTP_SERV
#define HTTP_SERV

#include <string>
#include <map>
#include "route.h"
#include "logger.h"

// typedef void (*routeHandler)(); TODO move this somewhere else?
typedef std::string (*FUNCTION)(Request, Response);

class Server {
private:
  const int PORT = 8080;
  Logger* logger;

  /*
   * Holds all the registered routes with their route handlers
   */
  std::map<std::string, Route> routes;

public:
  /*
   * Connect to a socket and listen to requests
   *
   */
  int listen();

  Server(Logger* log) : logger(log) {}

  /*
   * Add a route // TODO update this comment
   *
   */
  void use(const std::string &path, Route route);

  /*
   * Parse a new request. 
   * Input: Whole request as a string
   * Output: routeHandler
   *
   */
  std::string parseRequestAndRespond(const std::string &request);
};

#endif
