#include "execp_user.h"

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

int  execute(char **argv, int check)
{
     pid_t  pid;
     int    status;
     //exit(1);
     if ((pid = fork()) < 0) {     /* fork a child process           */
          printf("ERROR: Forking Failed\n");
          exit(1);
     }
     else if (pid == 0) {          /* for the child process:         */
          if (execvp(*argv, argv) < 0) {  
               //printf("execute hua\n");   /* execute the command  */
               printf("ERROR: exec Failed\n");
               exit(1);
          }
     }
     else {    
          //printf("yahaa\n"); 
          //printf("pid: %d status:%d\n",pid,status );                                /* for the parent:      */
          if(check == 0){
               while (wait(&status) != pid)
               {       /* wait for completion  */
               //printf("%d\n",pid);
               
               }
          }  
          else
          {
               printf("[+]%d\n",pid );
          }  

         
          

     }
     return pid;
}




int get_execp_user(char string[1001],int check)
{
     char  line[1024];             /* the input line                 */
     char  *argv[64];              /* the command line argument      */
     int i=1;
     while (i--) {                   /* repeat until done ....         */
         // printf("Shell -> ");     /*   display a prompt             */
          //printf("\n");
          if(check == 0)
               parse(string, argv);       /*   parse the line               */
          else
          {
               //printf("%s\n",string );
               //printf("%d\n",strlen(string) );
          }

                /*   exit if it is                */
          execute(argv,check);           /* otherwise, execute the command */

     }
}
