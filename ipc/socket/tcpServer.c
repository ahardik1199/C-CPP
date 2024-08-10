#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>  
#include <netinet/in.h>

int main(){
    char server_message[256]="You received msg from server";

    //create the server_socket
    int server_socket;
    server_socket=socket(AF_INET,SOCK_STREAM,0);

    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY; //connect to 0.0.0.0 (any ip address on local machine)

    //bind the socket to out specified IP and port
    bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));

    //listen to connections
    listen(server_socket,5); // TODO read more about this 5 is backlog how many clients are waiting for socket connection 

    //accept connection
    int client_socket;
    client_socket = accept(server_socket,NULL,NULL); //TODO read more about NULL they are for client socket address

    //send message 
    send(client_socket,server_message,sizeof(server_message),0);

    //close socket
    close(server_socket);
    return 0;
}