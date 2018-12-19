CC      = gcc
CFLAGS  = -O3 -Wall -ansi -pedantic -msse4.1 -std=c99 -fopenmp -g
LDFLAGS = -lpthread


main: main.o dot_product.o matrix.o ompmult.o pthmult.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

main.o: main.c dot_product.c matrix.c ompmult.c pthmult.c dot_product.h matrix.h ompmult.h pthmult.h
	$(CC) $(CFLAGS) -c $<

dot_product.o: dot_product.c dot_product.h
	$(CC) $(CFLAGS) -c $<

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c $<

ompmult.o: ompmult.c ompmult.h dot_product.h matrix.h
	$(CC) $(CFLAGS) -c $<

pthmult.o: pthmult.c pthmult.h dot_product.h matrix.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main
