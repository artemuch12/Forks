#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//Taken from the example in manual
void err_fork(pid_t *kinder)
{
	if (*kinder == -1) 
	{
		perror("fork");
        exit(EXIT_FAILURE);
    }
}


int main()
{

	pid_t father;
	pid_t grand_father;
	pid_t kinder_ppid[5];
	pid_t kinder_pid[5];
	pid_t kinder[5];
	father = getpid();
	grand_father = getppid();
	printf("My PID = %d and PID my father %d! And ... no! I am your father!\n", father, grand_father);
	kinder[0] = fork();
	err_fork(&kinder[0]);
	if(kinder[0] == 0)
	{
		kinder_pid[0] = getpid();
		kinder_ppid[0] = getppid();
		printf("My PID = %d and PID my father %d!\n", kinder_pid[0], kinder_ppid[0]);
		kinder[1] = fork();
		err_fork(&kinder[1]);
		if(kinder[1] != 0)
		{
			kinder[2] = fork();
			err_fork(&kinder[2]);
		}
		if(kinder[1] == 0)
		{
			kinder_pid[1] = getpid();
			kinder_ppid[1] = getppid();
			printf("My PID = %d and PID my father %d!\n", kinder_pid[1], kinder_ppid[1]);
		}
		if(kinder[2] == 0)
		{
			kinder_pid[2] = getpid();
			kinder_ppid[2] = getppid();
			printf("My PID = %d and PID my father %d!\n", kinder_pid[2], kinder_ppid[2]);
		}
	}
	else
	{
		kinder[3] = fork();
		err_fork(&kinder[3]);
		if(kinder[3] == 0)
		{
			kinder_pid[3] = getpid();
			kinder_ppid[3] = getppid();
			printf("My PID = %d and PID my father %d!\n", kinder_pid[3], kinder_ppid[3]);
			kinder[4] = fork();
			err_fork(&kinder[4]);
			if(kinder[4] == 0)
			{
				kinder_pid[4] = getpid();
				kinder_ppid[4] = getppid();
				printf("My PID = %d and PID my father %d!\n", kinder_pid[4], kinder_ppid[4]);
			}
		}
	}
	getchar();
	exit(0);
}
