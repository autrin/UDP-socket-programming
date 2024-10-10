/* udp_forwarder.c
 *
 * Author:
 * Description: Forwards UDP packets from a source to a destination.
 *
 * Usage:
 *   Compile the program:
 *     make
 *   Run it:
 *     ./udp-forwarder <SOURCE_IP> <SOURCE_PORT> <DESTINATION_IP> <DESTINATION_PORT> <LOSS_RATE>
 *   Loss rate is the number of packets out of 1000 that are dropped.
 *
 * Tips:
 *   Check the man pages for any functions you're unsure of. Parameters,
 *   return values, and sometimes even examples are listed!
 *
 *   Check for errors, and abstract logically separate blocks into separate
 *   functions!
 */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>
int sock_fd;

void handle_sigint(int sig) { // check for ctrl + c to close the socket and exit cleanly
    printf("Caught signal %d\n", sig);
    close(sock_fd);
    printf("Socket closed. Exiting...\n");
    exit(0);
}


/* main
 * The main entry point of your program */
int main(int argc, char *argv[])
{
    // Register signal handler
    signal(SIGINT, handle_sigint);
    if(argc != 6)
    {
        printf("Usage: %s <SOURCE_IP> <SOURCE_PORT> <DESTINATION_IP> <DESTINATION_PORT> <LOSS_RATE>\n", argv[0]);
        exit(1);
    }
    char *source_ip = argv[1];
    int source_port = atoi(argv[2]);
    char *dest_ip = argv[3];
    int dest_port = atoi(argv[4]);
    int loss_rate = atoi(argv[5]);

    if (source_port < 1024 || source_port > 65535 || dest_port < 1024 || dest_port > 65535) {
        perror("Invalid port number. Port numbers should be between 1024 and 65535");
        exit(1);
    }
    
    struct sockaddr_in src_addr, dest_addr;
    char buffer[4096];
    socklen_t addr_len = sizeof(src_addr);

    // Create a soket
    if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Error creating socket");
        exit(1);    
    }
        printf("Socket created\n");

    // Configure source address
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.sin_family = AF_INET;
    src_addr.sin_addr.s_addr = inet_addr(source_ip);
    src_addr.sin_port = htons(source_port);

    // Bind socket to the source IP and port
    if(bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr)) < 0){
        perror("Error binding socket");
        close(sock_fd);
        exit(1);
    }
    printf("Socket bound\n");

    // Configure destination address
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(dest_ip);
    dest_addr.sin_port = htons(dest_port);

    srand(time(NULL));

    while(1){
        printf("Waiting for data...\n");
        ssize_t  recv_len = recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&src_addr, &addr_len);
        if(recv_len < 0){
            perror("Error receiving data");
            continue;
        }
        printf("Received %ld bytes\n", recv_len);

        // Determine whether to drop the packet based on the loss rate
        int random_value = rand() % 1000;
        if(random_value < loss_rate){
            printf("Packet dropped (random value: %d)\n", random_value);
            continue;
        }

        if(sendto(sock_fd, buffer, recv_len, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0){
            perror("Error sending data");
        }else{
            printf("Packet forwarded to %s:%d\n", dest_ip, dest_port);
        }
    }

    close(sock_fd);
    return 0;
}