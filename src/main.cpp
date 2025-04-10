#include "RpiPongServer.hpp"

using namespace maxtek;

int main(void)
{
    RpiPongServer pongServer;
    pongServer.server_init();
    pongServer.accept_client_connect();
    return 0;
}
