CFLAGS=-Wall -Wextra -g --std=c99 --pedantic-errors -ggdb -gstrict-dwarf
CC=gcc
DEPS=process.h
OBJ=main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)


uncrustify:
	uncrustify --replace --no-backup -c style.cfg *.c

clean:
	rm -f sender recv a.out core.*

.PHONY: clean uncrustify
