#include "MessageQueue.h"

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>

MessageQueue::MessageQueue(key_t key) {
    id = msgget(key, 0777| IPC_CREAT);
}

void MessageQueue::destroy() {
    msgctl(id, IPC_RMID, NULL);
}

int MessageQueue::push(EntryData* data) {
    return msgsnd(id, data, sizeof(EntryData) - sizeof(long), 0);
}

EntryData MessageQueue::pop() {
    EntryData data;
    msgrcv(id, &data, sizeof(EntryData) - sizeof(long), 0, 0);
    return data;
}