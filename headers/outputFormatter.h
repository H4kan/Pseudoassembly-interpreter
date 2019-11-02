#include <stdio.h>
#ifndef outputFormatter
#define outputFormatter

// colors for console terminal
#define RED "\x1B[31m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define RESET "\x1B[0m"

#define DEFAULT_MODE "default"
#define DEBUG_MODE "debug"
#define DEFAULT_SOURCE_FILENAME "sample.txt"

// console commands
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

void showLabels(Label *labels, int labelLength)
{
    printf(BLU "Labels\n" RESET);
    for (int i = 0; i < labelLength; i++)
        printf(YEL "Name: %8s, line: %2d\n" RESET, labels[i].name, labels[i].lineIndex);
}

void showStatus(char *status)
{
    printf(YEL "State register status is " RESET "%s\n\n", status);
}

void showRegisters(int *registers)
{
    printf(BLU "Registers\n" RESET);
    for (int i = 0; i < 16; i++)
        printf(YEL "Register #%02d:  " RESET "%08x\n", i, registers[i]);
    printf("\n");
}

void showMemory(Number *memory, int *numberOfVars)
{
    printf(BLU "Memory variables\n" RESET);
    for (int i = 0; i < *numberOfVars; i++)
        printf(YEL "%13s  " RESET "%08x\n", memory[i].name, memory[i].value);
    printf("\n");
}

void printLineExecution(int line, char *directive)
{
    printf(YEL "Executing line %d with directive  " RESET BLU "%2s\n" RESET, line, directive);
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
    char commandHandler[32];
    fgets(commandHandler, 32, stdin);
    commandHandler[strlen(commandHandler) - 1] = '\0';
    if (!strlen(commandHandler) || stringsToBeSame(commandHandler, NEXT_CMD))
        return;
    else if (stringsToBeSame(commandHandler, TRACK_STATUS_CMD))
    {
        *trackStatus = true;
        printf(YEL "Tracking status is on\n" RESET);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, TRACK_REGISTERS_CMD))
    {
        *trackRegisters = true;
        printf(YEL "Tracking registers is on\n" RESET);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, TRACK_MEMORY_CMD))
    {
        *trackMemory = true;
        printf(YEL "Tracking memory is on\n" RESET);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, UNTRACK_STATUS_CMD))
    {
        *trackStatus = false;
        printf(YEL "Tracking status is off\n" RESET);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, UNTRACK_REGISTERS_CMD))
    {
        *trackRegisters = false;
        printf(YEL "Tracking registers is off\n" RESET);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, UNTRACK_MEMORY_CMD))
    {
        *trackMemory = false;
        printf(YEL "Tracking memory is off\n" RESET);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, SHOW_STATUS_CMD))
    {
        showStatus(stateRegister);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, SHOW_REGISTERS_CMD))
    {
        showRegisters(registers);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, SHOW_MEMORY_CMD))
    {
        showMemory(memory, numberOfVars);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, SHOW_LABELS_CMD))
    {
        showLabels(labels, labelLength);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, SHOW_LABELS_CMD))
    {
        showLabels(labels, labelLength);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
    else if (stringsToBeSame(commandHandler, EXIT_DEBUG_CMD))
    {
        strcpy(executionMode, DEFAULT_MODE);
    }
    else if (stringsToBeSame(commandHandler, EXIT_PROGRAM_CMD))
    {
        *isFinished = true;
    }
    else
    {
        printf(RED "Unknown command\n" RESET);
        commandController(trackRegisters, trackStatus, trackMemory, stateRegister, memory, numberOfVars, labels, labelLength, registers, executionMode, isFinished);
    }
}

#endif
