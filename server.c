#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void send_response(int socket, const char *status, const char *content_type, const char *body) {
    char response[1024];
    snprintf(response, sizeof(response),
             "HTTP/1.1 %s\n"
             "Content-Type: %s\n"
             "Content-Length: %zu\n\n"
             "%s",
             status, content_type, strlen(body), body);
    write(socket, response, strlen(response));
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server running on port 8080...\n");
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen))) {
        read(new_socket, buffer, 1024);

        // Parse the request path
        char *request_line = strtok(buffer, "\n");
        char *path = strtok(request_line, " ");
        path = strtok(NULL, " ");

        if (strcmp(path, "/") == 0) {
            send_response(new_socket, "200 OK", "text/plain", "Hello, World!");
        } else if (strcmp(path, "/rtos") == 0) {
            send_response(new_socket, "200 OK", "text/plain", "Hello, RTOS!");
        } else if (strncmp(path, "/param/", 7) == 0) {
            char param[256];
            snprintf(param, sizeof(param), "Hello, %s", path + 7);
            send_response(new_socket, "200 OK", "text/plain", param);
        } else {
            send_response(new_socket, "404 Not Found", "text/plain", "404 Not Found");
        }

        close(new_socket);
    }

    return 0;
}