# Filename:    makefile
# Project:     encodeInput
# Author:      Bakr Jasim
# Date:        2022-02-05
# Description: This is the makefile for the encodeInput utility, and it includes all the dependencies and     
# their directory location for linking and compiling the code.

./bin/encodeInput: ./obj/sRecord.o ./obj/main.o ./obj/Assembly.o
	cc ./obj/sRecord.o ./obj/main.o ./obj/Assembly.o -o ./bin/encodeInput
	
	
./obj/sRecord.o: ./src/sRecord.c ./inc/encodeInput.h
	cc -c ./src/sRecord.c -o ./obj/sRecord.o
	
./obj/main.o: ./src/main.c ./inc/encodeInput.h
	cc -c ./src/main.c -o ./obj/main.o
	
./obj/Assembly.o: ./src/Assembly.c ./inc/encodeInput.h
	cc -c ./src/Assembly.c -o ./obj/Assembly.o
	
	
all: ./bin/encodeInput

clean: 
	rm ./bin/*
	rm ./obj/*
