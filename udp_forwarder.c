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

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 4890

/* main
 * The main entry point of your program */
int main(int argc, char **argv)
{
    if(argc != 6)
    {
        printf("Usage: %s <SOURCE_IP> <SOURCE_PORT> <DESTINATION_IP> <DESTINATION_PORT> <LOSS_RATE>\n", argv[0]);
        return 1;
    }
    
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

    return 0;
}