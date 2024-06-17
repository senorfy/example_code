#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>

extern int errno;
#define MSGID 0x1234

struct mymsgbuf{
    long mtype;
    char ctext[100];
};
int main(){
    struct mymsgbuf buf;
    int msgid;    
    int ret;
    if((msgid = msgget(MSGID, 0666 | IPC_CREAT)) < 0)    {
        fprintf(stderr, "open msg %X failed.\n", MSGID);
        return -1;
    }
    while(strncmp(buf.ctext, "exit", 4))    
    {
        memset(&buf, 0, sizeof(buf));
        while((ret = msgrcv(msgid, &buf, sizeof(buf.ctext), buf.mtype, 0)) < 0)
        {
            if(errno == EINTR)    
                continue;
            return -1;        
        }        
        fprintf(stderr,"Msg:Type=%ld, Len=%d, Text:%s \n",buf.mtype,ret, buf.ctext);
    }
    return 0;
}
