#include <iostream>
#include "server.h"
using namespace std;
int main()
{
    Server server;
    cout << server.connect();
    cout << "Hello from tests";
}
