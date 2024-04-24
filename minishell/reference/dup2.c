// CPP program to illustrate dup2() 
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main()
{
	int file_desc = open ("test.txt", O_WRONLY | O_APPEND);

	dup2(file_desc, 1);
	printf("After dup2 function, this is added to the txt file \n");
}