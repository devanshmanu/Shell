#include "cd_user.h"

int get_cd_user(int numberOfTokens, char command_array[10][1000] )
{	int i;
	if (numberOfTokens == 0) // ex. cd 
	{
		char homeDirectory[1001]; int i;
		getcwd(homeDirectory, sizeof(homeDirectory));

		for(i=0; i<strlen(homeDirectory);i++ )
		{
			command_array[1][i]=homeDirectory[i];
		}

		int cd_check = chdir(command_array[1]);
		return cd_check;			
		
	}

	else
	{
		if (command_array[1]=="..")
		{
			char temp_cwd[1000];
			getcwd(temp_cwd, sizeof(temp_cwd));
			for(i=0; i<strlen(temp_cwd);i++ )
			{
				command_array[1][i]=temp_cwd[i];
			}
		}

		int cd_check = chdir(command_array[1]);
		return cd_check;
		
	}
}	
