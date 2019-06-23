#
# Makefile
#
# AUTHOR: Greg Parkin
#
#


CC = gcc

CFLAGS = -Q -g3 -rdynamic -fstack-check -fPIC \
	-DLINUX -DORAX86_64 -D_GNU_SOURCE -D_LARGEFILE64_SOURCE=1 \
	-D_LARGEFILE_SOURCE=1 -DSLTS_ENABLE -DSLMXMX_ENABLE \
	-D_REENTRANT -DNS_THREADS -DLONG_IS_64 -fno-strict-aliasing -DSS_64BIT_SERVER -w


BUILD = ball_clock

BALL_CLOCK = main.o stack.o queue.o


Build: $(BUILD)

install: $(BUILD)

ball_clock: $(BALL_CLOCK)
	$(CC) -o ball_clock $(BALL_CLOCK)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

stack.o: stack.c stack.h
	$(CC) -c stack.c $(CFLAGS)

queue.o: queue.c queue.h
	$(CC) -c queue.c $(CFLAGS)
