#include "route.h"
#include <iostream>

void Route::get(const std::string &path, void (*f)(void)) {
  std::cout << "Route::get called with path " << path << std::endl;
  routes.insert({path, f});
}

void Route::prettyPrint() {
  std::cout << "Printing routes added to this route object: \n";
  int i = 1;
  for (auto it = routes.begin(); it != routes.end(); ++it) {

    std::cout << i << ": " << it->first << std::endl;
    ++i;
  }
  std::cout << "-------------------------------------------" << std::endl;
}

std::string handle404() { return "{\"msg\" : \"Route not found!\"}"; }

FUNCTION Route::return404() { return handle404; }
