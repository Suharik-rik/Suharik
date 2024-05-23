#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
	int *array;
	int shmid;
	int new= 1;
	char pathname[] = "fifo1.c";
	key_t key;
	if((key = ftok(pathname, 0)) < 0){
		printf("Не удалось сгенерировать ip-ключ\n");
		exit(-1);
	}
	if(shmid = shmget(key, 3*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL) < 0) {
		if(errno != EEXIST){
			printf("Не удалось создать сегмент разделяемой памяти\n");
			exit(-1);
		}
		new = 0;
	}
	if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("Не удалось присоеденить сегмент разделяемой памяти к адр. пространству процесса\n");
		exit(-1);
	}
	if(new) {
		array[0] = 1;
		array[1] = 0;
		array[2] = 1;
	}else {
		array[0] += 1;
		array[2] += 1;
	}
	printf("Программа 1 была запущена %d раз(а), общее кол-во запусков обеих программ %d\n", array[0], array[2]);
	if(shmdt(array) < 0) {
		printf("Не удалось создать сегмент разделяемой памяти из адр. пространства текущего процесса\n");
		exit(-1);
	}
	return 0;
}

