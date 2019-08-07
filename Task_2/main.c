#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void err_fork(pid_t *command)
{
	if (*command == -1) 
	{
		perror("fork");
        exit(EXIT_FAILURE);
    }
}

void extra_slash(char *path)
{
	int i = 0;
	for(i = 0; path[i] != '\n'; i++)
	{
	}
	if(path[i-1] == '/')
	{
		path[i-1] = path[i];
	}
}

int main()
{
	int i = 0, j = 0;
	int position_end = -1;
	int status = 1;
	int len_path = 1;
	char *err_wd = NULL;
	char buff[100] = {'/', 'b', 'i', 'n', '/'};
	char name[50] = {'0'};
	char path[100] = {'0'};
	char PWD[254] = {'0'};
	pid_t command;
	pid_t kid;
	err_wd = getcwd(PWD, 254);
	if(err_wd == NULL)
	{
		puts("Error");
		exit(-1);
	}
	puts("Enter command");
	fgets(path, 50, stdin);
	printf("PWD:	%s\n", PWD);
	if(((path[0]) == '.') && (path[1] == '/'))
	{
		extra_slash(path);
		len_path = strlen(PWD);
		for(i = 2; path[i] != '\n'; i++)
		{
			name[i-2] = path[i];
		}
		for(i = 1; path[i] != '\n'; i++)
		{
			PWD[i+len_path-1] = path[i];
		}
		
	}
	else if(path[0] == '/')
	{
		extra_slash(path);
		for(i = 0; path[i] != '\n'; i++)
		{
			if(path[i] == '/')
			{
				position_end = i;
			}
		}
		for(i = position_end+1, j = 0; path[i] != '\n'; i++, j++)
		{
			name[j] = path[i];
		}
	}
	else
	{
		extra_slash(path);
		for(i = 0; path[i] != '\n'; i++)
		{
			name[i] = path[i];
		}
		
		for(i = 0; path[i] != '\n'; i++)
		{
			buff[i+5] = path[i];
		}
		buff[i+5] = '\n';
		for(i = 0; buff[i] != '\n'; i++)
		{
			path[i] = buff[i];
		}
		
	}
	printf("PWD:	%s\n", PWD);
	printf("name:	%s\n", name);
	printf("path:	%s\n", path);
	
	
	/*command = fork();
	err_fork(&command);
	if(command == 0)
	{
		kid = getpid();
		execl(, name, NULL);
	}
	else
	{
		waitpid(kid, &status, 0);
	}*/
	exit(0);
}
