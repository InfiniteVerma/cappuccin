#ifndef CAPPUCCIN_H
#define CAPPUCCIN_H

#include "server.h"

class Cappuccin {

public:
  /*
   * Returns a Server object
   *
   */
  Server createApplication();

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
