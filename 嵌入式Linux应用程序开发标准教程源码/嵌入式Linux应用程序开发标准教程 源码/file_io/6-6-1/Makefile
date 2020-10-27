EXEC1 = producer 
EXEC2 = customer
OBJS1 = producer.o mylock.o
OBJS2 = customer.o mylock.o
HEADERS = mylock.h

CC = gcc
CFLAGS = -O2 -g 

all:${EXEC1} ${EXEC2}
${EXEC1} : ${OBJS1}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS1}
${EXEC2} : ${OBJS2}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS2}

${OBJS1} : ${HEADERS}
${OBJS2} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS1} ${EXEC1}
	-rm -f ${OBJS2} ${EXEC2}
	cat /dev/null > myfifo