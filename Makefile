ecig: ecig.c
	gcc -o ecig ecig.c -lm -lncurses -ltinfo
install:
	cp ecig /usr/bin/ecig
	cp ecig.6 /usr/share/man/man6
	bzip2 -f /usr/share/man/man6/ecig.6
