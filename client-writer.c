#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVER_FIFO "/tmp/chat_server_fifo"
#define MAX_MSG_LEN 512
#define MAX_CLIENT 10

typedef struct {
    pid_t client_pid;
    char text[MAX_MSG_LEN];
} Message;

int main() {
    int server_fd;
    Message msg;
    msg.client_pid = getpid();

    server_fd = open(SERVER_FIFO, O_WRONLY);
    if (server_fd == -1) {
        perror("Server not running");
        return 1;
    }

    printf("Enter your message (write 'exit' to exit):\n");
    while (1) {
        printf("> ");
        fgets(msg.text, MAX_MSG_LEN, stdin);

        if (strncmp(msg.text, "exit", 4) == 0) break;

        write(server_fd, &msg, sizeof(Message));
    }

    close(server_fd);
    return 0;
}
