#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef settings
#define settings

#define NUMBER_OF_DIRS 20
#define MAX_CODELINE_LENGTH 256
#define MAX_CODE_LENGTH 256

typedef struct Label Label;
typedef struct Number Number;

char STATUS[4][2] = { "00", "01", "10", "11" };
// 00 - zero
// 01 - positive
// 10 - negative
// 11 - error

char directives[NUMBER_OF_DIRS][3] = {
    "A\0", "AR",
    "S\0", "SR",
    "M\0", "MR",
    "D\0", "DR",
    "C\0", "CR",
    "J\0", "JZ", "JP", "JN",
    "L\0", "LA", "LR", "ST",
    "DC", "DS"
    };

struct Label
{
    int lineIndex;
    char name[16];
};

struct Number
{
    int value;
    char name[16];
};
#endif