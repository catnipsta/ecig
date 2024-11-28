ecig: ecig.c
	gcc -o ecig ecig.c -lm -lncurses -ltinfo
install:
	cp ecig /usr/bin/ecig
