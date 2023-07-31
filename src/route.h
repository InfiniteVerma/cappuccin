#ifndef HTTP_ROUTE
#define HTTP_ROUTE

#include <map>
#include <string>

// TODO this is defined multiple places. Make a common_defs.h file
typedef std::string (*FUNCTION)(void);

class Route {

private:
  std::map<std::string, void (*)(void)> routes;

public:
  // TODO pass req, res in params of second arg
  void get(const std::string &path,
           void (*f)(void) /* TODO add controller callback */);

  void prettyPrint();

  // TODO pass custom message?
  static FUNCTION return404();
};

#endif // !HTTP_ROUTE
