all:
	gcc src/*.c -o dnoted -g 
clean:
	rm /usr/bin/dnoted
install:
	mv dnoted /usr/bin
