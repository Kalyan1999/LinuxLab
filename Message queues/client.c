#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define true (1)
#define false (0)
#define BUFFER_SIZE (1024)

typedef struct {
    long msg_type;
    char msg_text[BUFFER_SIZE];
} message;

int main(int argc, char* argv[]) {
    key_t key;
    int msg_id;

    printf("Client Program.\nType \".exit\" to exit.\n\n");

    if((key = ftok("server.c", 69)) < 0) {
        printf("Error creating key using ftok(). Exiting...\n");
        return -1;
    }

    if((msg_id = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Error getting message queue using msgget(). Exiting...\n");
        return -1;
    }

    message msg;
    while(true) {
        msgrcv(msg_id, &msg, sizeof(msg) - sizeof(msg.msg_type), 1, 0);
        printf("Server: %s\n", msg.msg_text);
        if(strcmp(msg.msg_text, ".exit") == 0) break;

        printf("> ");
        scanf("%1000[^\n]%*c", msg.msg_text);
        msg.msg_type = 2;
        msgsnd(msg_id, &msg, sizeof(msg) - sizeof(msg.msg_type), 0);
        if(strcmp(msg.msg_text, ".exit") == 0) break;
    }

    return 0;
}
