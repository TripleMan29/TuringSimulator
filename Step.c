#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Source.h"

void step(
        struct iterator *tape,
        struct listOfStates *states, int numOfStep, int *curState, struct state *curStateCell) {

    //находим состояние
    while (states != NULL && states->stateNumb != *curState) states = states->nextState;
    if(states == NULL) {
        printf("Error 8.\nNo suitable state on step num.%i.", numOfStep);
        exit(8);
    }

    //ищем подходящую часть состояния
    curStateCell = states->thisState;
    struct iterator *curListOfTapeCell = tape;
    while (curListOfTapeCell != NULL) {
        char *curCondition = strdup(curStateCell->curCondition);

        //сравнение condition с tape
        if (curListOfTapeCell->curSymbol != *curCondition) {

            curStateCell = curStateCell->next;
            free(curCondition);
        } else{
            curListOfTapeCell = NULL;
            free(curCondition);
        }
    }

    char *nextCondition = strdup(curStateCell->newCondition);
    curListOfTapeCell = tape;

        //доходим до положения каретки
        struct tapeCell *curTapeCell = curListOfTapeCell->thisTapeCell;
        while (curListOfTapeCell->curPosition != curTapeCell->position) curTapeCell = curTapeCell->next;

        char *newData = strdup(nextCondition);
        newData = strtok(newData, ",");
        curTapeCell->data = *newData;
        nextCondition = strcut(nextCondition, 2, strlen(nextCondition));

        char *stepDir = strdup(nextCondition);
        stepDir = strtok(stepDir, ";");
        switch (*stepDir) {
            case 'L':
                if (curTapeCell->prev != NULL) {
                    curListOfTapeCell->curPosition = curTapeCell->prev->position;
                    curListOfTapeCell->curSymbol = curTapeCell->prev->data;
                } else {
                    printf("Error 10.\nCan't make left step on step num.%i.", numOfStep);
                    exit(10);
                }
                break;
            case 'R':
                if (curTapeCell->next != NULL) {
                    curListOfTapeCell->curPosition = curTapeCell->next->position;
                    curListOfTapeCell->curSymbol = curTapeCell->next->data;
                } else{
                    printf("Error 12.\nCan't make right step on step num.%i.", numOfStep);
                    exit(12);
                }

                break;
            default:
                if (*stepDir != 'S') {
                    printf("Error 11.\nWrong step condition in step num.%i.", numOfStep);
                    exit(11);
                }
                curListOfTapeCell->curSymbol = curTapeCell->data;
                break;
        }

        free(newData);
        free(stepDir);


    *curState = curStateCell->nextState;
    free(nextCondition);
}

