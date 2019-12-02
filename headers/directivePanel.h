#ifndef directivePanel

#define directivePanel

void A_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], int *memory, MemLabel *memoryLabels, int *numberOfVars, char *stateRegister, int *arrowMemory)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] += findMemoryValue(memory, memoryLabels, numberOfVars, words[2], registers, arrowMemory);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void AR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] += registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void S_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], int *memory, MemLabel *memoryLabels, int *numberOfVars, char *stateRegister, int *arrowMemory)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] -= findMemoryValue(memory, memoryLabels, numberOfVars, words[2], registers, arrowMemory);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void SR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] -= registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void M_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], int *memory, MemLabel *memoryLabels, int *numberOfVars, char *stateRegister, int *arrowMemory)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] *= findMemoryValue(memory, memoryLabels, numberOfVars, words[2], registers, arrowMemory);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void MR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    int regIndex = parseToDecimal(words[1]);
    registers[regIndex] *= registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void D_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], int *memory, MemLabel *memoryLabels, int *numberOfVars, char *stateRegister, int *arrowMemory)
{
    int memValHandler = findMemoryValue(memory, memoryLabels, numberOfVars, words[2], registers, arrowMemory);
    if (memValHandler)
    {
        int regIndex = parseToDecimal(words[1]);
        registers[regIndex] /= memValHandler;
        switchRegisterStatus(stateRegister, registers[regIndex]);
    }
    else
    {
        printDividingZeroError();
        strcpy(stateRegister, ERROR_STATUS);
    }
}

void DR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    if (registers[parseToDecimal(words[2])])
    {
        int regIndex = parseToDecimal(words[1]);
        registers[regIndex] /= registers[parseToDecimal(words[2])];
        switchRegisterStatus(stateRegister, registers[regIndex]);
    }
    else
    {
        printDividingZeroError();
        strcpy(stateRegister, ERROR_STATUS);
    }
}

void C_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], int *memory, MemLabel *memoryLabels, int *numberOfVars, char *stateRegister, int *arrowMemory)
{
    int returnedValue = registers[parseToDecimal(words[1])] - findMemoryValue(memory, memoryLabels, numberOfVars, words[2], registers, arrowMemory);
    switchRegisterStatus(stateRegister, returnedValue);
}

void CR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    int returnedValue = registers[parseToDecimal(words[1])] - registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, returnedValue);
}

void J_directive(char (*words)[MAX_WORD_LINE_LENGTH], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished)
{
    if (stringsToBeSame(words[1], ENDING_WORDS)) {printEndingWords(); *isFinished = true;}
    else *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
}

void JZ_directive(char (*words)[MAX_WORD_LINE_LENGTH], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, ZERO_STATUS))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS)) {printEndingWords(); *isFinished = true;}
        else *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
    }
}

void JP_directive(char (*words)[MAX_WORD_LINE_LENGTH], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, POSITIVE_STATUS))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS)) {printEndingWords(); *isFinished = true;}
        else *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
    }
}

void JN_directive(char (*words)[MAX_WORD_LINE_LENGTH], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, NEGATIVE_STATUS))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS)) {printEndingWords(); *isFinished = true;}
        else *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
    }
}

void L_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], int *memory, MemLabel *memoryLabels, int *numberOfVars, int *arrowMemory)
{
    registers[parseToDecimal(words[1])] = findMemoryValue(memory, memoryLabels, numberOfVars, words[2], registers, arrowMemory);
}

void LA_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], int *memory, MemLabel *memoryLabels, int *numberOfVars, int *arrowMemory)
{
    registers[parseToDecimal(words[1])] = (intptr_t)findMemoryAddress(memory, memoryLabels, numberOfVars, words[2], registers, arrowMemory);
}

void LR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH])
{
    registers[parseToDecimal(words[1])] = registers[parseToDecimal(words[2])];
}

void ST_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], int *memory, MemLabel *memoryLabels, int *numberOfVars, int *arrowMemory)
{
    char secondWord[COMMON_WORD_LENGTH];
    strcpy(secondWord, words[2]);
    if ((int)secondWord[strlen(secondWord) - 1] == LINEFEED_ASCII) secondWord[strlen(secondWord) - 1] = NOTHING_CHAR;

    if (secondWord[strlen(secondWord) - 1] == CLOSE_BRACKET_CHAR)
    {
        int *secWordHandler;
        secWordHandler = parseSecondWord(secondWord, registers);
        *secWordHandler = registers[parseToDecimal(words[1])];
        return;
    }
    memory[findMemoryIndex(memoryLabels, numberOfVars, words[2], arrowMemory)] = registers[parseToDecimal(words[1])];
}

void DC_directive(char (*words)[MAX_WORD_LINE_LENGTH], int lineIndex, Label *labels, int labelLength, int **memory, 
                  MemLabel *memoryLabels, int *currMemLabelLength, int *numberOfVars, int *arrowMemory)
{
    char newNumberName[COMMON_WORD_LENGTH];
    strcpy(newNumberName, labels[findLabelIndexByLine(labels, lineIndex, labelLength)].name);
    *arrowMemory = *numberOfVars;
    if (isArrayInitialization(words[1]))
    {
        char arraySizeString[COMMON_WORD_LENGTH];
        char wordWithoutSize[COMMON_WORD_LENGTH];
        int arraySize;
        int newNumberValue;
        int i = 0;
        int j = 0;
        int k = 0;
        while (words[1][i] != STAR_CHAR) arraySizeString[j++] = words[1][i++];
        while (j < COMMON_WORD_LENGTH) arraySizeString[j++] = NOTHING_CHAR;
        arraySize = parseToDecimal(arraySizeString);
        while (i < COMMON_WORD_LENGTH) wordWithoutSize[k++] = words[1][++i];
        while (k < COMMON_WORD_LENGTH) wordWithoutSize[k++] = NOTHING_CHAR;

        newNumberValue = extractValueFromIntegerString(wordWithoutSize);
        *numberOfVars = *numberOfVars + arraySize;
        *memory = (int *)realloc(*memory, *numberOfVars * sizeof(int));
        for (i = 0; i < arraySize; i++) (*memory)[*numberOfVars - arraySize + i] = newNumberValue;
        if (strlen(newNumberName)) 
        {
        strcpy(memoryLabels[*currMemLabelLength].label, newNumberName);
        memoryLabels[*currMemLabelLength].memIndex = *numberOfVars - arraySize;
        *currMemLabelLength = *currMemLabelLength + 1;
        }
    }
    else
    {
        int newNumberValue = extractValueFromIntegerString(words[1]);
        *numberOfVars = *numberOfVars + 1;
        *memory = (int *)realloc(*memory, *numberOfVars * sizeof(int));
        if (strlen(newNumberName)) 
        {
        strcpy(memoryLabels[*currMemLabelLength].label, newNumberName);
        memoryLabels[*currMemLabelLength].memIndex = *numberOfVars - 1;
        *currMemLabelLength = *currMemLabelLength + 1;
        }
        (*memory)[*numberOfVars - 1] = newNumberValue;
    }
}

void DS_directive(char (*words)[MAX_WORD_LINE_LENGTH], int lineIndex, Label *labels, int labelLength, int *memory, MemLabel *memoryLabels, int *currMemLabelLength, int *numberOfVars, int *arrowMemory)
{
    char newNumberName[COMMON_WORD_LENGTH];
    *arrowMemory = *numberOfVars;
    strcpy(newNumberName, labels[findLabelIndexByLine(labels, lineIndex, labelLength)].name);
    if (isArrayInitialization(words[1]))
    {
        char arraySizeString[COMMON_WORD_LENGTH];
        char wordWithoutSize[COMMON_WORD_LENGTH];
        int newNumberValue;
        int arraySize;
        int i = 0;
        int j = 0;
        int k = 0;
        while (words[1][i] != STAR_CHAR) arraySizeString[j++] = words[1][i++];
        while (j < COMMON_WORD_LENGTH) arraySizeString[j++] = NOTHING_CHAR;
        arraySize = parseToDecimal(arraySizeString);
        *numberOfVars = *numberOfVars + arraySize;
        memory = (int *)realloc(memory, *numberOfVars * sizeof(int));
        if (strlen(newNumberName)) 
        {
        strcpy(memoryLabels[*currMemLabelLength].label, newNumberName);
        memoryLabels[*currMemLabelLength].memIndex = *numberOfVars - arraySize;
        *currMemLabelLength = *currMemLabelLength + 1;
        }
    }
    else
    {
        *numberOfVars = *numberOfVars + 1;
        memory = (int *)realloc(memory, *numberOfVars * sizeof(int));
        if (strlen(newNumberName)) 
        {
        strcpy(memoryLabels[*currMemLabelLength].label, newNumberName);
        memoryLabels[*currMemLabelLength].memIndex = *numberOfVars - 1;
        *currMemLabelLength = *currMemLabelLength + 1;
        }
    }
}

#endif