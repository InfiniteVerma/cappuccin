#ifndef CAPPUCCIN_H
#define CAPPUCCIN_H

#include "server.h"
#include "route.h"

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

  static Cappuccin &getInstance();

  /*
   * Deleting the copy constructor and assignment operator to prevent copying
   *
   */
  Cappuccin(const Cappuccin &) = delete;
  Cappuccin &operator=(const Cappuccin &) = delete;

private:

  /*
   * Making constructor private to make this a singleton class
   */
  Cappuccin();
};

#endif /* CAPPUCCIN_H */
