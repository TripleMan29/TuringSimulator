#include <stdio.h>
#include <stdlib.h>
#include "Source.h"

void foutCondition(char *file, struct iterator *tape, int numOfStep) {
    FILE *output;
    output = fopen(file, "w");


    fprintf(output, "Number of steps: %i;\n", numOfStep);

        fprintf(output, "Position: %i;\nCurrent symbol: %c;\nTape:",
                tape->curPosition, tape->curSymbol);
        struct tapeCell *curTapeCell = tape->thisTapeCell;

        fprintf(output,"\n");

        while (curTapeCell != NULL) {
            if (tape->curPosition == curTapeCell->position) fprintf(output,"V");
            else fprintf(output,".");
            curTapeCell = curTapeCell->next;
        }
        fprintf(output,"\n");

        curTapeCell = tape->thisTapeCell;

        while (curTapeCell != NULL) {
            fprintf(output, "%c", curTapeCell->data);
            curTapeCell = curTapeCell->next;
        }
    fclose(output);
}

