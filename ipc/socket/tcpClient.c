#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>  
#include <netinet/in.h>

/*
* int socket(int domain, int type, int protocol);

domain ->   determines protocol family to be used AF_INET for IPv4, AF_INET6 for IPv6, AF_UNIX for local communication
            AF_UNIX/AF_LOCAL: Used for local communication within the same machine.
            AF_INET: Used for IPv4 Internet protocols.
            AF_INET6: Used for IPv6 Internet protocols.
            AF_NETLINK: Used for communication between the kernel and user space.
            AF_BLUETOOTH: Used for Bluetooth communication.

type ->     specifies communication semantics 
            SOCK_STREAM: Provides reliable, two-way, connection-based byte streams (e.g., TCP).
            SOCK_DGRAM: Supports datagrams (connectionless, unreliable messages, e.g., UDP).
            SOCK_SEQPACKET: Similar to SOCK_STREAM, but preserves message boundaries.
            SOCK_RAW: Provides direct access to lower-level protocols (e.g., ICMP).

protocol -> Specifies a particular protocol to use with the socket. Typically, this is
            set to 0, which selects the default protocol for the given domain and type.
  
*/

// struct sockaddr_in {
//         sa_family_t     sin_family;     /* AF_INET */
//         in_port_t       sin_port;       /* Port number */
//         struct in_addr  sin_addr;       /* IPv4 address */
//     };        

int main() {

    int network_socket; //create a socket
    network_socket= socket(AF_INET,SOCK_STREAM,0);
    //now our socket need another end point to connect with

    //specify an address to socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY; //connect to 0.0.0.0

    int connection_status = connect(network_socket,(struct sockaddr *) &server_address,sizeof(server_address));
    //check for error with connection
    if(connection_status==-1){
        printf("There was an error making a connection to remote socket \n\n");
    }

    //receive data from server
    char server_response[256];
    recv(network_socket,&server_response,sizeof(server_response),0);

    //print out server's response
    printf("the server sent the data: %s\n",server_response);

    //close the socket
    close(network_socket);
    return 0;
}