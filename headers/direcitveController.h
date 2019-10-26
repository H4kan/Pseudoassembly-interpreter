#include "util.h"
#include "directivePanel.h"


#ifndef directiveController
#define directiveController


void executeLine(int lineIndex, char (*words)[16], int *registers, Label *labels, int labelLength, Number *memory, int *numberOfVars, char *stateRegister)
{
    printf("Executing line %d with directive %s\n", lineIndex, words[0]);
    if (stringsToBeSame(words[0], directives[0]))
    {
        A_directive(registers, words, memory, numberOfVars, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[1]))
    {
        AR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[2]))
    {
        S_directive(registers, words, memory, numberOfVars, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[3]))
    {
        SR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[4]))
    {
        M_directive(registers, words, memory, numberOfVars, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[5]))
    {
        MR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[6]))
    {
        D_directive(registers, words, memory, numberOfVars, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[7]))
    {
        DR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[8]))
    {
        C_directive(registers, words, memory, numberOfVars, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[9]))
    {
        CR_directive(registers, words, stateRegister);
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
        DC_directive(words, lineIndex, labels, labelLength, memory, numberOfVars);
    }
    else if (stringsToBeSame(words[0], directives[19]))
    {
        DS_directive(words, lineIndex, labels, labelLength, memory, numberOfVars);
    }
}
#endif