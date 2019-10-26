#include<stdio.h>
#include<string.h>
#ifndef util
#define util
#include "settings.h"
bool stringsToBeSame(char *firstWord, char *secondWord)
{
    if (strlen(firstWord) != strlen(secondWord))
        return false;
    for (int i = 0; i < strlen(firstWord); i++)
        if (firstWord[i] != secondWord[i])
            return false;
    return true;
}

bool isArrayInitialization(char *word) {
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == '*') return true;
    }
    return false;
}
int parseToDecimal(char *word)
{
    int result = 0;
    int decPower = 1;
    int sign = 1;
    for (int i = strlen(word) - 1; i >= 0; i--)
    {
        if (word[i] == '-')
        {
            sign *= -1;
            continue;
        }
        if ((int)word[i] == 10)
            continue;
        if ((int)word[i] < 48 || (int)word[i] > 57)
        {
            printf("ERROR: Tried parsing inparseable value\n");
            return NULL;
        }
        result += ((int)word[i] - 48) * decPower;
        decPower *= 10;
    }
    return sign * result;
}

int findLabelIndex(Label *labels, int lineIndex, int labelLength)
{
    for (int i = 0; i < labelLength; i++)
        if (labels[i].lineIndex == lineIndex)
            return i;
    printf("Can't find given label");
    return -1;
}

int findMemoryValue(Number *memory, int *numberOfVars, char *name) {
    // removing last character if it is line feed
    if ((int)name[strlen(name) - 1] == 10) name[strlen(name) - 1] = '\0';
    for (int i = 0; i < *numberOfVars; i++) {
        if (stringsToBeSame(memory[i].name, name)) return memory[i].value;
    };
    printf("%s is not defined\n", name);
    return 0;
}


int extractValueFromIntegerString(char *word) {
    char extractedValue[16];
    int j = 0;
    int i = 1;
    while(word[i-1] != '(') i++;
    while(word[i] != ')') extractedValue[j++] = word[i++];
    while(j<16) extractedValue[j++] = '\0'; 
    return parseToDecimal(extractedValue);
}

bool isDirective(char *word)
{
    for (int i = 0; i < NUMBER_OF_DIRS; i++)
    {
        char directiveHandler[2];
        strcpy(directiveHandler, directives[i]);
        if (stringsToBeSame(directiveHandler, word))
            return true;
    }
    return false;
};

void splitLineIntoWords(char *codeLine, char (*words)[16])
{
    int j = 0;
    int k = 0;
    for (int i = 0; i < strlen(codeLine); i++)
    {
        if (codeLine[i] != ' ' && codeLine[i] != ',')
            words[j][k++] = codeLine[i];
        else if (i && codeLine[i - 1] != ' ' && codeLine[i - 1] != ',')
        {
            while (k < 16)
                // filling missing letters in words
                words[j][k++] = '\0';
            j++;
            k = 0;
        }
        else
        {
            k = 0;
        }
    }
    while (k < 16)
    {
        words[j][k++] = '\0';
    }
    j++;
    // filling missing words
    while (j < 16)
    {
        for (int i = 0; i < 16; i++)
            words[j][i] = '\0';
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
    for (int i = 1; i < 16; i++)
        strcpy(words[i - 1], words[i]);
    for (int i = 0; i < 16; i++)
        words[15][i] = '\0';
};

void switchRegisterStatus(char *programStatusRegister, int valueReturned)
{
    if (valueReturned == 0) strcpy(programStatusRegister, STATUS[0]);
    else if (valueReturned > 0) strcpy(programStatusRegister, STATUS[1]);
    else if (valueReturned < 0) strcpy(programStatusRegister, STATUS[2]);
    else strcpy(programStatusRegister, STATUS[3]);
    
    
}

#endif