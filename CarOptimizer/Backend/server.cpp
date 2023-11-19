// main.cpp
#include "server.h"

int main() {
    // Create a server instance
    Server myServer;  
    // Start the server on port 8080 
    myServer.start(8080);

    return 0;
}
