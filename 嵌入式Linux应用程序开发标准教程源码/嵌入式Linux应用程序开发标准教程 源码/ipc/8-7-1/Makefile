EXEC = pipe_select
OBJS = pipe_select.o
HEADERS = 

CC = gcc
INC = -I.
CFLAGS = ${INC} -g 

all:${EXEC}
${EXEC} : ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJS} 

${OBJS} : ${HEADERS}

.PHONY : clean
TMP_FILES = in1 in2
clean :
	-rm -f ${OBJS} ${EXEC}
	-rm -f TMP_FILES