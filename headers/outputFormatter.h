#ifndef outputFormatter

#define outputFormatter

bool stringsToBeSame(char *firstWord, char *secondWord)
{
    int i;
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
    int i;
    for (i = 0; i < NUMBER_OF_DIRS; i++)
    {
        char directiveHandler[DIR_CHAR_LENGTH - 1];
        strcpy(directiveHandler, directives[i]);
        if (stringsToBeSame(directiveHandler, word)) return true;
    }
    return false;
};

void printFileChoose() {printf("Choose source file:\n");}

void printDefaultFileChoose() {printf("Default file chosen\n");}

void printFileLoadSuccess() {printf("\nFile loaded\n");}

void printFileLoadError() {printf("\nCannot find parseable file\n");}

void printEmptyLineWarning() {printf("\nWARNING: There is empty line in given file. It will cause line numeration change\n");}

void printInitializationInfo() {printf("Initializing...\n");}

void printInitializationSuccess() {printf("Program initialized succesfully\n");}

void printExecutionChoose() {printf("\nChoose execution mode[default\\debug]:\n");}

void printInvalidArgument() {printf("Invalid argument\n");}

void printDebugModeOn() {printf("Debug mode is on\n\n");}

void printDebugModeOff() {printf("Default mode is on\n\n");}

void printDividingZeroError() {printf("ERROR: Dividing by zero\n");}

void printEndingWords() {printf("%s\n\n", ENDING_WORDS);}

void printImparseableValueError() {printf("ERROR: Tried parsing inparseable value\n\n");}

void printMissingLabel() {printf("Can't find given label\n");}

void printUndWord(char *word) {printf("%s is not defined\n", word);}

void printUnDirective() {printf("Unknown directive\n");}

void printLine(int lineLength) {
    int i;
    for (i = 0; i < lineLength; i++) printf("-");
    printf("\n");
}

void printMiddle(char *word) {
    int i;
    for (i = 0; i < (TERMINAL_SIZE - strlen(word)) / 2; i++) printf(" ");
    printf("%s", word);
    printf("\n");
}

void printColumn(char *word) {
    int i;
    for (i = 0; i < ceil((((double)TERMINAL_SIZE - 4 )/ 3 - strlen(word))) / 2; i++) printf(" ");
    printf("%s", word);
    for (i = 0; i < ((TERMINAL_SIZE - 4 )/ 3 - strlen(word)) / 2; i++) printf(" ");
    printf("|");
}

void printRow(char *word1, char *word2, char *word3) {
    printf("|");
    printColumn(word1);
    printColumn(word2);
    printColumn(word3);
    printf("\n");
}

bool hasLabel(int lineIndex, MemLabel *memoryLabels, int length) {
    int i;
    for (i = 0; i < length; i++)
        if (memoryLabels[i].memIndex == lineIndex) return true;
    return false;
}
int findMemLabelIndexByLine(int lineIndex, MemLabel *memoryLabels, int length) {
    int i;
    for (i = 0; i < length; i++) {
        if(memoryLabels[i].memIndex == lineIndex) return i;
    }
}
void fillLeftCol(
    char leftColScheme[TERMINAL_LENGTH][TERMINAL_SIZE / 3], 
    char (*words)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH], 
    int nextLineToExec){
    char arrowHandler[DBL_CHAR_LENGTH];
    int printCodeStart = 0;
    int i, j;
    sprintf(leftColScheme[0], "");
    if (nextLineToExec - 1 > TERMINAL_LENGTH / 4 + 2 * printCodeStart) 
        printCodeStart = nextLineToExec -1 - TERMINAL_LENGTH / 4;
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
}

void fillRightCol(
    char rightColScheme[TERMINAL_LENGTH][TERMINAL_SIZE / 3], 
    int *memory, MemLabel *memoryLabels,
    int arrowMemory, int *numberOfVars)
    {
    char arrowHandler[DBL_CHAR_LENGTH];
    int printMemStart = 0;
    int i,j;
    sprintf(rightColScheme[0], "");
    j = 0;
    if (arrowMemory > TERMINAL_LENGTH / 4 + 2 * printMemStart)
        printMemStart += arrowMemory -  TERMINAL_LENGTH / 4;
        else if (arrowMemory < printMemStart) printMemStart = printMemStart - TERMINAL_LENGTH / 4 > 0 ? arrowMemory - TERMINAL_LENGTH / 4 : 0;
    for (i = 2 * printMemStart; i < TERMINAL_LENGTH + 2 * printMemStart; i+= 2) {
        if (i / 2 >= *numberOfVars) 
        {
            sprintf(rightColScheme[i + 1 - 2 * printMemStart], "");
            sprintf(rightColScheme[i + 2 - 2 * printMemStart], "");
        } 
        else 
        {
        strcpy(arrowHandler, "");
        if (arrowMemory == i / 2) strcpy(arrowHandler, "->");
        sprintf(rightColScheme[i + 1 - 2 * printMemStart], 
        "%2s %10d %15s %10x",
        arrowHandler,
        &(memory[i / 2]),
        hasLabel(i / 2, memoryLabels, MAX_CODE_LENGTH) ? memoryLabels[findMemLabelIndexByLine(i / 2, memoryLabels, MAX_CODE_LENGTH)].label : " ", 
        memory[i / 2]);
        sprintf(rightColScheme[i + 2 - 2 * printMemStart], "");
        }
    }
}
void fillMidCol(
    char middColScheme[TERMINAL_LENGTH][TERMINAL_SIZE / 3], 
    int *registers, char *stateRegister)
    {
        int i;
    for (i = 0; i < REG_TERM_DIST; i++) sprintf(middColScheme[i], "");
    sprintf(middColScheme[i], "------------------------------");
        for (i = 1; i < 2* NUMBER_OF_REGS; i+=2) {
        sprintf(middColScheme[i + REG_TERM_DIST], "%02d         |          %08x", i / 2, registers[i / 2]); 
        sprintf(middColScheme[i + 1 + REG_TERM_DIST], "------------------------------");      
    }
    i += REG_TERM_DIST;
    sprintf(middColScheme[i++], "|%11sSTATUS%11s|", "", "");
    sprintf(middColScheme[i++], "------------------------------");
    sprintf(middColScheme[i++], "|%13s%s%13s|", "", stateRegister,"");
    sprintf(middColScheme[i++], "------------------------------");
    while (i < TERMINAL_LENGTH) {sprintf(middColScheme[i], " "); i++;};
}
void printPanel(
    int *registers, char *stateRegister, 
    char (*words)[MAX_WORD_LINE_LENGTH][COMMON_WORD_LENGTH], 
    char codeLines[MAX_CODE_LENGTH][MAX_CODELINE_LENGTH], 
    int codeLength, int nextLineToExec, 
    int *memory, MemLabel *memoryLabels, 
    int *numberOfVars, int arrowMemory)
{
    int i;
    char middColScheme[TERMINAL_LENGTH][TERMINAL_SIZE / 3];
    char leftColScheme[TERMINAL_LENGTH][TERMINAL_SIZE / 3];
    char rightColScheme[TERMINAL_LENGTH][TERMINAL_SIZE / 3];
    char arrowHandler[DBL_CHAR_LENGTH];
    fillLeftCol(leftColScheme, words, nextLineToExec);
    fillRightCol(rightColScheme, memory, memoryLabels, arrowMemory, numberOfVars);
    fillMidCol(middColScheme, registers, stateRegister);
    system(CLEAR_CMD);
    printLine(TERMINAL_SIZE);
    printMiddle("Pseudoassembly Interpreter 1.0");
    printMiddle("Author: Szymon Sieradzki");
    printLine(TERMINAL_SIZE);
    printRow("CODE", "REGISTERS", "MEMORY");
    printLine(TERMINAL_SIZE);
    for (i = 0; i < TERMINAL_LENGTH; i++)
    printRow(leftColScheme[i], middColScheme[i], rightColScheme[i]);
    printLine(TERMINAL_SIZE);
}

void commandController(char *executionMode, bool *isFinished)
{
    char commandHandler[LONG_WORD_LENGTH];
    fgets(commandHandler, LONG_WORD_LENGTH, stdin);
    commandHandler[strlen(commandHandler) - 1] = NOTHING_CHAR;
    if (!strlen(commandHandler) || stringsToBeSame(commandHandler, NEXT_CMD)) return;
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
    else printf("Unknown command\n");
    commandController(executionMode, isFinished);
}

#endif
