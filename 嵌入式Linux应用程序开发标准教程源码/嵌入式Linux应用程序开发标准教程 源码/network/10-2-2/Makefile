EXEC = getaddrinfo
OBJS = getaddrinfo.o
HEADERS =

CC = gcc
INC =
CFLAGS = ${INC} -g 

all:${EXEC}
${EXEC} : ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} 

${OBJS} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS} ${EXEC}