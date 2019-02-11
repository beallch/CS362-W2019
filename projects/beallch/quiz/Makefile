CFLAGS = -Wall -coverage

runtest: testme.c
	gcc -o testme testme.c $(CFLAGS)	
	./testme

clean: 
	rm -f *.gcov *.gcda *.gcno testme
	
