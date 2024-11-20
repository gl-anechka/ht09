CC=gcc
LD=gcc
CFLAGS=-O2 -Wall -Werror
LDFLAGS=-ldl

all: main.o linear.o mt.o mtwister.o
	@$(LD) main.o linear.o mt.o mtwister.o -o printrandom $(LDFLAGS) -rdynamic

main.o: main.c
	@$(CC) $(CFLAGS) main.c -c -o main.o
linear.o: linear.c
	@$(CC) $(CFLAGS) linear.c -c -o linear.o
mtwister.o: mtwister.c
	@$(CC) $(CFLAGS) mtwister.c -c -o mtwister.o
mt.o: mt.c
	@$(CC) $(CFLAGS) mt.c -c -o mt.o

clean:
	@rm *.o