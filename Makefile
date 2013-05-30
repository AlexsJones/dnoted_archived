all:
	gcc src/*.c -o dnoted 
install:
	mv dnoted /usr/bin
