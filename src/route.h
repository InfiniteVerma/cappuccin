#ifndef HTTP_ROUTE
#define HTTP_ROUTE

#include <string>

class Route {

private:
public:
  void get(const std::string &path /* TODO add controller callback */);
};

#endif // !HTTP_ROUTE
