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

void lex(char *path, int *number_lex)
{
	int i = 0;
	for(i = 0; path[i-1] != '\n'; i++)
    {
		if((path[i] == ' '))
        {
			number_lex++;
        }
	}
}






int main()
{
	int i = 0, j = 0, k = -1, l = 0;
	int position_end = -1;
	int status = 1;
	int len_path = 1;
	int exec_err = 0;
	int number_lex = 1;
	int lenght = 0;
	int poz1 = 0;
    int poz2 = 0;
	
	
	char *err_wd = NULL;
	char buff[100] = {'/', 'b', 'i', 'n', '/'};
	char name[50] = {'0'};
	char path[100] = {'0'};
	char buff_path[100] = {'0'};
	char buff_str[50] = {'0'};
	char PWD[254] = {'0'};
	char **input = NULL;
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
	lex(path, &number_lex);
	input = malloc(sizeof(char **)*number_lex);
	
	
	for(i = 0; path[i-1] != '\n'; i++)
    {
		if((path[i] == ' ') || (path[i] == '\n'))
        {
			poz1 = poz2;
            poz2 = i;
            if(poz1 == 0)
            {
				poz1 = -1;
            }
            if(k != -1)
            {
				for(j = poz1+1, l = 0; j < poz2; j++, l++)
				{
					buff_str[l] = path[j];
				}
				lenght = strlen(buff_str);
				input[k] = malloc(sizeof(char *)*lenght);
				for(j = 0; j < lenght; j++)
				{
					input[k][j] = buff_str[j];
				}
				k++;
            }
            else
            {
				for(j = poz1+1, l = 0; j < poz2; j++, l++)
				{
					buff_path[j] = path[j];
				}
				k++;
			}
        }
	}
	lenght = strlen(buff_path);
	for(i = 0; i < lenght; i++)
	{
		path[i] = buff_path[i];
	}
	path[i] = '\n';
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
		PWD[i+len_path-1] = '\n';
		for(i = 0; PWD[i] != '\n'; i++)
		{
			path[i] = PWD[i];
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
	
	
	command = fork();
	err_fork(&command);
	if(command == 0)
	{
		exec_err = execle(path, name, NULL, input);
		if(exec_err == -1)
		{
			printf("Error.");
		}
	}
	else
	{
		wait(&status);
		printf("Proccess terminated\n");
	}
	for(i = 0; i < number_lex -1; i++)
	{
		free(input[i]);
	}
	free(input);
	exit(0);
}
