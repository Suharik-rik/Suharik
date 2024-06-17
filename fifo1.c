#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main () {
	int fd, result;
	size_t size;
	char string[] = "gr.3.008.2.23", resstring[13];
	char name[] = "fifo.fifo";

	if (mknod(name, S_IFIFO | 0666, 0) < 0) {
		printf("Ne udalos sozdat sredstvo fifo\n");
		exit(-1);
	}
	if((result = fork()) < 0) {
		printf("Ne udalos sozdat dochernii process\n");
		exit(-1);
	} else if(result > 0){
		if ((fd = open(name, O_WRONLY)) < 0){
			printf("Ne udalos otkit fifo dlya zapisi\n");
			exit(-1);
		}
		size = write(fd, string, 13);
		if (size != 13){
			printf("Ne udalos zapisat vsyu stroku\n");
			exit(-1);
		}
		close(fd);
		printf("Stroka zapisana v fifo. Process roditel zakanchivaet rabotu\n");
	}
	else {
		if((fd = open(name, O_RDONLY)) < 0){
			printf("Ne udalos otkit fifo dlya chtenia\n");
		}
		size = read(fd, resstring, 13);
		if(size != 13){
			printf("Ne udalos prochitat vsyu stoku\n");
			exit(-1);
		}
		printf("Prochitannaya stroka %s. Dochernii process zavershaet rabotu\n", resstring);
		close(fd);
	}
	return 0;
}
