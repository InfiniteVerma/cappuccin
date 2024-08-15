#ifndef HTTP_ROUTE
#define HTTP_ROUTE

#include "request.h"
#include "response.h"
#include <map>
#include <string>
#include "logger.h"

// TODO this is defined multiple places. Make a common_defs.h file
typedef std::string (*FUNCTION)(Request, Response);

class Route {

private:
  std::map<std::string, FUNCTION> routes;
  Logger* logger;

public:
  Route(Logger* log) : logger(log) {}

  // TODO pass req, res in params of second arg
  void get(const std::string &path, FUNCTION handler);

  void prettyPrint();

  // TODO pass custom message?
  static std::string return404();

  std::string execute(Request request, Response response, const std::string &path, const std::string &subPath);
};

#endif // !HTTP_ROUTE
