#
# Makefile
#
# robots
#

robots: robots.h board.c helpers.c human.c moverobots.c place.c robots.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o robots robots.c -lm

clean:
	rm -f *.o a.out core robots
