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
/* main
 * The main entry point of your program */
int main(int argc, char *argv[])
{
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
    
    int sock_fd;
    struct sockaddr_in src_addr, dest_addr;
    char buffer[4096];
    socklen_t addr_len = sizeof(src_addr);

    // Create a soket
    if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Error creating socket");
        exit(1);    
    }
    
    return 0;
}