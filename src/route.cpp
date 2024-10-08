#include "route.h"
#include "logger.h"
#include <iostream>

#define LOG(x) logger->writeLog(x)

void Route::get(const std::string &path, FUNCTION handler) {
    LOG("Route::get called with path " + path);
    routes.insert({path, handler});
}

std::string Route::execute(Request request, Response response,
        const std::string &path, const std::string &subPath) {
    
    LOG("Route::execute BEGIN " + path + ": subPath :" + subPath + ":");
    // reached here after finding route base url. 
    // Now searching for specific subpath

    for (auto it = routes.begin(); it != routes.end(); ++it) {
        if(it->first == subPath) {
            LOG("Found subpath! " + it->first + ":");

            FUNCTION hlr = it->second;
            return hlr(request, response);
        }
    }

    return "{\"msg\" : \"TODO response!\"}";
}

void Route::prettyPrint() {
    LOG("Printing routes added to this route object");
    int i = 1;
    for (auto it = routes.begin(); it != routes.end(); ++it) {

        //LOG(i << ": " << it->first );
        ++i;
    }
    LOG("-------------------------------------------" );
}

std::string handle404() { return "{\"msg\" : \"Route not found!\"}"; }

std::string Route::return404() { return handle404(); }
