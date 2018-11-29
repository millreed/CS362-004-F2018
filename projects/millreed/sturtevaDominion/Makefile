CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

unittestresults: dominion.o
	gcc -o unittest1 unittest1.c -g dominion.c rngs.c $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -o unittest2 unittest2.c -g dominion.c rngs.c $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -o unittest3 unittest3.c -g dominion.c rngs.c $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -o unittest4 unittest4.c -g dominion.c rngs.c $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -o cardtest1 cardtest1.c -g dominion.c rngs.c $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -o cardtest2 cardtest2.c -g dominion.c rngs.c $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -o cardtest3 cardtest3.c -g dominion.c rngs.c $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -o cardtest4 cardtest4.c -g dominion.c rngs.c $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

randomtestcard1: dominion.o
	gcc -o randomtest randomtestcard1.c -g dominion.c rngs.c $(CFLAGS)
	./randomtest >> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out

randomtestcard2: dominion.o
	gcc -o randomtest randomtestcard2.c -g dominion.c rngs.c $(CFLAGS)
	./randomtest >> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out

randomtestadventurer: dominion.o
	gcc -o randomtest randomtestadventurer.c -g dominion.c rngs.c $(CFLAGS)
	./randomtest >> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
