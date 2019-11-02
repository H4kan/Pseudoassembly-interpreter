#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "headers/settings.h"
#include "headers/util.h"
#include "headers/outputFormatter.h"
#include "headers/directivePanel.h"
#include "headers/direcitveController.h"

void initializeLine(int lineNumber, char *codeLine, char (*words)[16], Label *labels, int *labelLength)
{
    splitLineIntoWords(codeLine, words);

    // check is there a label
    if (!(isDirective(words[0])))
    {
        saveLabel(lineNumber, words[0], labels, &labelLength);
        removeLabelFromWords(words);
    }
}

void initializeProgram(char (*codeLines)[256], char (*words)[16][16], int codeLength, Label *labels, int *labelLength)
{
    printInitializationInfo();

    for (int i = 0; i < codeLength; i++)
        initializeLine(i, codeLines[i], words[i], labels, labelLength);

    printInitializationSuccess();
}

void executeProgram(char (*words)[16][16], int *registers, Label *labels, int labelLength, Number *memory, int *numberOfVars, char *stateRegister, int codeLength, char *executionMode)
{
    int nextLineToExec = START_LINE_INDEX;
    bool isFinished = false;
    bool trackRegisters = false;
    bool trackStatus = false;
    bool trackMemory = false;
    while (!isFinished && nextLineToExec <= codeLength)
    {
        if (stringsToBeSame(executionMode, DEBUG_MODE))
        {
            commandController(&trackRegisters, &trackStatus, &trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, &isFinished);
        }
        if (!isFinished)
            executeLine(words[nextLineToExec - 1], registers, labels, labelLength, memory, numberOfVars, stateRegister, &nextLineToExec, &isFinished);
        if (stringsToBeSame(executionMode, DEBUG_MODE))
        {
            printTracked(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers);
        }
    }
    showStatus(stateRegister);
    showRegisters(registers);
}

int main()
{
    FILE *file;
    char fileName[16];
    char codeLines[MAX_CODE_LENGTH][MAX_CODELINE_LENGTH];
    char words[MAX_CODE_LENGTH][16][16];
    Label labels[128];
    int labelLength = 0;
    int numberOfVars = 0;
    int registers[16];
    char stateRegister[2];
    char sourcePath[16];
    int codeLength = 0;
    char codeLineHandler[64];
    char executionMode[16];

    // fix MinGW scanf issue
    setvbuf(stdout, 0, _IONBF, 0);
    strcpy(sourcePath, SOURCE_DIRECTORY_PATH);
    strcpy(stateRegister, ZERO_STATUS);
    printFileChoose();
    fgets(fileName, 16, stdin);
    fileName[strlen(fileName) - 1] = '\0';
    if (!strlen(fileName))
    {
        printDefaultFileChoose();
        strcpy(fileName, DEFAULT_SOURCE_FILENAME);
    }
    strcat(sourcePath, fileName);
    file = fopen(sourcePath, "r");
    Number *memory = (Number *)malloc(1);
    if (file != NULL)
    {
        printFileLoadSuccess();
    }
    else
    {
        printFileLoadError();
        return 0;
    };

    while (!feof(file))
    {
        fgets(codeLineHandler, 64, file);
        if (strlen(codeLineHandler) != 1)
        {
            strcpy(codeLines[codeLength], codeLineHandler);
            codeLength++;
        }
        else
        {
            printEmptyLineWarning();
        }
    };

    fclose(file);
    initializeProgram(codeLines, words, codeLength, labels, &labelLength);

    printExecutionChoose();
    fgets(executionMode, 16, stdin);
    if (stringsToBeSame(executionMode, DEBUG_MODE))
        printDebugModeOn();
    else if (stringsToBeSame(executionMode, DEFAULT_MODE))
        printDebugModeOff();
    else
    {
        printInvalidArgument();
        printDebugModeOff();
    }
    executeProgram(words, registers, labels, labelLength, memory, &numberOfVars, stateRegister, codeLength, executionMode);
    return 0;
}