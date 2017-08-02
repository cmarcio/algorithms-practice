# INSTRUCTION
# 	always call make commands on the project root directory
# 	call "make" to compile the instructions program
# 	call "make dir=dir_name" to compile the files inside the desired directory
#	call "make run" to run the program compiled
# 	call "make clean" to delete the object and program files

# default directory, containd instructions for using the makefile
dir = instructions

all: main

main: main.o
	@g++ -o program.exe main.o  

main.o:
	@g++ -c $(dir:=/main.cpp)

clean:
	@-rm -f *.o program.exe *~

run:
	@./program.exe