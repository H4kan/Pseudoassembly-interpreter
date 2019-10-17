#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// FILE *infile;

char directives[20][2] = {
    "A", "AR",
    "S", "SR", 
    "M", "MR", 
    "D", "DR", 
    "C", "CR", 
    "J", "JZ", "JP", "JN",
    "L", "LA", "LR", "ST",
    "DC", "DS"
    };
bool isDirective() {
    return true;
}

void splitLineIntoWords(char *codeLine, char (*words)[16]) {
    int j = 0;
    int k = 0;
    for (int i = 0; i < strlen(codeLine); ++i) {
        if ( codeLine[i] != ' ' && codeLine[i] != ',' ) words[j][k++] = codeLine[i];
        else {
            j++;
            k = 0;
        }
    }
}

int executeLine(char *codeLine) {
    char words[16][16];
    splitLineIntoWords(codeLine, words);
    int i = 0;
    while(codeLine[i] != ' ' || i == 10) {
    codeLine[i] = 'p';
    i++;
    }
}



int main() {
    FILE *file;
    char codeStrings[256][256];
    file = fopen("sample.txt", "r");
    if (file != NULL){ printf("hey \n"); }
    else{ printf("Error"); };
    int i = 0;
    while(!feof(file)) 
    {
        fgets(codeStrings[i], 64, file);
        i++;
    };
    fprintf(stdout, "%s", codeStrings[19]);
    executeLine(codeStrings[10]);
    fprintf(stdout, "%s", codeStrings[10]);
    fclose( file );

    return 0;
}