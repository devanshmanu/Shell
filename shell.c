#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include "pwd_user.h"
#include "echo_user.h"
#include "cd_user.h"
#include "ls_user.h"
#include "execp_user.h"
#include "pinfo_user.h"



int main(int argc, char const *argv[])
{
	char input[1001]={'\0'};
	strcpy(input,"");
	char inputText[1001]={'\0'};
	strcpy(inputText,"");
	char currentDirectory[1001];
	char hostname[1001];
	char homeDirectory[1001];
	char exitt[5];					
	strcpy(exitt,"exit");

	//-------- getting details for prompt
	getcwd(homeDirectory, sizeof(homeDirectory));
	gethostname(hostname, sizeof(hostname));
	register struct passwd *pw; //to get username
	register uid_t uid;
	uid = geteuid (); // gets the current user id
	pw = getpwuid (uid);


	//---------------------------------------


 
  
  

	// ------- Basic info --------------------
	printf("\n");
	printf("\n");
	printf("|==============================ENTERING SHELL==============================|\n");
	printf("|..........................................................................|\n");
	printf("|..............................Operating Systems...........................|\n");
	printf("|.................................Monsoon 2017.............................|\n");
	printf("|..................................................-> Devansh Manu.........|\n");
	printf("|..................................................-> Mayank Modi..........|\n");
	printf("|..........................................................................|\n");
	printf("|..........................................................................|\n");
	printf("|==========================================================================|\n");
	printf("\n");
	printf("\n");



	//------------------------------------------


	//-------------------------------------------------------------------------------------shell process loop ----------------
	
	while(strcmp(input, "exit") != 0)
	{	
		//------------STARTING THE SHELL--------------


			//------------PRINTING THE COMMAND PROMPT, USER, HOST, DIRECTORY DETAILS-----------

			getcwd(currentDirectory, sizeof(currentDirectory));
			if( strcmp(currentDirectory,homeDirectory) !=0) // currently not in home folder
			{
				int i;
				printf("<%s@%s~/",pw->pw_name,hostname );
				for(i = strlen(homeDirectory)+1; i<strlen(currentDirectory); i++)
					printf("%c", currentDirectory[i]);
				printf("> ");
			}
			else // in home folder
			{
				printf("<%s@%s:~> ",pw->pw_name,hostname );
			}


			

			// ------SHELL WAITS FOR INPUT-----------
			fgets(input, sizeof(input), stdin);
			input[strcspn(input, "\n")] = 0; // converting input string to a str-comparable format
			//char command = strtok(input, " ");
			
			

			//----------TOKENISING THE COMMAND---------			
			char command_array[10][1000]={0};
			int j=0;
			int numberOfTokens=0; 
			int i=0;
    		for(i=0;i<strlen(input);i++)
    		{
        		if(input[i]==' ')
        		{
            		if(input[i+1]!=' ')
            		{
                		command_array[numberOfTokens][j]='\0';
                		j=0;
                		numberOfTokens++;
            		}
            		continue;
        		}
        		else
        		{
            		//copy other characters
            		command_array[numberOfTokens][j++]=input[i];
        		}       
    		}
    		command_array[numberOfTokens][j]='\0';
    		//printf("%d\n",numberOfTokens );
     
     	
    

    		//--------------redicrection----------------
    		if(strcmp(command_array[numberOfTokens-1],">")==0)
    		{
    			printf("redicrection\n");
    		}


			// ----------PWD COMMAND-----------------
			else if(strcmp(command_array[0],"pwd")==0 )
			{
				//int *pwd_check = getcwd(currentDirectory, sizeof(currentDirectory));
				//printf("%s\n",currentDirectory );
				int pwd_check = get_pwd_user(strlen(homeDirectory),hostname);
				if (pwd_check!=5)
				{
					printf("ERROR in pwd\n");
				}

			}






			//------------CD COMMAND--------------
			else if (strcmp(command_array[0], "cd") == 0)
			{
				
				
				if(numberOfTokens > 1)
				{
					printf("ERROR: 'cd' accepts only one argument\n");
				}

				else
				{
					int cd_check = get_cd_user(numberOfTokens, command_array);
					
					if (cd_check ==0)
						{
							//printf("now in %s\n",currentDirectory );
						}

					else{
						printf("ERROR\n");
					}	
				}

				

				
				
			}


			//-------------EXIT COMMAND-------------
			else if(strcmp(command_array[0],"exit") ==0)
			{
				return 0;
			}

			


			//-----------ECHO COMMAND-----------
			else if(strcmp(command_array[0],"echo")==0)
			{	
				int echo_check = get_echo_user(numberOfTokens, command_array);
				if(echo_check != 0 )
				{
					printf("ERROR\n");
				}

			}





			//----------------LS COMMAND-----------------
			else if(strcmp(command_array[0],"ls")==0 && strcmp(command_array[1],"-")!=0)
			{

				int ls_check = get_ls_user(".", command_array);
				printf("\n");
				if (ls_check!=0)
				{
					printf("ERROR\n");
				}

			}




			//---------------PINFO COMMAND---------
			else if(strcmp(command_array[0],"pinfo")==0)
			{
				
				int pinfotag=0;
				if (numberOfTokens ==0)
				{
					pinfotag=1;
				}


				int pinfo_check = get_pinfo_user(input,pinfotag);
				if(pinfo_check != 0)
				{
					printf("ERROR\n");
				}
			}







			//-----------EXEC COMMAND-----------
			else 
			{	int check =0;
				//printf("token: %d\n", numberOfTokens);
				if(strcmp(command_array[numberOfTokens], "&")==0)
					check = 1;
				//printf("%d\n",check );

				int execp_check = get_execp_user(input,check);
				if(execp_check != 0 )
				{
					printf("ERROR\n");
				}

			}








			












		//--------------SHELL ENDS------------




	}
	return 0;
}
