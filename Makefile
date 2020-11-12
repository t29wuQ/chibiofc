CFLAGS=-std=c11 -g -static
SRCS=main.c $(wildcard ./lib/*.c)
OBJS=$(SRCS: .c=.o)

chibiofc: $(OBJS)
	  $(CC) -o chibiofc $(OBJS) $(LDFLAGS)
