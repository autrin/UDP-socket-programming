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
    // the ports should be between 1024 and 65535
    int source_ip = inet_addr(argv[1]);
    int source_port = atoi(argv[2]);
    int destination_ip = inet_addr(argv[3]);
    int destination_port = atoi(argv[4]);
    int loss_rate = atoi(argv[5]); // number of the packets out of 1000 that are intentionally dropped (not forwarded)
    
    if(source_port  < 1024 || destination_port < 1024 || source_port > 65535 || destination_port > 65535){
        perror("Invalid port number. Port number should be between 1024 and 65535");
        exit(1);
    }

    
    return 0;
}