warmup1: warmup1.o my402list.o functionlist.o
	gcc -o warmup1 -g warmup1.o my402list.o functionlist.o

warmup1.o: warmup1.c my402list.h functionlist.h
	gcc -g -c -Wall warmup1.c

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c

functionlist.o: my402list.h functionlist.c functionlist.h
	gcc -g -c -Wall functionlist.c
	
clean:
	rm -f *.o warmup1
