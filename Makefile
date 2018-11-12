CC=gcc
CFLAGS=-lWarn -pedantic

temp:	Temp.o libmyifttt.a
	cc Temp.o -L. -lmyifttt -lcurl -o Temp

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o:	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

Temp.o:	Temp.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

all: temp
