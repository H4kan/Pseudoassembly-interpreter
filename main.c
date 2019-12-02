/* Pseudoassembly interpreter 1.0 */
/* Author: Szymon Sieradzki */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "headers/settings.h"
#include "headers/outputFormatter.h"
#include "headers/util.h"
#include "headers/directivePanel.h"
#include "headers/direcitveController.h"

void initializeLine(int lineNumber, char *codeLine,
                    char (*words)[MAX_WORD_LINE_LENGTH],
                    Label *labels, int *labelLength,
                    char (*terminalWords)[MAX_WORD_LINE_LENGTH]);
void initializeProgram(char (*codeLines)[MAX_CODELINE_LENGTH],
                       char (*words)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH],
                       int codeLength, Label *labels,
                       int *labelLength, char (*terminalWords)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH]);
void executeProgram(char (*words)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH],
                    int *registers, Label *labels,
                    int labelLength, int **memory,
                    MemLabel memoryLabels[MAX_CODE_LENGTH],
                    int *currMemLabelLength, int *numberOfVars, char *stateRegister,
                    char codeLines[MAX_CODE_LENGTH][MAX_CODELINE_LENGTH],
                    int codeLength, char *executionMode,
                    char (*terminalWords)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH]);
int main()
{
    /* DECLARATION SECTION START */
    int **memory = malloc(sizeof(intptr_t));
    MemLabel memoryLabels[MAX_CODE_LENGTH];

    FILE *file;
    Label labels[MAX_CODE_LENGTH];
    char fileName[LONG_WORD_LENGTH];
    char codeLines[MAX_CODE_LENGTH][MAX_CODELINE_LENGTH];
    char words[MAX_CODE_LENGTH][MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH];
    char terminalWords[MAX_CODE_LENGTH][MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH];
    char stateRegister[DBL_CHAR_LENGTH];
    char sourcePath[MAX_SOURCE_PATH_LENGTH];
    char codeLineHandler[MAX_CODELINE_LENGTH];
    char executionMode[COMMON_WORD_LENGTH];

    int registers[NUMBER_OF_REGS];
    int labelLength = 0;
    int currMemLabelLength = 0;
    int numberOfVars = 0;
    int codeLength = 0;
    /* DECLARATION SECTION END */
    setvbuf(stdout, 0, _IONBF, 0); // fix MinGW scanf issue
    strcpy(sourcePath, SOURCE_DIRECTORY_PATH);
    strcpy(stateRegister, ZERO_STATUS);
    printFileChoose();
    fgets(fileName, LONG_WORD_LENGTH, stdin);
    fileName[strlen(fileName) - 1] = NOTHING_CHAR;
    if (!strlen(fileName)){printDefaultFileChoose(); strcpy(fileName, DEFAULT_SOURCE_FILENAME);}
    strcat(sourcePath, fileName);
    file = fopen(sourcePath, "r");
    if (file != NULL) printFileLoadSuccess();
    else { printFileLoadError(); return 0;}
    while (!feof(file))
    {
        fgets(codeLineHandler, MAX_CODELINE_LENGTH, file);
        if (strlen(codeLineHandler) > 1)
        {
            strcpy(codeLines[codeLength], codeLineHandler);
            codeLength++;
        }
        else printEmptyLineWarning();
    };
    fclose(file);
    initializeProgram(codeLines, words, codeLength, labels, &labelLength, terminalWords);
    printExecutionChoose();
    fgets(executionMode, COMMON_WORD_LENGTH, stdin);
    *memory = (int *)malloc(1);
    if (stringsToBeSame(executionMode, DEBUG_MODE)) printDebugModeOn();
    else if (stringsToBeSame(executionMode, DEFAULT_MODE)) printDebugModeOff();
    else { printInvalidArgument(); printDebugModeOff();}
    executeProgram(words, registers,
                   labels, labelLength,
                   memory, memoryLabels,
                   &currMemLabelLength, 
                   &numberOfVars, stateRegister, 
                   codeLines, codeLength,
                   executionMode, terminalWords);
    free(memory);
    return 0;
}

void initializeLine(int lineNumber,
                    char *codeLine,
                    char (*words)[MAX_WORD_LINE_LENGTH],
                    Label *labels,
                    int *labelLength,
                    char (*terminalWords)[MAX_WORD_LINE_LENGTH])
{
    splitLineIntoWords(codeLine, words);
    splitLineIntoWords(codeLine, terminalWords);
    if (!(isDirective(words[0]))) // check is there a label
    {
        saveLabel(lineNumber, words[0], labels, &labelLength);
        removeLabelFromWords(words);
    }
}

void initializeProgram(char (*codeLines)[MAX_CODELINE_LENGTH],
                       char (*words)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH],
                       int codeLength, Label *labels, int *labelLength,
                       char (*terminalWords)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH])
{
    int i;
    printInitializationInfo();
    for (i = 0; i < codeLength; i++)
        initializeLine(i, codeLines[i], words[i], labels, labelLength, terminalWords[i]);
    printInitializationSuccess();
}
void executeProgram(char (*words)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH],
                    int *registers, Label *labels,
                    int labelLength, int **memory,
                    MemLabel memoryLabels[MAX_CODE_LENGTH],
                    int *currMemLabelLength, int *numberOfVars,
                    char *stateRegister,
                    char codeLines[MAX_CODE_LENGTH][MAX_CODELINE_LENGTH],
                    int codeLength, char *executionMode,
                    char (*terminalWords)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH])
{
    int nextLineToExec = START_LINE_INDEX;
    int arrowMemory = 0;
    bool isFinished = false;
    bool trackRegisters = false;
    bool trackStatus = false;
    bool trackMemory = true;
    int i;
    for (i = 0; i < MAX_CODE_LENGTH; i++) memoryLabels[i].memIndex = -1;
    while (!isFinished && nextLineToExec <= codeLength)
    {
        printPanel(registers, stateRegister, 
        terminalWords, codeLines, 
        codeLength, nextLineToExec, 
        *memory, memoryLabels, 
        numberOfVars, arrowMemory);
        if (stringsToBeSame(executionMode, DEBUG_MODE)) commandController(executionMode, &isFinished);
        if (!isFinished) executeLine(
            words[nextLineToExec - 1], registers, 
            labels, labelLength, 
            memory, memoryLabels, 
            currMemLabelLength, numberOfVars, 
            stateRegister, &nextLineToExec, 
            &isFinished, &arrowMemory);
    }
}

