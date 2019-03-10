CC = gcc
LD = gcc


OPT = -O3 -fopenmp
LIB = -lm

openmp_petle: openmp_petle.o
	$(LD) $(OPT) openmp_petle.o -o openmp_petle $(LIB)



openmp_petle.o: openmp_petle.c
	$(CC) -c  $(OPT) openmp_petle.c



clean:
	rm -f *.o
