#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
mkfifo(FIFO_PATH, 0666);

    printf("Server running. \nPress Ctrl+C to exit.\n");

    while (1){

        sleep(1);
    }

    unlink(FIFO_PATH);
    return 0;
}

