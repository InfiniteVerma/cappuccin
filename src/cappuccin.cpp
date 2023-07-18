#include "cappuccin.h"

Cappuccin::Cappuccin() {
    
}

Cappuccin &Cappuccin::getInstance() {

  // static keyword here is used to ensure that this object is created only
  // once.
  static Cappuccin instance;
  return instance;
}

Server Cappuccin::createApplication() { return Server(); }

Route Cappuccin::createRoute() { return Route(); }
