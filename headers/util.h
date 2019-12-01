#ifndef util

#define util

bool isArrayInitialization(char *word)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */

    for (i = 0; i < strlen(word); i++)
    {
        if (word[i] == STAR_CHAR)
            return true;
    }
    return false;
}

int parseToDecimal(char *word)
{
    /* DECLARATION SECTION START */
    int result = 0;
    int decPower = 1;
    int sign = 1;
    int i;
    /* DECLARATION SECTION END */

    for (i = strlen(word) - 1; i >= 0; i--)
    {
        if (word[i] == MINUS_CHAR)
        {
            sign *= -1;
            continue;
        }

        if ((int)word[i] == LINEFEED_ASCII)
            continue;

        if ((int)word[i] < LOWER_ASCII_BOUND || (int)word[i] > UPPER_ASCII_BOUND)
        {
            printImparseableValueError();
            return NULL;
        }
        result += ((int)word[i] - LOWER_ASCII_BOUND) * decPower;
        decPower *= 10;
    }
    return sign * result;
}

int *parseSecondWord(char *word, int *registers)
{
    /* DECLARATION SECTION START */
    char bytesToShift[COMMON_WORD_LENGTH];
    char registerNum[REG_CHAR_LENGTH];
    int address;
    int *result;
    int i = 0;
    int j = 0;
    /* DECLARATION SECTION END */

    while (word[i] != OPEN_BRACKET_CHAR)
    {
        bytesToShift[i] = word[i];
        i++;
    }
    i++;

    while (word[i + j] != CLOSE_BRACKET_CHAR)
    {
        registerNum[j] = word[i + j];
        j++;
    }
    while (i <= COMMON_WORD_LENGTH)
    {
        bytesToShift[i - 1] = NOTHING_CHAR;
        i++;
    }

    while (j < REG_CHAR_LENGTH)
        registerNum[j++] = NOTHING_CHAR;

    // multiplying because number data type is bigger than integer
    address = registers[parseToDecimal(registerNum)] + parseToDecimal(bytesToShift);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
    result = address;
#pragma GCC diagnostic pop
    return result;
}

int findLabelIndexByLine(Label *labels, int lineIndex, int labelLength)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */

    for (i = 0; i < labelLength; i++)
        if (labels[i].lineIndex == lineIndex)
            return i;

    printMissingLabel();
    return -1;
}

int findLabelIndexByName(Label *labels, char *name, int labelLength)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */

    for (i = 0; i < labelLength; i++)
    {
        if (stringsToBeSame(labels[i].name, name))
            return i;
    }

    printMissingLabel();
    return -1;
}

int findMemoryValue(int *memory, MemLabel *memoryLabels, int *numberOfVars, char *word, int *registers)
{
    int *secWordHandler;
    // removing last character if it is line feed
    if ((int)word[strlen(word) - 1] == LINEFEED_ASCII)
        word[strlen(word) - 1] = NOTHING_CHAR;

    if (word[strlen(word) - 1] == CLOSE_BRACKET_CHAR)
    {
        secWordHandler = parseSecondWord(word, registers);
        return *secWordHandler;
    }
    else
    {
        /* DECLARATION SECTION START */
        int i;
        /* DECLARATION SECTION END */

        for (i = 0; i < *numberOfVars; i++)
        {
            if (stringsToBeSame(memoryLabels[i].label, word))
                return memory[i];
        };
    }

    printUndWord(word);
    return 0;
}

int *findMemoryAddress(int *memory, MemLabel *memoryLabels, int *numberOfVars, char *name, int *registers)
{
    /* DECLARATION SECTION START */
    int *memoryAddress;
    int i;
    /* DECLARATION SECTION END */

    // removing last character if it is line feed
    if ((int)name[strlen(name) - 1] == LINEFEED_ASCII)
        name[strlen(name) - 1] = NOTHING_CHAR;
    if (name[strlen(name) - 1] == CLOSE_BRACKET_CHAR)
    {
        memoryAddress = parseSecondWord(name, registers);
        return memoryAddress;
    }

    for (i = 0; i < *numberOfVars; i++)
    {
        if (stringsToBeSame(memoryLabels[i].label, name))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
            memoryAddress = (intptr_t)&memory[i];
#pragma GCC diagnostic pop
        return memoryAddress;
    };

    printUndWord(name);
    return 0;
}

int findMemoryIndex(MemLabel *memoryLabels, int *numberOfVars, char *name)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */

    // removing last character if it is line feed
    if ((int)name[strlen(name) - 1] == LINEFEED_ASCII)
        name[strlen(name) - 1] = NOTHING_CHAR;

    for (i = 0; i < *numberOfVars; i++)
    {
        if (stringsToBeSame(memoryLabels[i].label, name))
            return i;
    };

    printUndWord(name);
    return -1;
}

int extractValueFromIntegerString(char *word)
{
    /* DECLARATION SECTION START */
    char extractedValue[COMMON_WORD_LENGTH];
    int j = 0;
    int i = 1;
    /* DECLARATION SECTION END */

    while (word[i - 1] != OPEN_BRACKET_CHAR)
        i++;

    while (word[i] != CLOSE_BRACKET_CHAR)
        extractedValue[j++] = word[i++];

    while (j < COMMON_WORD_LENGTH)
        extractedValue[j++] = NOTHING_CHAR;

    return parseToDecimal(extractedValue);
}

bool isDirective(char *word)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */

    for (i = 0; i < NUMBER_OF_DIRS; i++)
    {
        char directiveHandler[DIR_CHAR_LENGTH - 1];
        strcpy(directiveHandler, directives[i]);
        if (stringsToBeSame(directiveHandler, word))
            return true;
    }
    return false;
};

void splitLineIntoWords(char *codeLine, char (*words)[COMMON_WORD_LENGTH])
{
    /* DECLARATION SECTION START */
    int i;
    int j = 0;
    int k = 0;
    /* DECLARATION SECTION END */

    for (i = 0; i < strlen(codeLine); i++)
    {
        if (codeLine[i] != SPACE_CHAR && codeLine[i] != COMMA_CHAR)
            words[j][k++] = codeLine[i];
        else if (i && codeLine[i - 1] != SPACE_CHAR && codeLine[i - 1] != COMMA_CHAR)
        {
            while (k < COMMON_WORD_LENGTH)
                // filling missing letters in words
                words[j][k++] = NOTHING_CHAR;

            j++;
            k = 0;
        }
        else
        {
            k = 0;
        }
    }

    while (k < COMMON_WORD_LENGTH)
    {
        words[j][k++] = '\0';
    }
    j++;

    // filling missing words
    while (j < MAX_WORD_LINE_LENGTH)
    {
        /* DECLARATION SECTION START */
        int i;
        /* DECLARATION SECTION END */

        for (i = 0; i < COMMON_WORD_LENGTH; i++)
            words[j][i] = NOTHING_CHAR;
        j++;
    };
}

void saveLabel(int lineNumber, char *labelName, Label *labels, int **labelLength)
{
    labels[**labelLength].lineIndex = lineNumber + 1;
    strcpy(labels[**labelLength].name, labelName);
    **labelLength = **labelLength + 1;
};

void removeLabelFromWords(char (*words)[16])
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */

    for (i = 1; i < MAX_WORD_LINE_LENGTH; i++)
        strcpy(words[i - 1], words[i]);

    for (i = 0; i < COMMON_WORD_LENGTH; i++)
        words[MAX_WORD_LINE_LENGTH - 1][i] = NOTHING_CHAR;
};

void switchRegisterStatus(char *programStatusRegister, int valueReturned)
{
    if (valueReturned == 0)
        strcpy(programStatusRegister, ZERO_STATUS);
    else if (valueReturned > 0)
        strcpy(programStatusRegister, POSITIVE_STATUS);
    else if (valueReturned < 0)
        strcpy(programStatusRegister, NEGATIVE_STATUS);
    else
        strcpy(programStatusRegister, ERROR_STATUS);
}

#endif