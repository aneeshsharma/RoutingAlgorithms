CC = gcc

all: lsr.o dvr.o

lsr.o: lsr.c
	$(CC) lsr.c -o lsr.o

dvr.o: dvr.c
	$(CC) dvr.c -o dvr.o