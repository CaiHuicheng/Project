EXEC = sem_fork
OBJS = sem_fork.o sem_com.o
HEADERS = sem_com.h

CC = gcc
INC = -I.
CFLAGS = ${INC} -g 

all:${EXEC}
${EXEC} : ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} 

${OBJS} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS} ${EXEC}
