ecig: ecig.c
	gcc -o ecig ecig.c -lm -lncurses -ltinfo
DESTDIR=/usr/local/bin
install:
	cp ecig $(DESTDIR)
	cp ecig.6 /usr/share/man/man6
	bzip2 -f /usr/share/man/man6/ecig.6
