CC=gcc
CFLAGS=-Wall -Werror -Wextra

rebuild:
	$(MAKE) clean
	$(MAKE) all

cipher: cipher.o
	$(CC) $(CFLAGS) cipher.o -o ../build/cipher

logging_cipher: logger.o cipherQ5.o
	$(CC) $(CFLAGS) logger.o cipherQ5.o -o ../build/logging_cipher

all: cipher logging_cipher

logger.o: logger.c
	$(CC) -c $(CFLAGS) logger.c -o logger.o

cipherQ5.o: cipher.c
	$(CC) -c $(CFLAGS) cipher.c -DQuest_5 -o cipherQ5.o

cipher.o: cipher.c
	$(CC) -c $(CFLAGS) cipher.c -o cipher.o 

clean:
	rm -rf *.o ../build/cipher ../build/logging_cipher
