#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>
#define MSG_KEY 21 // common for both server and client
/*
msgget creates the message queue with the given MSG_KEY and if it already exists it throws error
qid will we used for reading and writing data to msg queue
*/

/*
******FUNCTION DEFINITIONS******

* int msgget(key_t key, int msgflg);

IPC_PRIVATE: Always creates a new queue, not associated with any specific key, making it accessible only via the returned msgid.
Other Key Values: A new queue is created if no queue exists with the given key, and IPC_CREAT is specified in msgflg. 
Otherwise, it either returns the existing queue's msgid or fails if the queue doesn't exist and IPC_CREAT is not used.

----------------------------

* ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);

msgp -> pointer to message buffer here Logger, it must start with field of type long to store mtype followed by actual mtext
msgsz-> The number of bytes to read from the message text. If the incoming message is larger than msgsz, it will be truncated 
(if MSG_NOERROR is set in msgflg).
msgtyp ->
Scenario 1: msgtyp = 0

The queue has messages with types 2, 4, and 7.
msgrcv will return the first message in the queue (type 2).
Scenario 2: msgtyp = 3

The queue has messages with types 1, 3, and 7.
msgrcv will return the message with type 3.
Scenario 3: msgtyp = -4

The queue has messages with types 1, 3, 4, and 5.
msgrcv will return the message with type 3, because 3 is the lowest type that is less than or equal to 4.

msgflg -> Message Flag Controls the behavior when no message of the desired type is available:
IPC_NOWAIT: If set, the function returns immediately with ENOMSG if no message is available.
If IPC_NOWAIT is not set, the calling process waits until a message is available, the message queue is removed, or a signal is received.

* int msgsnd(int msqid,const void* msgp,size_t msgsz,int msgflg)


*/


int qid =0;

typedef struct Logger
{
    long type;         // standard use long for message type
    char app1MsgTxt[1000];
}Log;

void connects(void)
{
    if((qid=msgget(MSG_KEY,0700|IPC_CREAT))==-1)
    perror("QID");
}
int main(int argc,char* argv[])
{
    Log msgLogger;
    connects();
    while(1)
    {
        if(msgrcv(qid,&msgLogger,sizeof(Log),0,0)==-1)
        continue;

        if(msgLogger.app1MsgTxt[0]!='\0')
        printf("%s\n",msgLogger.app1MsgTxt);
    }
    return 0;
}