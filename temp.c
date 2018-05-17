#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h> 

int list_dir(const char *dirname)     
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
                pwd = getpwuid(file_stat.st_uid); // Get User-ID
            }

            // Last Modified 
            time_t last_modified = file_stat.st_mtime;
            localtime_r(&last_modified, &lt);
            char timebuf[80];
            strftime(timebuf, sizeof(timebuf), "%c", &lt);

            if (pwd != 0) 
            {

                printf("%s \t %ld \t %s \t %s", pwd->pw_name, (long)file_stat.st_size, timebuf, file_list->d_name);
                printf("\n");

            } else  
            {

                printf("%d \t %ld \t %s \t %s", file_stat.st_uid, (long)file_stat.st_size, timebuf, file_list->d_name);
                printf("\n");
            } 
    }
    closedir(directory);        
    return 0; 
}

int main(int argc, char* argv[])    {

    if ( argc == 1 ) {

    return list_dir ( "." );

    } else {

    int ret = 0;

    for (int i = 1; i < argc; i += 1 ) {

        if ( list_dir ( argv[i] ) != 0 ) {

        ret = 1; 
        }
    }

    return ret;
     } 
}