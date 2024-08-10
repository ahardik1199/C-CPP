#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>
#define MSG_KEY 21 // common for both server and client


// struct msqid_ds {
//                struct ipc_perm msg_perm;   /* Ownership and permissions */
//                time_t          msg_stime;  /* Time of last msgsnd(2) */
//                time_t          msg_rtime;  /* Time of last msgrcv(2) */
//                time_t          msg_ctime;  /* Time of creation or last
//                                               modification by msgctl() */
//                unsigned long   msg_cbytes; /* # of bytes in queue */
//                msgqnum_t       msg_qnum;   /* # number of messages in queue */
//                msglen_t        msg_qbytes; /* Maximum # of bytes in queue */
//                pid_t           msg_lspid;  /* PID of last msgsnd(2) */
//                pid_t           msg_lrpid;  /* PID of last msgrcv(2) */
//            };


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
    int rc;
    struct msqid_ds buf; // defined in ipc.h file
    msgLogger.type=1;
    connects();
    int i=0;
    while(1)
    {
        sprintf(msgLogger.app1MsgTxt,"**************** Starting MSG que count %d ******************",i);
        if(msgsnd(qid,(void*)&msgLogger,strlen(msgLogger.app1MsgTxt)+1,IPC_NOWAIT)==-1)
            perror("Logger Message: \n");
        sleep(1);
        rc=msgctl(qid,IPC_STAT,&buf);  //read the statics of message queue
        printf("msg_qbytes %lu msg_qnum %lu \n",buf.msg_qbytes,buf.msg_qnum);
        i++;
    }
    return 0;
}