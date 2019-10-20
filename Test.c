#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// FILE *infile;
#define NUMBER_OF_DIRS 20

char directives[NUMBER_OF_DIRS][2] = {
    "A\0", "AR",
    "S\0", "SR",
    "M\0", "MR",
    "D\0", "DR",
    "C\0", "CR",
    "J\0", "JZ", "JP", "JN",
    "L\0", "LA", "LR", "ST",
    "DC", "DS"};
typedef struct Label Label;

struct Label
{
    int lineIndex;
    char name[16];
};

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
        directiveHandler[1] = directives[i][1];
        directiveHandler[2] = '\0';
        if (stringsToBeSame(directiveHandler, word))
            return true;
    }
    return false;
};

void splitLineIntoWords(char *codeLine, char (*words)[16])
{
    int j = 0;
    int k = 0;
    // printf("%s\n", codeLine);
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

void showLabels(Label *labels, int *labelLength)
{
    printf("Labels:\n");
    for (int i = 0; i < *labelLength; i++)
        printf("Name: %s, line: %d\n", labels[i].name, labels[i].lineIndex);
}

void initializeLine(int lineNumber, char *codeLine, char (*words)[16], Label *labels, int *labelLength)
{
    // printf("initializing line %d\n", lineNumber);
    // char words[16][16];
    splitLineIntoWords(codeLine, words);

    // check is there a label
    if (!(isDirective(words[0])))
    {
        // printf("words[0] is %d  ", strlen(words[0]));
        saveLabel(lineNumber, words[0], labels, &labelLength);
        removeLabelFromWords(words);
    }

    for (int i = 0; i < 16; i++)
        printf("%s ", words[i]);
    printf("\n");
}

void initializeProgram(char (*codeLines)[256], char (*words)[16][16], int codeLength, Label *labels, int *labelLength)
{
    printf("Initializing...\n");

    for (int i = 0; i < codeLength; i++)
        initializeLine(i, codeLines[i], words[i], labels, labelLength);

    printf("Program initialized succesfully\n");
}
// TODO: Put directives in struct
void A_directive()
{
    printf("ex A dir");
}

void AR_directive()
{
    printf("ex AR dir");
}

void S_directive()
{
    printf("ex S dir");
}

void SR_directive()
{
    printf("ex SR dir");
}

void M_directive()
{
    printf("ex M dir");
}

void MR_directive()
{
    printf("ex MR dir");
}

void D_directive()
{
    printf("ex D dir");
}

void DR_directive()
{
    printf("ex DR dir");
}

void C_directive()
{
    printf("ex C dir");
}

void CR_directive()
{
    printf("ex CR dir");
}

void J_directive()
{
    printf("ex J dir");
}

void JZ_directive()
{
    printf("ex JZ dir");
}

void JP_directive()
{
    printf("ex JP dir");
}

void JN_directive()
{
    printf("ex JN dir");
}

void L_directive()
{
    printf("ex L dir");
}

void LA_directive()
{
    printf("ex LA dir");
}

void LR_directive()
{
    printf("ex LR dir");
}

void ST_directive()
{
    printf("ex ST dir");
}

void DC_directive()
{
    printf("ex DC dir");
}

void DS_directive()
{
    printf("ex DS dir");
}

void executeLine(int lineNumber, char (*words)[16])
{
    printf("Executing line %d with first word %s\n", lineNumber, words[0]);
    printf("%s %s", directives[18], words[0]);
    if (stringsToBeSame(words[0], directives[0]))
    {
        A_directive();
    }
    else if (stringsToBeSame(words[0], directives[1]))
    {
        AR_directive();
    }
    else if (stringsToBeSame(words[0], directives[2]))
    {
        S_directive();
    }
    else if (stringsToBeSame(words[0], directives[3]))
    {
        SR_directive();
    }
    else if (stringsToBeSame(words[0], directives[4]))
    {
        M_directive();
    }
    else if (stringsToBeSame(words[0], directives[5]))
    {
        MR_directive();
    }
    else if (stringsToBeSame(words[0], directives[6]))
    {
        D_directive();
    }
    else if (stringsToBeSame(words[0], directives[7]))
    {
        DR_directive();
    }
    else if (stringsToBeSame(words[0], directives[8]))
    {
        C_directive();
    }
    else if (stringsToBeSame(words[0], directives[9]))
    {
        CR_directive();
    }
    else if (stringsToBeSame(words[0], directives[10]))
    {
        J_directive();
    }
    else if (stringsToBeSame(words[0], directives[11]))
    {
        JZ_directive();
    }
    else if (stringsToBeSame(words[0], directives[12]))
    {
        JP_directive();
    }
    else if (stringsToBeSame(words[0], directives[13]))
    {
        JN_directive();
    }
    else if (stringsToBeSame(words[0], directives[14]))
    {
        L_directive();
    }
    else if (stringsToBeSame(words[0], directives[15]))
    {
        LA_directive();
    }
    else if (stringsToBeSame(words[0], directives[16]))
    {
        LR_directive();
    }
    else if (stringsToBeSame(words[0], directives[17]))
    {
        ST_directive();
    }
    else if (stringsToBeSame(words[0], directives[18]))
    {
        DC_directive();
    }
    else if (stringsToBeSame(words[0], directives[19]))
    {
        DS_directive();
    }
}

int main()
{
    FILE *file;
    char codeLines[256][256];
    char words[256][16][16];
    Label labels[128];
    int labelLength = 0;
    file = fopen("sample.txt", "r");

    if (file != NULL)
    {
        printf("File loaded\n");
    }
    else
    {
        printf("Cannot find parseable file\n");
    };

    int codeLength = 0;
    char codeLineHandler[64];

    while (!feof(file))
    {
        fgets(codeLineHandler, 64, file);
        if (strlen(codeLineHandler) != 1)
        {
            strcpy(codeLines[codeLength], codeLineHandler);
            codeLength++;
        }
        else
        {
            printf("WARNING: There is empty line in given file. It will cause line numeration change");
        }
    };

    fclose(file);
    initializeProgram(codeLines, words, codeLength, labels, &labelLength);

    executeLine(1, words[0]);

    return 0;
}