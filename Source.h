#ifndef TURINGMAFORONETAPE_SOURCE_H
#define TURINGMAFORONETAPE_SOURCE_H

struct iterator
{
    char curSymbol; //символ под кареткой
    int curPosition; //позиция каретки
    struct tapeCell* thisTapeCell; //указатель на первый элемент ленты
};

struct tapeCell //ячейка ленты
{
    int position; //позиция данной ячейки на ленте
    char data; //символ ячейки
    struct tapeCell* next; //указатель на следующую ячейку ленты
    struct tapeCell* prev; //указатель на предыдущую ячейку ленты
};

struct listOfStates
{
    int stateNumb; //номер состояния
    struct state* thisState; //указатель на ячейку с состоянием перехода
    struct listOfStates* nextState; //указатель на следующее состояние
};

struct state { //ячейка состояния
    char* curCondition; //текущий символ под кареткой
    char* newCondition; //символ, который необходимо напечатать под кареткой
    int nextState; //следующее состояние, в которое необходимо перейти
    struct state* next; //указатель на следующую ячейку
};

char *strcut(char *string, int fromIndex, int toIndex);
void splitState(char state[], struct listOfStates *states);
void printIssues();
void printCurState(struct iterator *tape, int numOfStep, int curState);
void printTape(struct iterator *tape);
struct listOfStates* readDescription(char *file, struct listOfStates *states, int *curState);
struct iterator* readTape(char *fileName, char voidSymbol);
void foutCondition(char *file, struct iterator *tape, int numOfStep);
void step(struct iterator *tape, struct listOfStates *states, char voidSymbol, int numOfStep, int *curState, struct state *curStateCell);

#endif //TURINGMAFORONETAPE_SOURCE_H
