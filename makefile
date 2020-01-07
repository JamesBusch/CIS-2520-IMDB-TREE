#Name: James Busch
#ID: 1054886
#Email: buschj@uoguelph.ca
#Date: 26/10/2019
#Version: 0.01

CC = gcc
CFLAGS = -ansi -Wall -g -pedantic
objects = a3.o binary.o common.o name.o principals.o title.o

all: a3

a3: $(objects)
	$(CC) $(objects) -o $@

a3.o: a3.c *.h
	$(CC) $(CFLAGS) -c a3.c -o $@

common.o: common.c
	$(CC) $(CFLAGS) -c common.c -o $@

name.o: name.c binary.h common.h
	$(CC) $(CFLAGS) -c name.c -o $@

principals.o: principals.c binary.h common.h
	$(CC) $(CFLAGS) -c principals.c -o $@

title.o: title.c binary.h common.h
	$(CC) $(CFLAGS) -c title.c -o $@

binary.o: binary.c common.h
	$(CC) $(CFLAGS) -c binary.c -o $@

run:
	./a3

clean:
	rm ./*.o a3