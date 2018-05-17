CC = gcc

default: a.out

a.out :	shell.o pwd_user.o cd_user.o echo_user.o ls_user.o execp_user.o pinfo_user.o
	$(CC) -o a.out shell.o pwd_user.o cd_user.o echo_user.o ls_user.o execp_user.o pinfo_user.o $(CFLAGS)

shell.o : shell.c pwd_user.h execp_user.h cd_user.h echo_user.h ls_user.h
	$(CC) $(CFLAGS) -c shell.c

mypwd.o : pwd_user.c pwd_user.h
	$(CC) $(CFLAGS) -c pwd_user.c

mycd.o : cd_user.c cd_user.h
	$(CC) $(CFLAGS) -c cd_user.c

myecho.o : echo_user.c echo_user.h
	$(CC) $(CFLAGS) -c echo_user.c

myls.o : ls_user.c ls_user.h
	$(CC) $(CFLAGS) -c ls_user.c

myexecp.o : execp_user.c execp_user.h
	$(CC) $(CFLAGS) -c execp_user.c

mypinfo.o : pinfo_user.c pinfo_user.h
	$(CC) $(CFLAGS) -c pinfo_user.c
clean:
	rm a.out *.o  
