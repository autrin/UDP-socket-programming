#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4890
#define BUFFER_SIZE 4096
#define MESSAGE "Hello from client!"

int main(int argc, char* argv[]){
    int sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0){
        perror("Error creating socket");
        return 1;
    }
    printf("Socket created\n");
    // Build the socket address for the server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    int byte_sent = sendto(sock_fd, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(byte_sent < 0){
        perror("Error sending message");
        close(sock_fd);
        return 1;
    }
    printf("Sent %d bytes\n", byte_sent);
    return 0;
}