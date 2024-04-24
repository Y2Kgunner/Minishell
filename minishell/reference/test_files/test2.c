/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykulkarn <ykulkarn@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:21:35 by ykulkarn          #+#    #+#             */
/*   Updated: 2022/08/23 15:03:44 by ykulkarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

void printDir(void)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}

int takeInput(char* str)
{
    char* buf;
  
    buf = readline("\nminishell>>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        // if (strcmp(buf, "pwd") == 0)
		// 	printDir;
		return 0;
    } else {
        return 1;
	}
	//free(buf);
}

void execArgs(char** parsed)
{
	// Forking a child
	pid_t pid = fork();

	if (pid == -1) {
		printf("\nFailed forking child..");
		return;
	} else if (pid == 0) {
		if (execvp(parsed[0], parsed) < 0) {
			printf("\nCould not execute command..");
		}
		exit(0);
	} else {
		// waiting for child to terminate
		wait(NULL);
		return;
	}
}

int main()
{
	char str[1000];
	char cwd[1024];
	char	*parsedArgs[100];
	while (1)
	{
		takeInput(str);
		execArgs(parsedArgs);
		// if (str == "pwd")
		// {
		// 	getcwd(cwd, sizeof(cwd));
		// 	printf("\n%s", cwd);
		// }
		// else
		//if (str == "pwd")
			//printDir();
		//printf("%s", str);
	}
	//free(str);
}