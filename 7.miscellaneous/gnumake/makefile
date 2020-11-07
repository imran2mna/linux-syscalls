CC=gcc
CFLAGS=-g -Wall
INCLUDES=

SRCS = test.c add.c
OBJS = $(SRCS:.c=.o)
MAIN = output



all: 	$(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)
	$(RM) *.o *~

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)
