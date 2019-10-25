#include <stdio.h>
#include "util.h"

#ifndef directivePanel
#define directivePanel

void A_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars)
{
    printf("executing A dir\n");
    registers[parseToDecimal(words[1])] += findMemoryValue(memory, numberOfVars, words[2]);
}

void AR_directive(int *registers, char (*words)[16])
{
    printf("executing AR dir\n");
    registers[parseToDecimal(words[1])] += registers[parseToDecimal(words[2])];
}

void S_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars)
{
    printf("executing S dir\n");
    registers[parseToDecimal(words[1])] -= findMemoryValue(memory, numberOfVars, words[2]);
}

void SR_directive(int *registers, char (*words)[16])
{
    printf("executing SR dir\n");
    registers[parseToDecimal(words[1])] -= registers[parseToDecimal(words[2])];
}

void M_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars)
{
    printf("executing M dir\n");
    registers[parseToDecimal(words[1])] *= findMemoryValue(memory, numberOfVars, words[2]);
}

void MR_directive(int *registers, char (*words)[16])
{
    printf("executing MR dir\n");
    registers[parseToDecimal(words[1])] *= registers[parseToDecimal(words[2])];
}

void D_directive(int *registers, char (*words)[16], Number *memory, int *numberOfVars)
{
    printf("executing D dir\n");
    if (findMemoryValue(memory, numberOfVars, words[2]))
        registers[parseToDecimal(words[1])] /= findMemoryValue(memory, numberOfVars, words[2]);
    else
        printf("ERROR: Dividing by zero");
}

void DR_directive(int *registers, char (*words)[16])
{
    printf("executing DR dir\n");
    if (!registers[parseToDecimal(words[2])])
        registers[parseToDecimal(words[1])] /= registers[parseToDecimal(words[2])];
    else
        printf("ERROR: Dividing by zero");
}

void C_directive()
{
    printf("ex C dir");
}

void CR_directive()
{
    printf("ex CR dir");
}

void J_directive()
{
    printf("ex J dir");
}

void JZ_directive()
{
    printf("ex JZ dir");
}

void JP_directive()
{
    printf("ex JP dir");
}

void JN_directive()
{
    printf("ex JN dir");
}

void L_directive()
{
    printf("ex L dir");
}

void LA_directive()
{
    printf("ex LA dir");
}

void LR_directive()
{
    printf("ex LR dir");
}

void ST_directive() 
{
    printf("ex ST dir");
}

void DC_directive(char (*words)[16], int lineIndex, Label *labels, int labelLength, Number *memory, int *numberOfVars)
{
    printf("executing DC dir\n");
    char newNumberName[16];
    strcpy(newNumberName, labels[findLabelIndex(labels, lineIndex, labelLength)].name);
    if (isArrayInitialization(words[1])) {
        char arraySizeString[16];
        char wordWithoutSize[16];
        int arraySize;
        int i = 0;
        int j = 0;
        int k = 0;
        while (words[1][i] != '*') {arraySizeString[j++] = words[1][i++]; }
        while (j < 16) {arraySizeString[j++] = '\0';}
        arraySize = parseToDecimal(arraySizeString);
        while (i < 16) { wordWithoutSize[k++] = words[1][++i];}
        while (k < 16) wordWithoutSize[k++] = '\0';
        int newNumberValue = extractValueFromIntegerString(wordWithoutSize);
        *numberOfVars = *numberOfVars + arraySize;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        Number newNumber = { .value = newNumberValue };
        for (int i = 0; i< arraySize; i++) {
            memory[*numberOfVars - arraySize + i] = newNumber;
        }
        strcpy(memory[*numberOfVars - arraySize].name, newNumberName);   
    } else {
    int newNumberValue = extractValueFromIntegerString(words[1]);
    *numberOfVars = *numberOfVars + 1;
    memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
    Number newNumber = { .value = newNumberValue };
    strcpy(newNumber.name, newNumberName);
    memory[*numberOfVars - 1] = newNumber;
    }
}

void DS_directive(char (*words)[16], int lineIndex, Label *labels, int labelLength, Number *memory, int *numberOfVars)
{
    printf("executing DS dir\n");
    char newNumberName[16];
    strcpy(newNumberName, labels[findLabelIndex(labels, lineIndex, labelLength)].name);
    if (isArrayInitialization(words[1])) {
        char arraySizeString[16];
        char wordWithoutSize[16];
        int arraySize;
        int i = 0;
        int j = 0;
        int k = 0;
        while (words[1][i] != '*') {arraySizeString[j++] = words[1][i++]; }
        while (j < 16) {arraySizeString[j++] = '\0';}
        arraySize = parseToDecimal(arraySizeString);
        while (i < 16) { wordWithoutSize[k++] = words[1][++i];}
        while (k < 16) wordWithoutSize[k++] = '\0';
        int newNumberValue = extractValueFromIntegerString(wordWithoutSize);
        *numberOfVars = *numberOfVars + arraySize;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        Number newNumber = { .value = newNumberValue };
        for (int i = 0; i< arraySize; i++) {
            memory[*numberOfVars - arraySize + i] = newNumber;
        }
        strcpy(memory[*numberOfVars - arraySize].name, newNumberName);   
    } else {
    int newNumberValue = extractValueFromIntegerString(words[1]);
    *numberOfVars = *numberOfVars + 1;
    memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
    Number newNumber = { .value = newNumberValue };
    strcpy(newNumber.name, newNumberName);
    memory[*numberOfVars - 1] = newNumber;
    }
}

#endif