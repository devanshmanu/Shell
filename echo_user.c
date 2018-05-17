#include "echo_user.h"

int get_echo_user(int numberOfTokens, char command_array[10][1000])
{
	int i,j;
	for(i=1; i<=numberOfTokens; i++)
		{
			for(j=0; j<strlen(command_array[i]); j++)
			{
				if(command_array[i][j]!='"')
				{printf("%c",command_array[i][j] );}
			}
			printf(" ");
		}
	printf("\n");
}
