#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define CHAR_MAX_LENGTH                 1024
#define CHAR_PATH_PARAMETER_END         "HTTP"
#define CHAR_PATH_PARAMETER_NONE        "GET / "
#define CHAR_PATH_PARAMETER_RTOS        "GET /rtos "
#define CHAR_PATH_PARAMETER_PARAM       "GET /param/"
#define CHAR_OUTPUT_NONE                "Hello, World!"
#define CHAR_OUTPUT_RTOS                "Hello, RTOS!!"
#define CHAR_OUTPUT_NOT_FOUND           "404 Not Found!"

typedef enum
{
    CHAR_PATH_NONE              = 0,
    CHAR_PATH_DEFAULT           = 1,
    CHAR_PATH_RTOS              = 2,
    CHAR_PATH_PARAM             = 3,
    CHAR_PATH_NOT_FOUND         = 4,

}   CHAR_PATH_TYPE_E;

int GetPath(char* pBuffer, char* pPath);
int MakeResponse(int iCheckPath, char* pPath);

char ResponseBody[CHAR_MAX_LENGTH];
char* ResponseHeader =
"HTTP/1.1 200 OK\n"
"Content-Type: text/plain\n"
"Content-Length: 13\n\n";


int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char pPath[CHAR_MAX_LENGTH];
    char buffer[CHAR_MAX_LENGTH] = { 0 };
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
        read(new_socket, buffer, CHAR_MAX_LENGTH);
        MakeResponse(GetPath(buffer, pPath), pPath);
        write(new_socket, ResponseBody, strlen(ResponseBody));
        close(new_socket);
        //printf("Path Result %d \n", iResult);
    }

    return 0;
}

int GetPath(char* pBuffer, char* pPath)
{
    char* pPathParam;
    char* pPathParamEnd;
    char  aPathBase[CHAR_MAX_LENGTH];
    char  aPath[CHAR_MAX_LENGTH];

    if (NULL != strstr(pBuffer, CHAR_PATH_PARAMETER_NONE))
    {
        return CHAR_PATH_DEFAULT;
    }
    else if (NULL != strstr(pBuffer, CHAR_PATH_PARAMETER_RTOS))
    {
        return CHAR_PATH_RTOS;
    }
    else if (NULL != strstr(pBuffer, CHAR_PATH_PARAMETER_PARAM))
    {
        pPathParam = strstr(pBuffer, CHAR_PATH_PARAMETER_PARAM);
        strcpy(aPathBase, (pPathParam + strlen(CHAR_PATH_PARAMETER_PARAM)));
        pPathParamEnd = strstr(pPathParam, CHAR_PATH_PARAMETER_END);
        strncpy(pPath, aPathBase, ((pPathParamEnd - 1) - aPathBase));
        return CHAR_PATH_PARAM;
    }
    else
    {
        return CHAR_PATH_NOT_FOUND;
    }

    return CHAR_PATH_NONE;
}

int MakeResponse(int iCheckPath, char* pPath)
{

    switch (iCheckPath)

    {
    case CHAR_PATH_DEFAULT:
        snprintf(ResponseBody, CHAR_MAX_LENGTH, "%s%s", ResponseHeader, CHAR_OUTPUT_NONE);
        break;

    case CHAR_PATH_RTOS:
        snprintf(ResponseBody, CHAR_MAX_LENGTH, "%s%s", ResponseHeader, CHAR_OUTPUT_RTOS);
        break;

    case CHAR_PATH_PARAM:
        snprintf(ResponseBody, CHAR_MAX_LENGTH, "%s%s", ResponseHeader, pPath);
        break;

    case CHAR_PATH_NOT_FOUND:
    default:
        snprintf(ResponseBody, CHAR_MAX_LENGTH, "%s%s", ResponseHeader, CHAR_OUTPUT_NOT_FOUND);
        break;
    }

    printf("result : %d, %s \n", iCheckPath, ResponseBody);
    return 0;
}