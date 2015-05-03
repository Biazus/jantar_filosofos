din: phillie.o dinner.o main.o
	gcc -o din dinner.o phillie.o main.o -Wall -W -pthread

main.o: main.c
	gcc -c main.c -std=c99 -Wall -W -pthread

dinner.o: dinner.c
	gcc -c dinner.c -std=c99 -Wall -W -pthread

phillie.o: phillie.c
	gcc -c phillie.c -std=c99 -Wall -W -pthread
