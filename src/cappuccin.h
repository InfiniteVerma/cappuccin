#ifndef CAPPUCCIN_H
#define CAPPUCCIN_H

#include "route.h"
#include "server.h"
#include "request.h"
#include "response.h"
#include "logger.h"

class Cappuccin {

public:
  /*
   * Returns a Server object
   *
   */
  Server createApplication();

  /*
   * Creates and returns a router object
   *
   */
  Route createRoute();

  /*
   * Returns Cappuccin object.
   */
  static Cappuccin &getInstance();

  /*
   * Deleting the copy constructor and assignment operator to keep it a
   * singleton class
   *
   */
  Cappuccin(const Cappuccin &) = delete;
  Cappuccin &operator=(const Cappuccin &) = delete;

private:
  /*
   * Making constructor private to make this a singleton class
   */
  Cappuccin();

  Logger* logger;
};

#endif /* CAPPUCCIN_H */
