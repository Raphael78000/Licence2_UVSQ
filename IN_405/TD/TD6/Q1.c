#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define HOME_DIR "/home/user"

void Q1(){
	execlp("ps","ps",NULL);
}

void Q2(){
	execlp("ls","ls",HOME_DIR,NULL);
}

void Q3(const int first){
	if(first)
		execlp("find","find",HOME_DIR,"-type","d",NULL);

	char *cmd[] = {"find",HOME_DIR,"-type","f",NULL};
	execvp("find",cmd);
}

void main(){
	int i;

	if (!fork())
		Q1();
	wait(NULL);

	if (!fork())
		Q2();
	wait(NULL);

	for (i = 0;i < 2; ++i)
		if (!fork())
			Q3(!i);

	for (i = 0;i < 2; ++i)
		wait(NULL);
}
