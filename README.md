# UDP Forwarder
## Overview
The UDP Forwarder is a simple program written in C that listens for UDP packets on a specified source IP and port, and forwards them to a destination IP and port. It allows for simulating packet loss, making it a useful tool for testing the behavior of applications under unreliable network conditions.

## Features
Forwards UDP packets from a source to a destination.
Allows specification of packet loss rate to simulate network unreliability.
Displays statistics about forwarded and dropped packets.
Usage
1. Compile the Program
Use make to compile the program:
make

2. Run the UDP Forwarder
Run the UDP forwarder with the following command:
<SOURCE_IP>: IP address from which the program will receive UDP packets.
<SOURCE_PORT>: Port on which the program will listen for UDP packets.
<DESTINATION_IP>: IP address to which the program will forward UDP packets.
<DESTINATION_PORT>: Port to which the program will forward UDP packets.
<LOSS_RATE>: The number of packets out of 1000 that will be dropped to simulate packet loss (e.g., 0 for no loss, 10 for 1% loss).

## Example
./udp_forwarder 127.0.0.1 5000 127.0.0.1 6000 0
This command will forward all packets from 127.0.0.1:5000 to 127.0.0.1:6000 with no packet loss.

3. Streaming Video with VLC (Source)
To stream a video file using VLC to the source port, use the following command:
cvlc --repeat test.mp4 --sout '#standard{access=udp,mux=ts,dst=<SOURCE_IP>:<SOURCE_PORT>}'
Example:
cvlc --repeat test.mp4 --sout '#standard{access=udp,mux=ts,dst=127.0.0.1:5000}'

4. Receiving the Video Stream with VLC (Destination)
On the destination machine, run VLC to receive the forwarded video stream:
vlc -vvv udp://@<DESTINATION_IP>:<DESTINATION_PORT>

Example:
vlc -vvv udp://@127.0.0.1:6000

Requirements
GCC compiler
Linux environment
VLC media player (for testing UDP streaming)
