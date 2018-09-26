#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Source.h"

struct iterator *readTape(char *fileName, char voidSymbol) {

    FILE *input;
    input = fopen(fileName, "r");
    if (input == NULL) {
        printf("File \"%s\" can't be open.\n", fileName);
        exit(1);
    }


    //создаём пустую ленту с одним пустым символом
    struct iterator *newListOfTapeCell = (struct iterator *) malloc(sizeof(*newListOfTapeCell));
    struct tapeCell *newTapeCell = (struct tapeCell *) malloc(sizeof(*newTapeCell));
    newTapeCell->data = voidSymbol;
    newTapeCell->next = NULL;
    newTapeCell->prev = NULL;
    newTapeCell->position = 1;
    newListOfTapeCell->thisTapeCell = newTapeCell;
    newListOfTapeCell->curSymbol = newTapeCell->data;
    newListOfTapeCell->curPosition = newTapeCell->position;

    char tape[1280000];
    //проверка на содержание ленты
    if (!fgets(tape, sizeof(tape), input)) {
        printf("The file is empty %s", fileName);
        exit(1);
    }
    do {
        char *tapePart;

        //считываем положение каретки
        int i = 0;
        while (tape[i] != 'V' && tape[i] != '\n' && tape[i] != '\0') {
            i++;
        }

        //проверка на отсутствие каретки
        if (tape[i] == '\n' || tape[i] == '\0') {
            printf("No pointer (V)\n");
            exit(1);
        }

        newListOfTapeCell->curPosition = i + 1;

        fgets(tape, sizeof(tape), input);

        //записываем ленту
        tapePart = tape;
        if (tapePart[strlen(tapePart) - 1] == '\n') tapePart = strcut(tapePart, 0, strlen(tapePart) - 1);

        //проверка на вхождение каретки в ленту
        if (i >= strlen(tapePart)) {
            printf("Pointer out of tape(V)");
            exit(1);
        }
        for (int j = 0; j < strlen(tapePart) - 1; ++j) {

            if (j == newListOfTapeCell->curPosition) {
                newListOfTapeCell->curSymbol = tapePart[j - 1];
            }
            struct tapeCell *curTapeCell = newListOfTapeCell->thisTapeCell;
            while (curTapeCell->next != NULL) curTapeCell = curTapeCell->next;
            curTapeCell->data = tapePart[j];

            //добавляем крайний пустой символ
            struct tapeCell *voidCell = (struct tapeCell *) malloc(sizeof(*voidCell));
            voidCell->next = NULL;
            voidCell->data = voidSymbol;
            voidCell->prev = curTapeCell;
            voidCell->position = (curTapeCell->position + 1);
            curTapeCell->next = voidCell;
        }
    } while (fgets(tape, sizeof(tape), input));
        fclose(input);
    return newListOfTapeCell;
}

