#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Source.h"


struct listOfStates* readDescription(char *file, struct listOfStates *states, int *curState) {
    //открываем файл
    FILE *input;
    input = fopen(file, "r");
    if (input == NULL) {
        printf("File \"%s\" can't be open", file);
        exit(1);
    }

    char tmpLine[1280000];

    //считываем начальное состояние
    fgets(tmpLine, sizeof(tmpLine), input);
    *curState = atoi(strcut(tmpLine,1,strlen(tmpLine)));
    if (*curState == 0) {
        printf("Wrong start state.");
        exit(1);
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
    char *result = strdup(string);
    if (toIndex > strlen(string) + 1)
        toIndex = strlen(string) + 1;
    int length = toIndex - fromIndex;
    if (length < 0) return "";
    if (length == 0) result[0] = string[fromIndex];
    for (int i = fromIndex; i < toIndex; ++i) {
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
    newListOfStatesCell->nextState = NULL;

    //определяем номер состояния
    if (state[strlen(state)] == '\n') state = strcut(state, 0, strlen(state) - 1); // избавляемся от переноса строки
    char *statePart = strdup(state);
    statePart = strtok(statePart, " ");
    state = strcut(state, strlen(statePart) + 1, strlen(state));
    newListOfStatesCell->stateNumb = strtol(strcut(statePart, 1, strlen(statePart) - 1), NULL, 0);

    struct state *prevStateCell = NULL;
    strcpy(statePart, state);
    statePart = strtok(statePart, " ");
    state = strcut(state, strlen(statePart) + 1, strlen(state));
    while (statePart != NULL) {
        struct state *newStateCell = (struct state *) malloc(sizeof(*newStateCell));
        if (prevStateCell == NULL) newListOfStatesCell->thisState = newStateCell;
        else prevStateCell->next = newStateCell;


        newStateCell->curCondition = strdup(strtok(statePart, "->"));
        newStateCell->newCondition = strdup(strtok(NULL, "->"));
        char *newState = strtok(NULL, "->");
        newState = strcut(newState, 1, strlen(newState) - 1);
        newStateCell->nextState = strtol(newState, NULL, 0);
        newStateCell->next = NULL;

        prevStateCell = newStateCell;
        strcpy(statePart, state);
        statePart = strtok(statePart, " ");
        if (statePart != NULL) state = strcut(state, strlen(statePart) + 1, strlen(state));
    }

    if (newListOfStatesCell != states) {
        struct listOfStates *curListOfStates = states;
        while (curListOfStates->nextState != NULL) curListOfStates = curListOfStates->nextState;
        curListOfStates->nextState = newListOfStatesCell;
    }

    free(statePart);
}

