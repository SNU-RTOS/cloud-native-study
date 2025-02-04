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
  char buffer[1024] = {0};
  
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  bind(server_fd, (struct sockaddr *)&address, sizeof(address));
  listen(server_fd, 3);

  printf("Server running on port 8080...\n");
  
  while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)))
  {
    read(new_socket, buffer, 1024);
    char *method = strtok(buffer, " "); //GET
    char *path = strtok(NULL, " "); 	// "/"
    
    if(path == NULL){
      path = "/";
    }
    // "/"
    if(strcmp(path, "/") == 0){
      char *response = 
      	  "HTTP/1.1 200 OK\n"
          "Content-Type: text/plain\n"
          "Content-Length: 13\n\n"
          "Hello, World!";
      write(new_socket, response, strlen(response));
    }	
    // 요청된 경로가 /rtos인지 확인
    else if(strcmp(path, "/rtos") == 0) {
      char *response =
          "HTTP/1.1 200 OK\n"
          "Content-Type: text/plain\n"
          "Content-Length: 13\n\n"
          "Hello, RTOS!";
      write(new_socket, response, strlen(response));
    } 
    // param/<param>
    else if(strncmp(path, "/param/", 7) == 0){
      char param[1024];
      strncpyf(param, path + 7, sizeof(param)-1); // param/ 이후 문자열 추출
      param[sizeof(param) - 1] = '\0';

      char response_body[1024];
      snprintf(response_body, sizeof(response_body), "Hello, %s!", param);

      char response[1024];
      snprintf(response , sizeof(response),
	  "HTTP/1.1 200 OK\n"
          "Content-Type: text/plain\n"
          "Content-Length: 13\n\n"
          "%s",
	  strlen(response_body), response_body);
      write(new_socket, response, strlen(response));
    }

    //not found
    else {
      char *not_found =
          "HTTP/1.1 404 Not Found\n"
          "Content-Type: text/plain\n"
          "Content-Length: 9\n\n"
          "Not Found";
      write(new_socket, not_found, strlen(not_found));
    }
    
    close(new_socket);
  }

  return 0;
}

