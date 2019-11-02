#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef settings
#define settings

#define NUMBER_OF_DIRS 20
#define DIR_CHAR_LENGTH 3
#define REG_CHAR_LENGTH 3
#define LINEFEED_ASCII 10
#define MAX_CODELINE_LENGTH 256
#define STAR_CHAR '*'
#define MINUS_CHAR '-'
#define LOWER_ASCII_BOUND 48
#define UPPER_ASCII_BOUND 57
#define MAX_CODE_LENGTH 256
#define START_LINE_INDEX 1
#define ENDING_WORDS "KONIEC"
#define MAX_BYTES_TO_SHIFT_LENGTH 16
#define SOURCE_DIRECTORY_PATH "src/"
#define COMMON_WORD_LENGTH 16
#define ZERO_STATUS "00"
#define POSITIVE_STATUS "01"
#define NEGATIVE_STATUS "10"
#define ERROR_STATUS "11"
#define OPEN_BRACKET_CHAR '('
#define CLOSE_BRACKET_CHAR ')'
#define NOTHING_CHAR '\0'
#define INTEGER_SIZE 4
#define NUMBER_DATA_SIZE 20
#define SPACE_CHAR ' '
#define COMMA_CHAR ','
#define MAX_WORD_LINE_LENGTH 16
#define LONG_WORD_LENGTH 32
#define NUMBER_OF_REGS 16

typedef struct Label Label;
typedef struct Number Number;

char directives[NUMBER_OF_DIRS][DIR_CHAR_LENGTH] = {
    "A\0", "AR",
    "S\0", "SR",
    "M\0", "MR",
    "D\0", "DR",
    "C\0", "CR",
    "J\0", "JZ", "JP", "JN",
    "L\0", "LA", "LR", "ST",
    "DC", "DS"};

struct Label
{
    int lineIndex;
    char name[COMMON_WORD_LENGTH];
};

struct Number
{
    int value;
    char name[COMMON_WORD_LENGTH];
};
#endif