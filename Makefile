all:
	gcc src/*.c -o dnoted 
install:
	mv dirnoted /usr/bin
