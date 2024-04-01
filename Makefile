CC = cc

spag: main.c
	${CC} $^ -o $@

install: spag
	mv spag /usr/local/bin/
	chmod 755 /usr/local/bin/spag
	mkdir -p /usr/local/share/man/man1/
	cp spag.1 /usr/local/share/man/man1/
	chmod 644 /usr/local/share/man/man1/spag.1

uninstall:
	rm /usr/local/bin/spag
	rm /usr/local/share/man/man1/spag.1