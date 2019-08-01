 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

int main(int argc, char const *argv[]) { 
    int fd_server; 
    char buffer[1024] = {0};
       
    // Creating socket file descriptor 
    if ((fd_server = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("socket creation failed\n\n"); 
        exit(EXIT_FAILURE); 
    } 
    else{
        printf("Socket created\n\n");
    }
       
    int option = 1; 
    if (setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))) { 
        perror("setsockopt error\n\n"); 
        exit(EXIT_FAILURE); 
    } 
    

    struct sockaddr_in socket_address; 
    int addressLength = sizeof(socket_address); 

    socket_address.sin_family = AF_INET; 
    socket_address.sin_addr.s_addr = INADDR_ANY; 
    socket_address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(fd_server, (struct sockaddr *)&socket_address, sizeof(socket_address))<0) { 
        perror("binding of socket to port failed\n\n"); 
        exit(EXIT_FAILURE); 
    } 
    else{
        printf("Socket bond to the port\n\n");
    }


    if (listen(fd_server, 3) < 0) { 
        perror("Listening failed\n\n"); 
        exit(EXIT_FAILURE); 
    } 
    else{
        printf("Server listening through socket\n\n");
    }

    int socket_server;
    if ((socket_server = accept(fd_server, (struct sockaddr *)&socket_address,(socklen_t*)&addressLength))<0) { 
        perror("acceptance failed\n\n"); 
        exit(EXIT_FAILURE); 
    } 
    else{
        printf("Message accepted from client\n\n");
    }

    int readVal;
    readVal = read( socket_server , buffer, 1024); 
    printf("%s\n",buffer ); 

    char *server_message = "Hello message from server\n";
    send(socket_server , server_message , strlen(server_message) , 0 ); 
    printf("Hello message sent to client\n\n"); 
    return 0; 
} 