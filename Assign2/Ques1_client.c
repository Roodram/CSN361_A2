
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) { 

    int socket_fd = 0; 
    char buffer[1024] = {0}; 

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        printf("Error while creating socket \n\n"); 
        return -1; 
    } 
    else{
        printf("Connected to socket \n\n");
    }

    struct sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(PORT); 
       
    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr)<=0)  { 
        printf("Address is either not supported or invalid \n\n"); 
        return -1; 
    } 
    else{
        printf("Valid IP address\n\n");
    }
   
    if (connect(socket_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) { 
        printf("Error while connecting to server through socket \n\n"); 
        return -1; 
    } 
    else{
        printf("Server connected through socket\n\n");
    }

    char *client_message = "Hello message from client\n";
    send(socket_fd , client_message , strlen(client_message) , 0 ); 
    printf("Hello message sent to server\n\n"); 

    int readVal;
    readVal = read( socket_fd , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 
} 