#ifndef RPI_PONG_SERVER_HPP
#define RPI_PONG_SERVER_HPP

#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "pongdata_generated.h"

namespace maxtek
{
    class RpiPongServer
    {
        public:
            RpiPongServer();
            void server_init();
            void accept_client_connect();
            void client_handler(int client_fd);
        private:
            int server_fd;
            std::vector<std::thread> client_threads;
    };
}

#endif
