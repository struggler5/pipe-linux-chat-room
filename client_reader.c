#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fl = open(FIFO_PATH, O_RDONLY);

    char buffer[100];
    int n;

    while ((n = read(fl, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';
        printf("Received: %s", buffer);
    }

    close(fl);
    return 0;
}

