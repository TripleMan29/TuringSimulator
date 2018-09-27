TuringSimulator : main.o ConsolePrint.o inputFile.o inputTape.o OutputFile.o Step.o
	gcc -o TuringSimulator main.o ConsolePrint.o inputFile.o inputTape.o OutputFile.o Step.o

main.o : main.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c

ConsolePrint.o : ConsolePrint.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o ConsolePrint.o ConsolePrint.c

inputFile.o : inputFile.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o inputFile.o inputFile.c

inputTape.o : inputTape.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o inputTape.o inputTape.c

OutputFile.o : OutputFile.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o OutputFile.o OutputFile.c

Step.o : Step.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o Step.o Step.c