CC = gcc
CFLAGS = -Wall -pthread -O2
LDFLAGS = -lrt   # for shm_open

all: restaurante cocineros mozos

restaurante: restaurante.c
	$(CC) $(CFLAGS) -o restaurante restaurante.c $(LDFLAGS)

cocineros: cocineros.c
	$(CC) $(CFLAGS) -o cocineros cocineros.c $(LDFLAGS)

mozos: mozos.c
	$(CC) $(CFLAGS) -o mozos mozos.c $(LDFLAGS)

clean:
	rm -f restaurante cocineros mozos
