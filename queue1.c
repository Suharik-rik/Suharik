#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LAST_MESSAGE 255

int main() {
	int msgid;
	char pathname[] = "key.ipc";
	key_t key;
	int len, maxlen;

	struct mybuf {
		long mtype;
		char mtext[81];
	} mybuf;

	if ((key = ftok(pathname, 0)) < 0){
		printf("Ne udalos sgenerirovat kluch ipc\n");
		exit(-1);
	}

	if((msgid = msgget(key, 0666| IPC_CREAT)) < 0){
		printf("Ne udalos sozdat ili naiti ochered soobshenii\n");
		exit(-1);
	}
	while(1){
		maxlen = 81;

		if (len = msgrcv(msgid, (struct mybuf*) &mybuf, maxlen, 0, 0) < 0){
			printf("Ne udalos otpravit soobschenie v ochered\n");
			exit(-1);
		}

		if (mybuf.mtype == LAST_MESSAGE){
			msgctl(msgid, IPC_RMID, (struct msqid_ds *)NULL);
			exit(0);
		}
		printf("Tip soobshenia %ld, tekst: %s\n", mybuf.mtype, mybuf.mtext);
	}
	return 0;
}
