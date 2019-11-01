#include <stdio.h>
#ifndef outputFormatter
#define outputFormatter

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void printFileChoose()
{
    printf(BLU "Choose source file:\n" RESET);
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
    printf(BLU "Choose execution mode:\n" RESET);
}
#endif
