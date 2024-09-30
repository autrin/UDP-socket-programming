#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 4890
#define BUFFER_SIZE 4096
#define MESSAGE "Hello from server! I received your message."
/* main
 * The main entry point of your program */
int main(int argc, char *argv[])
{
    int sock_fd = socket(PF_INET, SOCK_DGRAM, 0); // create a datagram socket (udp)
    if(sock_fd < 0)
    {
        perror("Error creating socket");
        return 1;
    }
    printf("Socket created\n");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if(bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){ // Tell the os that any packet coming to this port should be sent to the server socket's buffer
        perror("Error binding socket");
        close(sock_fd);
        exit(1);
    }
    printf("Socket bound\n");

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char receivedMessage[BUFFER_SIZE];
    char sentMessage[BUFFER_SIZE];
    ssize_t num_read_bytes;
    while(1){
        num_read_bytes = recvfrom(sock_fd, receivedMessage, BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_addr, &client_addr_len);
        if(num_read_bytes < 0){
            perror("Error reading from socket");
            close(sock_fd);
            exit(1);
        }
        printf("Received %ld bytes\n", num_read_bytes);
        receivedMessage[num_read_bytes] = '\0';
        printf("Message read from client: %s\n", receivedMessage);
        
        ssize_t num_sent_bytes = sendto(sock_fd, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr*)&client_addr, client_addr_len);
        if(num_sent_bytes < 0){
            perror("Error sending to socket");
            close(sock_fd);
            exit(1);
        }
        printf("Sent %ld bytes\n", num_sent_bytes);
        printf("Message sent to client: %s\n", MESSAGE);
    }
    return 0;
}