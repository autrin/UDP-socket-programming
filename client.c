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
    socklen_t server_addr_len = sizeof(server_addr);
    int byte_sent = sendto(sock_fd, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr *)&server_addr, server_addr_len);
    if(byte_sent < 0){
        perror("Error sending message");
        close(sock_fd);
        return 1;
    }
    printf("Sent %d bytes\n", byte_sent);
    printf("Message sent to server: %s\n", MESSAGE);

    char receivedMessage[BUFFER_SIZE];
    ssize_t num_read_bytes = recvfrom(sock_fd, receivedMessage, BUFFER_SIZE - 1, 0, (struct sockaddr *)&server_addr, &server_addr_len);
    if(num_read_bytes < 0){
        perror("Error reading from socket");
        close(sock_fd);
        return 1;
    }
    receivedMessage[num_read_bytes] = '\0';
    printf("Received %ld bytes\n", num_read_bytes);
    printf("Message read from server: %s\n", receivedMessage);
    return 0;
}