#include <stdio.h>
#include <stdint.h>
#include "util.h"

#ifndef directivePanel
#define directivePanel

void A_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars, char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] += findMemoryValue(memory, numberOfVars, words[2], registers);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void AR_directive(int *registers, char (*words)[16], char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] += registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void S_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars, char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] -= findMemoryValue(memory, numberOfVars, words[2], registers);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void SR_directive(int *registers, char (*words)[16], char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] -= registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void M_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars, char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] *= findMemoryValue(memory, numberOfVars, words[2], registers);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void MR_directive(int *registers, char (*words)[16], char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] *= registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void D_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars, char *stateRegister)
{
    if (findMemoryValue(memory, numberOfVars, words[2], registers))
    {
        int regIndex = parseToDecimal(words[1]);
        registers[regIndex] /= findMemoryValue(memory, numberOfVars, words[2], registers);
        switchRegisterStatus(stateRegister, registers[regIndex]);
    }
    else
    {
        printf(RED "ERROR: Dividing by zero\n" RESET);
        strcpy(stateRegister, STATUS[3]);
    }
}

void DR_directive(int *registers, char (*words)[16], char *stateRegister)
{
    if (!registers[parseToDecimal(words[2])])
    {
        int regIndex = parseToDecimal(words[1]);
        registers[regIndex] /= registers[parseToDecimal(words[2])];
        switchRegisterStatus(stateRegister, registers[regIndex]);
    }
    else
    {
        printf(RED "ERROR: Dividing by zero\n" RESET);
        strcpy(stateRegister, STATUS[3]);
    }
}

void C_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars, char *stateRegister)
{
    int returnedValue = registers[parseToDecimal(words[1])] - findMemoryValue(memory, numberOfVars, words[2], registers);
    switchRegisterStatus(stateRegister, returnedValue);
}

void CR_directive(int *registers, char (*words)[16], char *stateRegister)
{
    int returnedValue = registers[parseToDecimal(words[1])] - registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, returnedValue);
}

void J_directive(char (*words)[16], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished)
{
    if (stringsToBeSame(words[1], ENDING_WORDS))
    {
        printf(BLU "%s\n\n" RESET, ENDING_WORDS);
        *isFinished = true;
    }
    else
    {
        *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
    }
}

void JZ_directive(char (*words)[16], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, STATUS[0]))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS))
        {
            printf(BLU "%s\n\n" RESET, ENDING_WORDS);
            *isFinished = true;
        }
        else
        {
            *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
        }
    }
}

void JP_directive(char (*words)[16], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, STATUS[1]))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS))
        {
            printf(BLU "%s\n\n" RESET, ENDING_WORDS);
            *isFinished = true;
        }
        else
        {
            *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
        }
    }
}

void JN_directive(char (*words)[16], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, STATUS[2]))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS))
        {
            printf(BLU "%s\n\n" RESET, ENDING_WORDS);
            *isFinished = true;
        }
        else
        {
            *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
        }
    }
}

void L_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars)
{
    registers[parseToDecimal(words[1])] = findMemoryValue(memory, numberOfVars, words[2], registers);
}

void LA_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars)
{
    registers[parseToDecimal(words[1])] = (intptr_t)findMemoryAddress(memory, numberOfVars, words[2]);
}

void LR_directive(int *registers, char (*words)[16])
{
    registers[parseToDecimal(words[1])] = registers[parseToDecimal(words[2])];
}

void ST_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars)
{
    memory[findMemoryIndex(memory, numberOfVars, words[2])].value = registers[parseToDecimal(words[1])];
}

void DC_directive(char (*words)[16], int lineIndex, Label *labels, int labelLength, Number *memory, int *numberOfVars)
{
    char newNumberName[16];
    strcpy(newNumberName, labels[findLabelIndexByLine(labels, lineIndex, labelLength)].name);
    if (isArrayInitialization(words[1]))
    {
        char arraySizeString[16];
        char wordWithoutSize[16];
        int arraySize;
        int i = 0;
        int j = 0;
        int k = 0;
        while (words[1][i] != '*')
        {
            arraySizeString[j++] = words[1][i++];
        }
        while (j < 16)
        {
            arraySizeString[j++] = '\0';
        }
        arraySize = parseToDecimal(arraySizeString);
        while (i < 16)
        {
            wordWithoutSize[k++] = words[1][++i];
        }
        while (k < 16)
            wordWithoutSize[k++] = '\0';
        int newNumberValue = extractValueFromIntegerString(wordWithoutSize);
        *numberOfVars = *numberOfVars + arraySize;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        Number newNumber = {.value = newNumberValue};
        for (int i = 0; i < arraySize; i++)
        {
            memory[*numberOfVars - arraySize + i] = newNumber;
        }
        strcpy(memory[*numberOfVars - arraySize].name, newNumberName);
    }
    else
    {
        int newNumberValue = extractValueFromIntegerString(words[1]);
        *numberOfVars = *numberOfVars + 1;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        Number newNumber = {.value = newNumberValue};
        strcpy(newNumber.name, newNumberName);
        memory[*numberOfVars - 1] = newNumber;
    }
}

void DS_directive(char (*words)[16], int lineIndex, Label *labels, int labelLength, Number *memory, int *numberOfVars)
{
    char newNumberName[16];
    strcpy(newNumberName, labels[findLabelIndexByLine(labels, lineIndex, labelLength)].name);
    if (isArrayInitialization(words[1]))
    {
        char arraySizeString[16];
        char wordWithoutSize[16];
        int arraySize;
        int i = 0;
        int j = 0;
        int k = 0;
        while (words[1][i] != '*')
        {
            arraySizeString[j++] = words[1][i++];
        }
        while (j < 16)
        {
            arraySizeString[j++] = '\0';
        }
        arraySize = parseToDecimal(arraySizeString);
        while (i < 16)
        {
            wordWithoutSize[k++] = words[1][++i];
        }
        while (k < 16)
            wordWithoutSize[k++] = '\0';
        int newNumberValue = extractValueFromIntegerString(wordWithoutSize);
        *numberOfVars = *numberOfVars + arraySize;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        Number newNumber = {.value = newNumberValue};
        for (int i = 0; i < arraySize; i++)
        {
            memory[*numberOfVars - arraySize + i] = newNumber;
        }
        strcpy(memory[*numberOfVars - arraySize].name, newNumberName);
    }
    else
    {
        int newNumberValue = extractValueFromIntegerString(words[1]);
        *numberOfVars = *numberOfVars + 1;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        Number newNumber = {.value = newNumberValue};
        strcpy(newNumber.name, newNumberName);
        memory[*numberOfVars - 1] = newNumber;
    }
}

#endif