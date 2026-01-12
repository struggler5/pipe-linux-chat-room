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
    int server_fd, reader_fd;
    Message msg;
    char my_fifo[MAX_MSG_LEN];

    msg.client_pid = getpid();
    sprintf(my_fifo, "/tmp/client_%d_fifo", msg.client_pid);
    mkfifo(my_fifo, 0666);

    server_fd = open(SERVER_FIFO, O_WRONLY);
    if (server_fd != -1) {
        strcpy(msg.text, "Joined Chat");
        write(server_fd, &msg, sizeof(Message));
        close(server_fd);
    }

    printf("Waiting message (PID: %d)\n", msg.client_pid);

    reader_fd = open(my_fifo, O_RDWR);

    while (read(reader_fd, &msg, sizeof(Message)) > 0) {
        printf("\n[%d]: %s", msg.client_pid, msg.text);
        fflush(stdout);
    }

    close(reader_fd);
    unlink(my_fifo);
    return 0;
}
