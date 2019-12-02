#ifndef outputFormatter

#define outputFormatter

#define NEXT_CMD "next"
#define EXIT_DEBUG_CMD "skip"
#define EXIT_PROGRAM_CMD "exit"
/* COMMANDS END */

/* OTHER START */
#define DEFAULT_MODE "default"
#define DEBUG_MODE "debug"
#define DEFAULT_SOURCE_FILENAME "sample.txt"
/* OTHER END */

bool stringsToBeSame(char *firstWord, char *secondWord)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */

    // fixing possible line feed
    if ((int)firstWord[strlen(firstWord) - 1] == LINEFEED_ASCII)
        firstWord[strlen(firstWord) - 1] = NOTHING_CHAR;
    if ((int)secondWord[strlen(secondWord) - 1] == LINEFEED_ASCII)
        secondWord[strlen(secondWord) - 1] = NOTHING_CHAR;

    if (strlen(firstWord) != strlen(secondWord))
        return false;

    for (i = 0; i < strlen(firstWord); i++)
        if (firstWord[i] != secondWord[i])
            return false;
    return true;
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

void printFileChoose()
{
    printf("Choose source file:\n");
}

void printDefaultFileChoose()
{
    printf("Default file chosen\n");
}

void printFileLoadSuccess()
{
    printf("\nFile loaded\n");
}

void printFileLoadError()
{
    printf("\nCannot find parseable file\n");
}

void printEmptyLineWarning()
{
    printf("\nWARNING: There is empty line in given file. It will cause line numeration change\n");
}

void printInitializationInfo()
{
    printf("Initializing...\n");
}

void printInitializationSuccess()
{
    printf("Program initialized succesfully\n");
}

void printExecutionChoose()
{
    printf("\nChoose execution mode:\n");
}

void printInvalidArgument()
{
    printf("Invalid argument\n");
}

void printDebugModeOn()
{
    printf("Debug mode is on\n\n");
}

void printDebugModeOff()
{
    printf("Default mode is on\n\n");
}

void printDividingZeroError()
{
    printf("ERROR: Dividing by zero\n");
}

void printEndingWords()
{
    printf("%s\n\n", ENDING_WORDS);
}

void printImparseableValueError()
{
    printf("ERROR: Tried parsing inparseable value\n\n");
}

void printMissingLabel()
{
    printf("Can't find given label\n");
}

void printUndWord(char *word)
{
    printf("%s is not defined\n", word);
}

void printUnDirective()
{
    printf("Unknown directive\n");
}

void printLine(int lineLength) {
    for (int i = 0; i < lineLength; i++)
        printf("-");
    printf("\n");
}

void printMiddle(char *word) {
    
    for (int i = 0; i < (TERMINAL_CHAR_SIZE - strlen(word)) / 2; i++)
        printf(" ");
    printf("%s", word);
    printf("\n");
}

void printColumn(char *word) {
    for (int i = 0; i < ceil((((double)TERMINAL_CHAR_SIZE - 4 )/ 3 - strlen(word))) / 2; i++)
        printf(" ");
    printf("%s", word);
    for (int i = 0; i < ((TERMINAL_CHAR_SIZE - 4 )/ 3 - strlen(word)) / 2; i++)
        printf(" ");
    printf("|");
}

void printRow(char *word1, char *word2, char *word3) {
    printf("|");
    printColumn(word1);
    printColumn(word2);
    printColumn(word3);
    printf("\n");
}

bool hasLabel(int lineIndex, MemLabel *memoryLabels, int *numberOfVars) {
    int i;
    for (i = 0; i < *numberOfVars; i++)
        if (memoryLabels[i].memIndex == lineIndex) return true;
    return false;
}

void printEverything(
    int *registers, 
    char (*words)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH], 
    char codeLines[MAX_CODE_LENGTH][MAX_CODELINE_LENGTH], 
    int codeLength, 
    int nextLineToExec, 
    int *memory, 
    MemLabel *memoryLabels, 
    int *numberOfVars,
    int arrowMemory)
{
    int i, j;
    char middColScheme[TERMINAL_LENGTH][TERMINAL_CHAR_SIZE / 3];
    char leftColScheme[TERMINAL_LENGTH][TERMINAL_CHAR_SIZE / 3];
    char rightColScheme[TERMINAL_LENGTH][TERMINAL_CHAR_SIZE / 3];
    char arrowHandler[2];
    int printCodeStart = 0;
    int printMemStart = 0;

    sprintf(middColScheme[0], "------------------------------");
    for (i = 1; i < 2* NUMBER_OF_REGS; i+=2) {
        sprintf(middColScheme[i], "%02d         |          %08d", i / 2, registers[i / 2]); 
        sprintf(middColScheme[i + 1], "------------------------------");      
    }
    while (i < TERMINAL_LENGTH) {sprintf(middColScheme[i], " "); i++;};

    sprintf(leftColScheme[0], "");
    if (nextLineToExec - 1 > TERMINAL_LENGTH / 4 + 2 * printCodeStart) 
        printCodeStart += nextLineToExec -1 - TERMINAL_LENGTH / 4;
        else if (nextLineToExec - 1 < printCodeStart) printCodeStart = nextLineToExec - 1 - TERMINAL_LENGTH / 4 > 0 ? nextLineToExec - 1 - TERMINAL_LENGTH / 4 : 0;
    for (i = 2 * printCodeStart; i < TERMINAL_LENGTH + 2 * printCodeStart; i+=2) {
        strcpy(arrowHandler, "");
        if (i / 2 == nextLineToExec - 1) strcpy(arrowHandler, "->");
        for (j = 0; j < MAX_WORD_LINE_LENGTH; j++)
            if ((int)(words[i / 2][j][strlen(words[i / 2][j]) - 1]) == LINEFEED_ASCII) 
                words[i / 2][j][strlen(words[i / 2][j]) - 1] = '\0';
        j = 0;
        char wordHandler[COMMON_WORD_LENGTH] = "";
        if (!isDirective(words[i / 2][j])) {strcpy(wordHandler, words[i / 2][j]); j++;}
        sprintf(leftColScheme[i + 1 - 2 * printCodeStart], 
        "%3d %2s %12s %8s %15s %12s",
        i / 2 +1,
        arrowHandler, 
        wordHandler, 
        words[i / 2][j], 
        words[i / 2][j + 1], 
        words[i / 2][j + 2]);
        sprintf(leftColScheme[i + 2 - 2* printCodeStart], " ");
    }
    while (i < TERMINAL_LENGTH) {sprintf(leftColScheme[i], " "); i++;}

    sprintf(rightColScheme[0], "");
    j = 0;
    // if (arrowMemory > TERMINAL_LENGTH / 4 + 2 * printMemStart)
    //     printMemStart = arrowMemory -  TERMINAL_LENGTH / 4;
    for (i = 0; i < 2*(*numberOfVars); i+= 2) {
        strcpy(arrowHandler, "");
        if (arrowMemory == i / 2) strcpy(arrowHandler, "->");
        sprintf(rightColScheme[i + 1], 
        "%2s %10d %15s %10d",
        arrowHandler,
        &(memory[i / 2]),
        hasLabel(i / 2, memoryLabels, numberOfVars) ? memoryLabels[j++].label : " ", 
        memory[i / 2]);
        sprintf(rightColScheme[i + 2], "");
    }
    system("clear");
    printLine(TERMINAL_CHAR_SIZE);
    printMiddle("Pseudoassembly Interpreter 1.0");
    printf("\n\n");
    printLine(TERMINAL_CHAR_SIZE);
    printRow("CODE", "REGISTERS", "MEMORY");
    printLine(TERMINAL_CHAR_SIZE);
    for (int i = 0; i < TERMINAL_LENGTH; i++)
    printRow(leftColScheme[i], middColScheme[i], rightColScheme[i]);

}

void commandController(char *executionMode, bool *isFinished)
{
    /* DECLARATION SECTION START */
    char commandHandler[LONG_WORD_LENGTH];
    /* DECLARATION SECTION END */
    fgets(commandHandler, LONG_WORD_LENGTH, stdin);
    commandHandler[strlen(commandHandler) - 1] = NOTHING_CHAR;
    if (!strlen(commandHandler) || stringsToBeSame(commandHandler, NEXT_CMD))
        return;
    else if (stringsToBeSame(commandHandler, EXIT_DEBUG_CMD))
    {
        strcpy(executionMode, DEFAULT_MODE);
        return;
    }
    else if (stringsToBeSame(commandHandler, EXIT_PROGRAM_CMD))
    {
        *isFinished = true;
        return;
    }
    else
    {
        printf("Unknown command\n");
    }
    commandController(executionMode, isFinished);
}

#endif
