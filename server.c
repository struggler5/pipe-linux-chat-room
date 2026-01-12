#include <stdio.h>
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
    int server_fd, client_fd;
    Message msg;
    pid_t clients[MAX_CLIENT];
    int client_count = 0;

    mkfifo(SERVER_FIFO, 0666);
    server_fd = open(SERVER_FIFO, O_RDWR);
    printf("Server Started\n");

    while (read(server_fd, &msg, sizeof(Message)) > 0) {
        int exists = 0;
        for (int i = 0; i < client_count; i++) {
            if (clients[i] == msg.client_pid) exists = 1;
        }

        if (!exists && client_count < MAX_CLIENT) {
            clients[client_count++] = msg.client_pid;
            printf("New Client Added: %d\n", msg.client_pid);
        }

        char client_fifo[MAX_MSG_LEN];
        for (int i = 0; i < client_count; i++) {
            sprintf(client_fifo, "/tmp/client_%d_fifo", clients[i]);
            client_fd = open(client_fifo, O_WRONLY | O_NONBLOCK);
            if (client_fd != -1) {
                write(client_fd, &msg, sizeof(Message));
                close(client_fd);
            }
        }
    }

    close(server_fd);
    unlink(SERVER_FIFO);
    return 0;
}
