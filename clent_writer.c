#include<stdio.h> 
#include <sys/stat.h>
#include <unistd.h> 
#include<fcntl.h> 
#include<string.h>

#define FIFO_PATH "/tmp/myfifo"


int main(){
    int fl = open(FIFO_PATH,O_WRONLY); 

    char  message[100];

    while(1){
        printf("Enter message: ");
        fgets(message,sizeof(message), stdin);
        write(fl,message,strlen(message));
    }

    close(fl);
}
