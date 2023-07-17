#ifndef HTTP_SERV
#define HTTP_SERV

class Server {
private:
  const int PORT = 8080;

public:
  /*
   * Connect to a socker and listen to requests
   *
   */
  int listen();
};

#endif
