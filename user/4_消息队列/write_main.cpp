#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>
#include <unistd.h>

extern int errno;
#define MSGID 0x1234

struct mymsgbuf{
	long mtype;
	char ctext[100];
};
int main(){
	struct mymsgbuf buf;    
	int msgid;
	if((msgid = msgget(MSGID, 0666 | IPC_CREAT)) < 0)    
	{
		fprintf(stderr, "open msg %x failed.\n", 0x1234);
		return -1;
	}
	while(strncmp(buf.ctext, "exit", 4))    
	{
		memset(&buf, 0, sizeof(buf));
		fgets(buf.ctext, sizeof(buf.ctext), stdin);
		buf.mtype = getpid();

		while((msgsnd(msgid, &buf, strlen(buf.ctext),0)) < 0)
		{
			if(errno == EINTR)
				continue;
			return -1;        
		}
	}
	return 0;
}
