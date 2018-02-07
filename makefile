#!/bin/bash
#file: MakeFile

#*****************************************
#Macro Variables CC and CFLAGS are created
#*****************************************
CC=gcc
CFLAGS = -c -Wall -g

#Format of commands in Make file is as follows
#*********************************************
#Target: Dependency
#<----tab---> <command>
#*********************************************


#***************************************************
#command for creation of executable file is:
#command = gcc <filename.c> -o <executable_filename>
#***************************************************

prog: main.o vehicles.o parseArgs.o 
	$(CC) main.o vehicles.o parseArgs.o -o prog -lm

#***********************************************************
#other command will be of the following form:
#command = gcc [options] <filename.c> [optional header files]

#their purpose is to compile each
#source code files in the program
#***********************************************************

main.o: main.c
	$(CC) $(CFLAGS) main.c -lm

vehicles.o: vehicles.c
	$(CC) $(CFLAGS) vehicles.c -lm

parseArgs.o: parseArgs.c
	$(CC) $(CFLAGS) parseArgs.c

#*********************************************************************
#clean is used to destroy all executable files
#so that the next make will compile all source code files from scratch
#*********************************************************************

clean:
	rm -rf *.o prog
