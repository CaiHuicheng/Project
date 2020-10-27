EXEC_WR = fifo_write
OBJS_WR = fifo_write.o
EXEC_RD = fifo_read
OBJS_RD = fifo_read.o
HEADERS = 

CC = gcc
INC = -I.
CFLAGS = ${INC} -g 

all:${EXEC_WR} ${EXEC_RD}

${EXEC_WR} : ${OBJS_WR}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS_WR} 
${OBJS_WR} : ${HEADERS}

${EXEC_RD} : ${OBJS_RD}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS_RD} 
${OBJS_RD} : ${HEADERS}


.PHONY : clean
clean :
	-rm -f ${OBJS_WR} ${EXEC_WR}
	-rm -f ${OBJS_RD} ${EXEC_RD}