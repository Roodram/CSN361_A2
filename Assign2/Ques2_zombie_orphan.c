// #include <bits/stdc++.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h> 
int main() 
{ 
 printf("Parent process pid = %d \n", getpid());       
    
    if (fork() == 0) 
    {   
        printf("Child process id = %d\nChild of parent process id = %d \n", getpid(), getppid());
        
        printf("Creating a grandchild to demonstrate zombie process\n\n");
        if (fork() > 0) {
            printf("(Grandchild) Parent process pid = %d \n", getpid()); 
            sleep(8); 
            printf("(Grandchild) Parent resumes but child terminnated while it was in sleep\nSo GrandChild is a zombie\n");
        }
        else{
            sleep(3);
            printf("GrandChild process id = %d\nChild of parent process id = %d \n", getpid(), getppid());       
            printf("GrandChild exits\n\n");
            exit(0); 
        }
         

        sleep(5); 
        printf("Now child is an Orphan \n");
        printf("Child process id = %d\nChild of parent process id = %d", getpid(), getppid());
    }
    sleep(8);
    return 0;
     
    
} 
