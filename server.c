#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* response =
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/plain\n"
        "Content-Length: 13\n\n"
        "Hello, World!";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server running on port 8080...\n");
    while ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)))
    {
        read(new_socket, buffer, 1024);
        write(new_socket, response, strlen(response));
        close(new_socket);
    }

    return 0;
}