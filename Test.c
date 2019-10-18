#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// FILE *infile;
#define NUMBER_OF_DIRS 20

char directives[NUMBER_OF_DIRS][2] = {
    "A ", "AR",
    "S ", "SR",
    "M ", "MR",
    "D ", "DR",
    "C ", "CR",
    "J ", "JZ", "JP", "JN",
    "L ", "LA", "LR", "ST",
    "DC", "DS"};

bool stringsToBeSame(char *firstWord, char *secondWord)
{
    if (strlen(firstWord) != strlen(secondWord))
        return false;
    for (int i = 0; i < strlen(firstWord); i++)
        if (firstWord[i] != secondWord[i])
            return false;
    return true;
}

bool isDirective(char *word)
{
    for (int i = 0; i < NUMBER_OF_DIRS; i++)
    {
        char directiveHandler[2];
        directiveHandler[0] = directives[i][0];
        if (directives[i][1] != ' ')
            directiveHandler[1] = directives[i][1];
        if (stringsToBeSame(directiveHandler, word))
            return true;
    }
    return false;
};

void splitLineIntoWords(char *codeLine, char (*words)[16])
{
    int j = 0;
    int k = 0;
    for (int i = 0; i < strlen(codeLine); ++i)
    {
        if (codeLine[i] != ' ' && codeLine[i] != ',')
            words[j][k++] = codeLine[i];
        else if (i && codeLine[i - 1] != ' ' && codeLine[i - 1] != ',')
        {
            j++;
            k = 0;
        }
    }
}

void extractLabel(char (*words)[16])
{
    int x = 5;
};
void saveLabel(){

};

void removeLabelFromWords(){

};

void executeLine(char *codeLine)
{
    printf("executing line...\n");
    char words[16][16];
    splitLineIntoWords(codeLine, words);
    // check is there a label
    if (!isDirective(words[0]))
    {
        saveLabel();
        removeLabelFromWords();
    }
    // continue executing
}

int main()
{
    FILE *file;
    char codeStrings[256][256];
    file = fopen("sample.txt", "r");
    if (file != NULL)
    {
        printf("File loaded\n");
    }
    else
    {
        printf("Cannot find parseable file\n");
    };
    int i = 0;
    while (!feof(file))
    {
        fgets(codeStrings[i], 64, file);
        i++;
    };
    executeLine(codeStrings[0]);
    fclose(file);

    return 0;
}