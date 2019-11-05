#ifndef directivePanel

#define directivePanel

void A_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], Number *memory, int *numberOfVars, char *stateRegister)
{
    /* DECLARATION SECTION START */
    int regIndex = parseToDecimal(words[1]);
    /* DECLARATION SECTION END */

    registers[regIndex] += findMemoryValue(memory, numberOfVars, words[2], registers);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void AR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    /* DECLARATION SECTION START */
    int regIndex = parseToDecimal(words[1]);
    /* DECLARATION SECTION END */

    registers[regIndex] += registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void S_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], Number *memory, int *numberOfVars, char *stateRegister)
{
    /* DECLARATION SECTION START */
    int regIndex = parseToDecimal(words[1]);
    /* DECLARATION SECTION END */

    registers[regIndex] -= findMemoryValue(memory, numberOfVars, words[2], registers);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void SR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    /* DECLARATION SECTION START */
    int regIndex = parseToDecimal(words[1]);
    /* DECLARATION SECTION END */

    registers[regIndex] -= registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void M_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], Number *memory, int *numberOfVars, char *stateRegister)
{
    /* DECLARATION SECTION START */
    int regIndex = parseToDecimal(words[1]);
    /* DECLARATION SECTION END */

    registers[regIndex] *= findMemoryValue(memory, numberOfVars, words[2], registers);
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void MR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    /* DECLARATION SECTION START */
    int regIndex = parseToDecimal(words[1]);
    /* DECLARATION SECTION END */

    registers[regIndex] *= registers[parseToDecimal(words[2])];
    switchRegisterStatus(stateRegister, registers[regIndex]);
}

void D_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], Number *memory, int *numberOfVars, char *stateRegister)
{
    if (findMemoryValue(memory, numberOfVars, words[2], registers))
    {
        /* DECLARATION SECTION START */
        int regIndex = parseToDecimal(words[1]);
        /* DECLARATION SECTION END */

        registers[regIndex] /= findMemoryValue(memory, numberOfVars, words[2], registers);
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
        /* DECLARATION SECTION START */
        int regIndex = parseToDecimal(words[1]);
        /* DECLARATION SECTION END */
        registers[regIndex] /= registers[parseToDecimal(words[2])];
        switchRegisterStatus(stateRegister, registers[regIndex]);
    }
    else
    {
        printDividingZeroError();
        strcpy(stateRegister, ERROR_STATUS);
    }
}

void C_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], Number *memory, int *numberOfVars, char *stateRegister)
{

    /* DECLARATION SECTION START */
    int returnedValue = registers[parseToDecimal(words[1])] - findMemoryValue(memory, numberOfVars, words[2], registers);
    /* DECLARATION SECTION END */
    switchRegisterStatus(stateRegister, returnedValue);
}

void CR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], char *stateRegister)
{
    /* DECLARATION SECTION START */
    int returnedValue = registers[parseToDecimal(words[1])] - registers[parseToDecimal(words[2])];
    /* DECLARATION SECTION END */

    switchRegisterStatus(stateRegister, returnedValue);
}

void J_directive(char (*words)[MAX_WORD_LINE_LENGTH], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished)
{
    if (stringsToBeSame(words[1], ENDING_WORDS))
    {
        printEndingWords();
        *isFinished = true;
    }
    else
    {
        *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
    }
}

void JZ_directive(char (*words)[MAX_WORD_LINE_LENGTH], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, ZERO_STATUS))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS))
        {
            printEndingWords();
            *isFinished = true;
        }
        else
        {
            *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
        }
    }
}

void JP_directive(char (*words)[MAX_WORD_LINE_LENGTH], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, POSITIVE_STATUS))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS))
        {
            printEndingWords();
            *isFinished = true;
        }
        else
        {
            // substracting one because it is added at the end of executeLine func
            *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
        }
    }
}

void JN_directive(char (*words)[MAX_WORD_LINE_LENGTH], Label *labels, int labelLength, int *nextLineToExec, bool *isFinished, char *stateRegister)
{
    if (stringsToBeSame(stateRegister, NEGATIVE_STATUS))
    {
        if (stringsToBeSame(words[1], ENDING_WORDS))
        {
            printEndingWords();
            *isFinished = true;
        }
        else
        {
            *nextLineToExec = labels[findLabelIndexByName(labels, words[1], labelLength)].lineIndex - 1;
        }
    }
}

void L_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], Number *memory, int *numberOfVars)
{
    registers[parseToDecimal(words[1])] = findMemoryValue(memory, numberOfVars, words[2], registers);
}

void LA_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], Number *memory, int *numberOfVars)
{
    registers[parseToDecimal(words[1])] = (intptr_t)findMemoryAddress(memory, numberOfVars, words[2], registers);
}

void LR_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH])
{
    registers[parseToDecimal(words[1])] = registers[parseToDecimal(words[2])];
}

void ST_directive(int *registers, char (*words)[MAX_WORD_LINE_LENGTH], Number *memory, int *numberOfVars)
{
    char secondWord[strlen(words[2])];
    strcpy(secondWord, words[2]);
    if ((int)secondWord[strlen(secondWord) - 1] == LINEFEED_ASCII)
        secondWord[strlen(secondWord) - 1] = NOTHING_CHAR;

    if (secondWord[strlen(secondWord) - 1] == CLOSE_BRACKET_CHAR)
    {
        intptr_t *secWordHandler;
        secWordHandler = parseSecondWord(secondWord, registers);
        *secWordHandler = registers[parseToDecimal(words[1])];
        return;
    }
    memory[findMemoryIndex(memory, numberOfVars, words[2])].value = registers[parseToDecimal(words[1])];
    // (findMemoryValue(memory, numberOfVars. words[2], registers)).value = registers[parseToDecimal(words[1])];
}

void DC_directive(char (*words)[MAX_WORD_LINE_LENGTH], int lineIndex, Label *labels, int labelLength, Number *memory, int *numberOfVars)
{
    /* DECLARATION SECTION START */
    char newNumberName[COMMON_WORD_LENGTH];
    /* DECLARATION SECTION END */

    strcpy(newNumberName, labels[findLabelIndexByLine(labels, lineIndex, labelLength)].name);
    if (isArrayInitialization(words[1]))
    {
        /* DECLARATION SECTION START */
        char arraySizeString[COMMON_WORD_LENGTH];
        char wordWithoutSize[COMMON_WORD_LENGTH];
        Number newNumber;
        int arraySize;
        int newNumberValue;
        int i = 0;
        int j = 0;
        int k = 0;
        /* DECLARATION SECTION END */

        while (words[1][i] != STAR_CHAR)
        {
            arraySizeString[j++] = words[1][i++];
        }

        while (j < COMMON_WORD_LENGTH)
        {
            arraySizeString[j++] = NOTHING_CHAR;
        }
        arraySize = parseToDecimal(arraySizeString);

        while (i < COMMON_WORD_LENGTH)
        {
            wordWithoutSize[k++] = words[1][++i];
        }

        while (k < COMMON_WORD_LENGTH)
            wordWithoutSize[k++] = NOTHING_CHAR;

        newNumberValue = extractValueFromIntegerString(wordWithoutSize);
        *numberOfVars = *numberOfVars + arraySize;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        newNumber.value = newNumberValue;

        for (i = 0; i < arraySize; i++)
        {
            memory[*numberOfVars - arraySize + i] = newNumber;
        }
        strcpy(memory[*numberOfVars - arraySize].name, newNumberName);
    }
    else
    {
        /* DECLARATION SECTION START */
        int newNumberValue = extractValueFromIntegerString(words[1]);
        /* DECLARATION SECTION END */

        *numberOfVars = *numberOfVars + 1;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        Number newNumber = {.value = newNumberValue};
        strcpy(newNumber.name, newNumberName);
        memory[*numberOfVars - 1] = newNumber;
    }
}

void DS_directive(char (*words)[MAX_WORD_LINE_LENGTH], int lineIndex, Label *labels, int labelLength, Number *memory, int *numberOfVars)
{
    /* DECLARATION SECTION START */
    char newNumberName[COMMON_WORD_LENGTH];
    /* DECLARATION SECTION END */

    strcpy(newNumberName, labels[findLabelIndexByLine(labels, lineIndex, labelLength)].name);
    if (isArrayInitialization(words[1]))
    {
        /* DECLARATION SECTION START */
        char arraySizeString[COMMON_WORD_LENGTH];
        char wordWithoutSize[COMMON_WORD_LENGTH];
        int newNumberValue;
        Number newNumber;
        int arraySize;
        int i = 0;
        int j = 0;
        int k = 0;
        /* DECLARATION SECTION END */

        while (words[1][i] != STAR_CHAR)
        {
            arraySizeString[j++] = words[1][i++];
        }

        while (j < COMMON_WORD_LENGTH)
        {
            arraySizeString[j++] = NOTHING_CHAR;
        }
        arraySize = parseToDecimal(arraySizeString);

        while (i < COMMON_WORD_LENGTH)
        {
            wordWithoutSize[k++] = words[1][++i];
        }

        while (k < COMMON_WORD_LENGTH)
            wordWithoutSize[k++] = NOTHING_CHAR;

        newNumberValue = extractValueFromIntegerString(wordWithoutSize);
        *numberOfVars = *numberOfVars + arraySize;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        newNumber.value = newNumberValue;

        for (i = 0; i < arraySize; i++)
        {
            memory[*numberOfVars - arraySize + i] = newNumber;
        }
        strcpy(memory[*numberOfVars - arraySize].name, newNumberName);
    }
    else
    {
        /* DECLARATION SECTION START */
        int newNumberValue = extractValueFromIntegerString(words[1]);
        /* DECLARATION SECTION END */

        *numberOfVars = *numberOfVars + 1;
        memory = (Number *)realloc(memory, *numberOfVars * sizeof(Number));
        Number newNumber = {.value = newNumberValue};
        strcpy(newNumber.name, newNumberName);
        memory[*numberOfVars - 1] = newNumber;
    }
}

#endif