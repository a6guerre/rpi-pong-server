#include "RpiPongServer.hpp"

using namespace maxtek;

RpiPongServer::RpiPongServer() : server_fd(-1)
{

}

void RpiPongServer::server_init()
{
    const int PORT = 8080;
    const int BACKLOG = 5;
    struct sockaddr_in server_addr{};

    // Open up socket fd
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        std::cerr << "Socket failed\n";
        return;
    }

    // Bind socket to address and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Bind failed " << strerror(errno) << "\n";
        close(server_fd);
        return;
    }

    if (listen(server_fd, BACKLOG) < 0)
    {
        std::cerr << "Listen failed" << strerror(errno) << "\n";
        close(server_fd);
        return;
    }
}

void RpiPongServer::accept_client_connect()
{
    int client_fd;
    struct sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    while (true)
    {
        std::cout << "Waiting to accept a client connection\n";
        client_fd = accept(server_fd, (struct sockaddr*) &client_addr, &client_len);
        std::cout << "Accepted connection on client fd: " << client_fd << "\n";
        if (client_fd < 0)
        {
            std::cerr << "accept failed " << strerror(errno) << "\n";
            close(server_fd);
            return;
        }
        client_threads.emplace_back([&] { this->client_handler(client_fd); }); 
    }
}

void RpiPongServer::client_handler(int client_fd)
{
    const int MAX_BUF_LEN = 256;
    uint8_t recv_buf[MAX_BUF_LEN];
    ssize_t nbytes;
    std::cout << "Handling client with fd " << client_fd << "\n";
    while (true)
    {
        nbytes = recv(client_fd, recv_buf, sizeof(recv_buf) - 1, 0);
        if (nbytes <= 0)
        {
            std::cerr << "Client disconnect or receive error occured " << strerror(errno) << "\n";
            break;
        }
        std::cout << "Recieved data: " << recv_buf;
    }
    close(client_fd);
}
