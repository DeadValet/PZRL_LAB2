.PHONY: clean
g := gcc
lab2.o: lab2.c
	$(g) -c lab2.c
functions.o: functions.c
	$(g) -c functions.c
sed_simplified: lab2.o functions.o
	$(g) -o sed_simplified lab2.o functions.o
test: sed_simplified
	./sed_simplified test.txt s/^/HEART/
clean:
	rm -f *.o sed_simplified

