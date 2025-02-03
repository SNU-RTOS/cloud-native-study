#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, sizeof(buffer));

    // 요청된 경로 추출
    char method[BUFFER_SIZE], path[BUFFER_SIZE], protocol[BUFFER_SIZE];
    sscanf(buffer, "%s %s %s", method, path, protocol);

    // 응답 메시지
    char response[BUFFER_SIZE];

    if (strcmp(path, "/") == 0) {
        snprintf(response, sizeof(response),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/plain\r\n"
                 "Content-Length: 13\r\n"
                 "\r\n"
                 "Hello, World!");
    } else if (strcmp(path, "/rtos") == 0) {
        snprintf(response, sizeof(response),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/plain\r\n"
                 "Content-Length: 12\r\n"
                 "\r\n"
                 "Hello, RTOS!");
    } else if (strncmp(path, "/param/", 7) == 0) {
        char param[BUFFER_SIZE];
        sscanf(path + 7, "%s", param);  // "/param/" 이후 문자열 추출
        snprintf(response, sizeof(response),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/plain\r\n"
                 "Content-Length: %ld\r\n"
                 "\r\n"
                 "Hello, %s!",
                 strlen(param) + 8, param);
    } else {
        // **4번 기능: 404 Not Found 응답 추가**
        snprintf(response, sizeof(response),
                 "HTTP/1.1 404 Not Found\r\n"
                 "Content-Type: text/plain\r\n"
                 "Content-Length: 13\r\n"
                 "\r\n"
                 "404 Not Found");
    }

    // 클라이언트에게 응답 전송
    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    // 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 소켓 바인딩
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(1);
    }

    // 클라이언트 연결 대기
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server running on http://127.0.0.1:%d\n", PORT);

    // 클라이언트 요청 처리
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }
        handle_request(client_socket);
    }

    close(server_socket);
    return 0;
}


