#include "cappuccin.h"
#include "logger.h"

Cappuccin::Cappuccin() {
    logger = new Logger("cappuccin");
}

Cappuccin &Cappuccin::getInstance() {

  // static keyword here is used to ensure that this object is created only
  // once.
  static Cappuccin instance;
  return instance;
}

Server Cappuccin::createApplication() { return Server(logger); }

Route Cappuccin::createRoute() { return Route(logger); }
