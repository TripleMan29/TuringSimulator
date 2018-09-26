#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Source.h"

void step(
        struct iterator *tape,
        struct listOfStates *states,
        char voidSymbol, int numOfStep, int *curState, struct state *curStateCell) {
    numOfStep++;

    //находим состояние
    struct listOfStates *curListOfStatesCell = states;
    while (curListOfStatesCell != NULL && curListOfStatesCell->stateNumb != *curState) curListOfStatesCell = curListOfStatesCell->nextState;
    if(curListOfStatesCell == NULL) {
        printf("No suitable state on step num.%i.\n", numOfStep);
        exit(1);
    }

    //ищем подходящую часть состояния
    curStateCell = curListOfStatesCell->thisState;
    struct iterator *curListOfTapeCell = tape;
    while (curListOfTapeCell != NULL) {
        char *curCondition = strdup(curStateCell->curCondition);

        //сравнение condition с tape
        if (curCondition == NULL) {
            printf("Less curCondition on step num.%i", numOfStep);
            exit(1);
        }
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
    while (curListOfTapeCell != NULL) {
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
                    printf("Can't make left step on step num.%i", numOfStep);
                    exit(1);
                }
                break;
            case 'R':
                if (curTapeCell->next == NULL) {
                    struct tapeCell *newTapeCell = (struct tapeCell *) malloc(sizeof(*newTapeCell));
                    newTapeCell->next = NULL;
                    newTapeCell->data = voidSymbol;
                    newTapeCell->prev = curTapeCell;
                    newTapeCell->position = curTapeCell->position + 1;
                    curTapeCell->next = newTapeCell;
                }
                curListOfTapeCell->curPosition = curTapeCell->next->position;
                curListOfTapeCell->curSymbol = curTapeCell->next->data;
                break;
            default:
                if (*stepDir != 'S') {
                    printf("Wrong step condition in step num.%i.", numOfStep);
                    exit(1);
                }
                curListOfTapeCell->curSymbol = curTapeCell->data;
                break;
        }

        curListOfTapeCell = NULL;
        free(newData);
        free(stepDir);
    }

    *curState = curStateCell->nextState;
    free(nextCondition);
}

