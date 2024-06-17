#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int semid;
	char pathname[] = "key.ipc";
	key_t key;
	struct sembuf mybuf;

	if((key = ftok(pathname, 0)) < 0){
		printf("Ne udalos sozdat kluch\n");
		exit(-1);
	}

	if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
		printf("Ne udalos poluchit deskriptor semaforov\n");
		exit(-1);
	}

	mybuf.sem_op = -1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;
	if(semop(semid, &mybuf, 1) < 0){
		printf("Ne udalos vipolnit operaciyu nad semaforom\n");
		exit(-1);
	}
	printf("Uslovie razblokirovki processa viyavleno\n");
	return 0;
}
