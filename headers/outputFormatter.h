#ifndef outputFormatter

#define outputFormatter

/* COLORS START */
#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define RESET "\x1B[0m"
/* COLORS END */

/* COMMANDS START */
#define TRACK_STATUS_CMD "track status"
#define TRACK_REGISTERS_CMD "track registers"
#define TRACK_MEMORY_CMD "track memory"

#define UNTRACK_STATUS_CMD "untrack status"
#define UNTRACK_REGISTERS_CMD "untrack registers"
#define UNTRACK_MEMORY_CMD "untrack memory"

#define SHOW_STATUS_CMD "show status"
#define SHOW_REGISTERS_CMD "show registers"
#define SHOW_MEMORY_CMD "show memory"
#define SHOW_LABELS_CMD "show labels"

#define NEXT_CMD "next"
#define EXIT_DEBUG_CMD "skip"
#define EXIT_PROGRAM_CMD "exit"
/* COMMANDS END */

/* OTHER START */
#define DEFAULT_MODE "default"
#define DEBUG_MODE "debug"
#define DEFAULT_SOURCE_FILENAME "srednia.txt"
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

void showLabels(Label *labels, int labelLength)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */
    printf(BLU "Labels\n" RESET);
    for (i = 0; i < labelLength; i++)
        printf(YEL "Name: %8s, line: %2d\n" RESET, labels[i].name, labels[i].lineIndex);
}

void showStatus(char *status)
{
    printf(YEL "State register status is " RESET "%s\n\n", status);
}

void showRegisters(int *registers)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */
    printf(BLU "Registers\n" RESET);
    for (i = 0; i < NUMBER_OF_REGS; i++)
        printf(YEL "Register #%02d:  " RESET "%08x\n", i, registers[i]);
    printf("\n");
}

void showMemory(Number *memory, int *numberOfVars)
{
    /* DECLARATION SECTION START */
    int i;
    /* DECLARATION SECTION END */
    printf(BLU "Memory variables\n" RESET);
    for (i = 0; i < *numberOfVars; i++)
        printf(YEL "%13s  " RESET "%08x\n", memory[i].name, memory[i].value);
    printf("\n");
}

void printLineExecution(int line, char *directive)
{
    printf(YEL "Executing line %3d with directive  " RESET BLU "%2s\n" RESET, line, directive);
}

void printFileChoose()
{
    printf(BLU "Choose source file:\n" RESET);
}

void printDefaultFileChoose()
{
    printf(YEL "Default file chosen\n" RESET);
}

void printFileLoadSuccess()
{
    printf(YEL "\nFile loaded\n" RESET);
}

void printFileLoadError()
{
    printf(RED "\nCannot find parseable file\n" RESET);
}

void printEmptyLineWarning()
{
    printf(RED "\nWARNING: There is empty line in given file. It will cause line numeration change\n" RESET);
}

void printInitializationInfo()
{
    printf(YEL "Initializing...\n" RESET);
}

void printInitializationSuccess()
{
    printf(YEL "Program initialized succesfully\n" RESET);
}

void printExecutionChoose()
{
    printf(BLU "\nChoose execution mode:\n" RESET);
}

void printInvalidArgument()
{
    printf(RED "Invalid argument\n" RESET);
}

void printDebugModeOn()
{
    printf(YEL "Debug mode is on\n\n" RESET);
}

void printDebugModeOff()
{
    printf(YEL "Default mode is on\n\n" RESET);
}

void printDividingZeroError()
{
    printf(RED "ERROR: Dividing by zero\n" RESET);
}

void printEndingWords()
{
    printf(BLU "%s\n\n" RESET, ENDING_WORDS);
}

void printImparseableValueError()
{
    printf(RED "ERROR: Tried parsing inparseable value\n\n" RESET);
}

void printMissingLabel()
{
    printf(RED "Can't find given label\n" RESET);
}

void printUndWord(char *word)
{
    printf(RED "%s is not defined\n" RESET, word);
}

void printUnDirective()
{
    printf(RED "Unknown directive" RESET);
}

void printTitle()
{
    printf("\n------------------------------\n");
    printf(BLU "Pseudoassembly Interpreter " RESET YEL "1.0\n" RESET);
    printf(BLU "Author: " RESET YEL "Szymon Sieradzki\n" RESET);
    printf("------------------------------\n\n");
}

void printTracked(bool trackRegisters, bool trackStatus, bool trackMemory, char *stateRegister, Number *memory, int *numberOfVars, Label *labels, int labelLength, int *registers)
{
    if (trackStatus)
        showStatus(stateRegister);
    if (trackRegisters)
        showRegisters(registers);
    if (trackMemory)
        showMemory(memory, numberOfVars);
}

void commandController(bool *trackRegisters, bool *trackStatus, bool *trackMemory, char *stateRegister, Number *memory, int *numberOfVars, Label *labels, int labelLength, int *registers, char *executionMode, bool *isFinished)
{
    /* DECLARATION SECTION START */
    char commandHandler[LONG_WORD_LENGTH];
    /* DECLARATION SECTION END */
    fgets(commandHandler, LONG_WORD_LENGTH, stdin);
    commandHandler[strlen(commandHandler) - 1] = NOTHING_CHAR;
    if (!strlen(commandHandler) || stringsToBeSame(commandHandler, NEXT_CMD))
        return;
    else if (stringsToBeSame(commandHandler, TRACK_STATUS_CMD))
    {
        *trackStatus = true;
        printf(YEL "Tracking status is on\n" RESET);
    }
    else if (stringsToBeSame(commandHandler, TRACK_REGISTERS_CMD))
    {
        *trackRegisters = true;
        printf(YEL "Tracking registers is on\n" RESET);
    }
    else if (stringsToBeSame(commandHandler, TRACK_MEMORY_CMD))
    {
        *trackMemory = true;
        printf(YEL "Tracking memory is on\n" RESET);
    }
    else if (stringsToBeSame(commandHandler, UNTRACK_STATUS_CMD))
    {
        *trackStatus = false;
        printf(YEL "Tracking status is off\n" RESET);
    }
    else if (stringsToBeSame(commandHandler, UNTRACK_REGISTERS_CMD))
    {
        *trackRegisters = false;
        printf(YEL "Tracking registers is off\n" RESET);
    }
    else if (stringsToBeSame(commandHandler, UNTRACK_MEMORY_CMD))
    {
        *trackMemory = false;
        printf(YEL "Tracking memory is off\n" RESET);
    }
    else if (stringsToBeSame(commandHandler, SHOW_STATUS_CMD))
    {
        showStatus(stateRegister);
    }
    else if (stringsToBeSame(commandHandler, SHOW_REGISTERS_CMD))
    {
        showRegisters(registers);
    }
    else if (stringsToBeSame(commandHandler, SHOW_MEMORY_CMD))
    {
        showMemory(memory, numberOfVars);
    }
    else if (stringsToBeSame(commandHandler, SHOW_LABELS_CMD))
    {
        showLabels(labels, labelLength);
    }
    else if (stringsToBeSame(commandHandler, SHOW_LABELS_CMD))
    {
        showLabels(labels, labelLength);
    }
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
        printf(RED "Unknown command\n" RESET);
    }
    commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
}

#endif
