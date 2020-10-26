EXEC_WR = write_lock
OBJS_WR = write_lock.o
EXEC_RD = read_lock
OBJS_RD = read_lock.o

HEADERS = 

CC = gcc
INC = -I.
CFLAGS = ${INC} -g 

all:${EXEC_WR} ${EXEC_RD}
${EXEC_WR} : ${OBJS_WR}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS_WR}
${EXEC_RD} : ${OBJS_RD}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS_RD} 


${OBJS_WR} : ${HEADERS}
${OBJS_RD} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS_WR} ${EXEC_WR} ${OBJS_RD} ${EXEC_RD}