#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "headers/settings.h"
#include "headers/util.h"
#include "headers/directivePanel.h"
#include "headers/direcitveController.h"

void initializeLine(int lineNumber, char *codeLine, char (*words)[16], Label *labels, int *labelLength)
{
    // printf("initializing line %d\n", lineNumber);
    // char words[16][16];
    splitLineIntoWords(codeLine, words);

    // check is there a label
    if (!(isDirective(words[0])))
    {
        // printf("words[0] is %d  ", strlen(words[0]));
        saveLabel(lineNumber, words[0], labels, &labelLength);
        removeLabelFromWords(words);
    }
}

void initializeProgram(char (*codeLines)[256], char (*words)[16][16], int codeLength, Label *labels, int *labelLength)
{
    printf("Initializing...\n");

    for (int i = 0; i < codeLength; i++)
        initializeLine(i, codeLines[i], words[i], labels, labelLength);

    printf("Program initialized succesfully\n");
}

void showLabels(Label *labels, int *labelLength)
{
    printf("Labels:\n");
    for (int i = 0; i < *labelLength; i++)
        printf("Name: %s, line: %d\n", labels[i].name, labels[i].lineIndex);
}

void showRegisters(int *registers)
{
    printf("Registers:\n");
    for (int i = 0; i < 16; i++)
        printf("Register #%d:   %d\n", i, registers[i]);
}

void showMemory(Number *memory, int numberOfVars) 
{
    printf("Memory variables:\n");
    for (int i = 0; i < numberOfVars; i++)
        printf("%s  %d\n", memory[i].name, memory[i].value); 
}

int main()
{
    FILE *file;
    char codeLines[MAX_CODE_LENGTH][MAX_CODELINE_LENGTH];
    char words[MAX_CODE_LENGTH][16][16];
    Label labels[128];
    int labelLength = 0;
    int numberOfVars = 0;
    int registers[16];
    char stateRegister[2];
    strcpy(stateRegister, STATUS[0]);
    file = fopen("src/sample.txt", "r");
    Number *memory = (Number *)malloc(1);
    if (file != NULL)
    {
        printf("File loaded\n");
    }
    else
    {
        printf("Cannot find parseable file\n");
        return 0;
    };

    int codeLength = 0;
    char codeLineHandler[64];

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
            printf("WARNING: There is empty line in given file. It will cause line numeration change");
        }
    };

    fclose(file);
    initializeProgram(codeLines, words, codeLength, labels, &labelLength);
    registers[13] = 2;
    showRegisters(registers);
    printf("Register status is  %s\n", stateRegister);
    executeLine(1, words[0], registers, labels, labelLength, memory, &numberOfVars, stateRegister);
    executeLine(2, words[1], registers, labels, labelLength, memory, &numberOfVars, stateRegister);
    executeLine(3, words[2], registers, labels, labelLength, memory, &numberOfVars, stateRegister);
    executeLine(4, words[3], registers, labels, labelLength, memory, &numberOfVars, stateRegister);
    executeLine(5, words[4], registers, labels, labelLength, memory, &numberOfVars, stateRegister);
    printf("Register status is  %s\n", stateRegister);
    showMemory(memory, numberOfVars);
    showRegisters(registers);
    // showLabels(labels, &labelLength);
    return 0;
}