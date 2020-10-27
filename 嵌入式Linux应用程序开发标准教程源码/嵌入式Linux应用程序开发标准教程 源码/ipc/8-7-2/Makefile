EXEC1 = producer
EXEC2 = customer
OBJS1 = producer.o sem_com.o
OBJS2 = customer.o sem_com.o
HEADERS = shm_com.h sem_com.h

CC = gcc
CFLAGS = -O2 

all:${EXEC1} ${EXEC2}
${EXEC1} : ${OBJS1}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
${EXEC2} : ${OBJS2}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

${OBJS1} : ${HEADERS}
${OBJS2} : ${HEADERS}

.PHONY : clean
clean :
	-rm -f ${OBJS1} ${EXEC1}
	-rm -f ${OBJS2} ${EXEC2}