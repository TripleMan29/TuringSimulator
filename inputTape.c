#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Source.h"

struct iterator *readTape(char *fileName, char voidSymbol) {

    FILE *input;
    input = fopen(fileName, "r");
    if (input == NULL) {
        printf("Error 2.\nFile \"%s\" can't be open.", fileName);
        exit(2);
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


    int length;

    fseek(input, 0, SEEK_END);
    length = ftell(input);
    fseek(input, 0, SEEK_SET);
    char tape[length];
    
    //проверка на содержание ленты
    if (!fgets(tape, sizeof(tape), input)) {
        printf("Error 4.\nThe file %s is empty.", fileName);
        exit(4);
    }
        char *tapePart;

        //считываем положение каретки
        int i = 0;
        while (tape[i] != 'V' && tape[i] != '\n' && tape[i] != '\0') {
            i++;
        }

        //проверка на отсутствие каретки
        if (tape[i] == '\n' || tape[i] == '\0') {
            printf("Error 5.\nNo pointer (V).");
            exit(5);
        }

        newListOfTapeCell->curPosition = i + 1;

        fgets(tape, sizeof(tape), input);

        //записываем ленту
        tapePart = tape;
        if (tapePart[strlen(tapePart) - 1] == '\n') tapePart = strcut(tapePart, 0, strlen(tapePart) - 2);

        //проверка на вхождение каретки в ленту
        if (i >= strlen(tapePart)) {
            printf("Error 6.\nPointer out of tape(V).");
            exit(6);
        }
        for (int j = 0; j < strlen(tapePart); ++j) {

            if (j == newListOfTapeCell->curPosition - 1) {
                newListOfTapeCell->curSymbol = tapePart[j];
            }
            struct tapeCell *curTapeCell = newListOfTapeCell->thisTapeCell;
            while (curTapeCell->next != NULL) curTapeCell = curTapeCell->next;
            curTapeCell->data = tapePart[j];

            //добавляем крайний пустой символ
            if(j < strlen(tapePart) - 1) {
                struct tapeCell *voidCell = (struct tapeCell *) malloc(sizeof(*voidCell));
                voidCell->next = NULL;
                voidCell->data = voidSymbol;
                voidCell->prev = curTapeCell;
                voidCell->position = (curTapeCell->position + 1);
                curTapeCell->next = voidCell;
            }
        }
        fclose(input);
    return newListOfTapeCell;
}

