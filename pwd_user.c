#include "pwd_user.h"

int get_pwd_user(int len, char hostname[1001])
{
	char currentDirectory[1001];
	getcwd(currentDirectory, sizeof(currentDirectory));
	int i;
	printf("/home/%s/",hostname );
	for(i = len+1; i<strlen(currentDirectory); i++)
		printf("%c", currentDirectory[i]);
	printf("\n");
	return 5;	
}