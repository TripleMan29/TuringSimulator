#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Source.h"


struct listOfStates* readDescription(char *file, struct listOfStates *states, int *curState) {
    //открываем файл
    FILE *input;
    input = fopen(file, "r");
    if (input == NULL) {
        printf("Error 2.\nFile \"%s\" can't be open.", file);
        exit(2);
    }
    int length;

    fseek(input, 0, SEEK_END);
    length = ftell(input);
    fseek(input, 0, SEEK_SET);
    char tmpLine[length];

    //считываем начальное состояние
    fgets(tmpLine, sizeof(tmpLine), input);
    *curState = strtol(strcut(tmpLine,1,strlen(tmpLine) - 1), NULL, 0);
    if (*curState == 0) {
        printf("Error 3.\nWrong start state.");
        exit(3);
    }


    states = (struct listOfStates *) malloc(sizeof(*states));
    states->stateNumb = 1;
    states->nextState = NULL;
    states->thisState = NULL;
    //считываем состояния
    while (fgets(tmpLine, sizeof(tmpLine), input)) {
        splitState(tmpLine, states);
    }

    fclose(input);
    return states;
}

char *strcut(char *string, int fromIndex, int toIndex) {
    if (strlen(string) == 0)
        return string;
    char *result = string;
    if (toIndex > (int)strlen(string) - 1)
        toIndex = strlen(string) - 1;
    int length = toIndex - fromIndex + 1;
    if (length < 1) return "";
    if (length == 1) result[0] = string[fromIndex];
    for (int i = fromIndex; i <= toIndex; ++i) {
        result[i - fromIndex] = string[i];
    }
    result[length] = '\0';
    return result;
}

void splitState(char state[], struct listOfStates *states) {

    struct listOfStates *newListOfStatesCell;
    if (states->thisState == NULL) {
        newListOfStatesCell = states;
    } else {
        newListOfStatesCell = (struct listOfStates *) malloc(sizeof(*newListOfStatesCell));
    }

    //определяем номер состояния
    char *statePart = strdup(state);
    statePart = strtok(statePart, " ");
    state = strcut(state, strlen(statePart) + 1, strlen(state) - 1);
    newListOfStatesCell->stateNumb = strtol(strcut(statePart, 1, strlen(statePart) - 1), NULL, 0);

    strcpy(statePart, state);
    statePart = strtok(statePart, " ");
    state = strcut(state, strlen(statePart) + 1, strlen(state) - 1);

    struct state *prevStateCell = NULL;
    while (statePart != NULL) {
        struct state *newStateCell = (struct state *) malloc(sizeof(*newStateCell));
        if (prevStateCell == NULL) newListOfStatesCell->thisState = newStateCell;
        else prevStateCell->next = newStateCell;


        newStateCell->curCondition = strdup(strtok(statePart, "->"));
        newStateCell->newCondition = strdup(strtok(NULL, "->"));
        char *newState = strtok(NULL, "->");
        if(newState == NULL){
            printf("Error 9.\nLess curCondition on step num.");
            exit(9);
        }
        newState = strcut(newState, 1, strlen(newState) - 1);
        newStateCell->nextState = strtol(newState, NULL, 0);
        newStateCell->next = NULL;

        prevStateCell = newStateCell;
        strcpy(statePart, state);
        statePart = strtok(statePart, " ");
        if (statePart != NULL) state = strcut(state, strlen(statePart) + 1, strlen(state) - 1);
    }

    if (newListOfStatesCell != states) {
        while (states->nextState != NULL) states = states->nextState;
        states->nextState = newListOfStatesCell;
     }

    free(statePart);
}

