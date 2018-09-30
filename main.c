#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Source.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Error 1.\nWrong format.\nUse: <description>.txt <tape>.txt <out>.txt \nOr <description>.txt <tape>.txt <out>.txt -d");
        exit(1);
    }

    char *descriptionFile, *outputFile, *tapeFile;
    char *modeFlag = NULL;
    int numOfStep = 0;
    struct iterator *tape = NULL;
    struct listOfStates *states = NULL;
    char voidSymbol = '_';

    int curState;

    struct state *curStateCell = NULL;

    descriptionFile = argv[1];
    tapeFile = argv[2];
    outputFile = argv[3];
    modeFlag = argv[4];

    //читаем файл входных инструкций
    states = readDescription(descriptionFile, states, &curState);
    //читаем файл с входной лентой
    tape = readTape(tapeFile, voidSymbol);

    while(curState != 0){
        if (modeFlag != NULL) {
            if (strcmp(modeFlag, "-d") != 0) {
                printf("Error 7.\nWrong flag.");
                exit(7);
            }

            if (strcmp(modeFlag, "-d") == 0) {
                int choice;
                do {
                    printIssues();
                    char *choiceLine = NULL;
                    char tmpLine[20000] = "";
                    choiceLine = gets(tmpLine);
                    choice = atoi(choiceLine);
                    switch (choice) {
                        case 1:
                            break;
                        case 2:
                            printTape(tape);
                            break;
                        case 3:
                            printCurState(tape, numOfStep, curState);
                            break;
                        case 4:
                            foutCondition(outputFile, tape, numOfStep);
                            printTape(tape);
                            exit(1);
                        default:
                            printf("Wrong choice.\n");
                            break;
                    }
                } while (choice != 1);
            }
        }
        step(tape, states, voidSymbol, numOfStep, &curState, curStateCell);
        numOfStep ++;
    }

    foutCondition(outputFile, tape, numOfStep);
    printTape(tape);

    return 0;
}

