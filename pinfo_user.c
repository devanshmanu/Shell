#include "pinfo_user.h"

int get_pinfo_user(char com[1001],int pinfotag)
{	
	char* token;
	char* saveptr;
	if(pinfotag == 1)
	{
		int pid_curr = getpid();
		
		//printf("%d\n",pid_curr);
		int i=0;
			int j,k;
		int temparr[6];
		int temparr2[6];
		while(pid_curr!=0)
		{
			temparr[i]=pid_curr%10;
			//printf("%d\n",pid_curr%10 );
			pid_curr/=10;
			i++;

		}
		for(k=0,j=i-1; j>=0,k<i; j--, k++)
			{
				//printf("%d\n",temparr[j] );
				temparr2[k]=temparr[j];
			}
		//for(k=0; k<i;k++)
		//{
	//		printf("%d\n",temparr2[k] );
		//}
		com[strlen(com)]=' ';
		//printf("-----%s\n",com );
		for (j = strlen(com),k=0; j <i+strlen(com), k<i ; j++,k++)
		{
			/* code */
			com[j]=temparr2[k]+'0';

		}
		for(k=0; k<strlen(com); k++)
		{
			//printf("%c\n",com[k] );
		}
	}
	token = strtok_r(com," ",&saveptr);
	token = strtok_r(NULL," ",&saveptr);
	int len = strlen(token);
	
	int pid = 0;
	int i= 0;
	while(i<len)
	{
		pid = pid*10 + ((int)token[i] - (int)'0');
		i += 1;
	}
	char line[10000];
	char path[100];
	FILE* fptr;
	sprintf(path,"/proc/%d/status",pid);
	if((fptr = fopen(path,"r")) == NULL){
		printf("Error accessing proc file\n");
		return 0;
	}
	while(fscanf(fptr," %[^\n]s",line) == 1)
	{
		char* linetoken;
		char* linesaveptr;
		int len = strlen(line);
		for(i=0;i<len;i++)
			if(line[i] == 9)
				line[i] = (char)32;
		linetoken = strtok_r(line," ",&linesaveptr);
		if(strcmp(linetoken,"Pid:") == 0)
		{
			printf("%s %s\n",linetoken,linesaveptr);
			linetoken = strtok_r(line," ",&linesaveptr);
		}
		if(strcmp(linetoken,"State:") == 0)
		{
			printf("Process state : %s\n",linesaveptr);
			linetoken = strtok_r(line," ",&linesaveptr);
		}
		if(strcmp(linetoken,"VmSize:") == 0)
		{
			printf("Virtual Memory : %s\n",linesaveptr);
			linetoken = strtok_r(line," ",&linesaveptr);
		}
	}
	sprintf(path,"/proc/%d/cmdline",pid);
	if((fptr = fopen(path,"r")) == NULL)
	{
		printf("Error accessing proc files\n");
		return 0;
	}
	fscanf(fptr," %[^\n]s",line);
	printf("Executable path : %s\n",line);
	return 0;
}