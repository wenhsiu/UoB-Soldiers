CFLAGS =  -Wall -Wextra -pedantic -ansi -O2
CC = clang


sold: sold_v4.c test_v4.c
	$(CC) sold.c test.c -o sold $(CFLAGS)
