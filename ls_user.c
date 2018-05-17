#include "ls_user.h"

int get_ls_user(const char *dirname, char command_array[10][1000])     
{ 

    struct dirent* file_list;
    struct stat file_stat;
    struct tm lt;  
    struct passwd *pwd; // For User-ID

    DIR* directory = opendir(dirname);


    if(directory == NULL)     
    { 

        printf("list_dir : %s : %s \n", dirname, strerror(errno));
        return 0;
    }   

    while( (file_list = readdir(directory) ) )     
    { 
        if ( (stat(file_list->d_name, &file_stat) ) == 0 )    
            {
                pwd = getpwuid(file_stat.st_uid);
            }
            time_t last_modified = file_stat.st_mtime;
            localtime_r(&last_modified, &lt);
            char timebuf[80];
            strftime(timebuf, sizeof(timebuf), "%c", &lt);

            if (pwd != 0)   
            {

                if((command_array[1][1]=='l' && command_array[1][2]=='a') || (command_array[1][1]=='a' && command_array[1][2]=='l'))
                {  
                //printf("LA\n");  
                printf("%s \t %ld \t %s \t %s", pwd->pw_name, (long)file_stat.st_size, timebuf, file_list->d_name);
                printf("\n");
                }
                
                else if(command_array [1][1]=='l')
                {
                    //printf("L\n");
                    if(file_list->d_name[0] != '.')
                        {   
                            printf("%s \t %ld \t %s \t %s", pwd->pw_name, (long)file_stat.st_size, timebuf, file_list->d_name);
                            printf("\n"); 
                        }   

                }
                
                else if(command_array[1][1]=='a')
                {
                    //printf("A\n");
                    printf("%s\t", file_list->d_name);
                
                }
                
                else if (strlen(command_array[1])==0)
                {
                    //printf("NONE\n");
                   if(file_list->d_name[0] != '.')
                        {   
                            printf("%s\t", file_list->d_name); 
                        }  
                }


            } 
            
            else  
            {   printf("restriceddddddd\n");

                printf("%d \t %ld \t %s \t %s", file_stat.st_uid, (long)file_stat.st_size, timebuf, file_list->d_name);
                printf("\n");
            } 
    }
    closedir(directory);        
    return 0; 
}

