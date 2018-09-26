#include <stdio.h>
#include <mem.h>
#include "Source.h"

void printIssues(){
    printf("1) Make a step.\n");
    printf("2) Display tape.\n");
    printf("3) Display the current state of the machine(current symbol, current position).\n");
    printf("4) Exit from debug mode.\n");
}

void printCurState(struct iterator *tape, int numOfStep, int curState) {
    printf("----------------------------\n");
    printf("Step number%i\n", numOfStep);
    printf("Current state: q%i\n", curState);
    printf("Tape:\n");

    struct iterator *curListOfTapeCell = tape;
        printf("symbol: %c, position: %i.\n",  curListOfTapeCell->curSymbol,curListOfTapeCell->curPosition);

    printf("----------------------------\n");
}

void printTape(struct iterator *tape) {
    printf("----------------------------\n");
    struct iterator *tapeCell = tape;

        printf("\t");

        struct tapeCell *curTapeCell = tapeCell->thisTapeCell;

        while (curTapeCell != NULL) {
            if (curTapeCell->position == tapeCell->curPosition) {
                printf("V");
            }
            else {
                printf(".");
            }
            curTapeCell = curTapeCell->next;
        }

        printf("\n");
        printf("\t");

        curTapeCell = tapeCell->thisTapeCell;
        while (curTapeCell != NULL) {
                printf("%c", curTapeCell->data);

                curTapeCell = curTapeCell->next;
        }
        printf("\n");

    printf("----------------------------\n");
}
