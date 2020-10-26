EXEC = thread
OBJS = thread.o
HEADERS = 

CC = gcc
INC = -I.
CFLAGS = ${INC} -lpthread

all:${EXEC}
${EXEC} : ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} 

${OBJS} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS} ${EXEC}

