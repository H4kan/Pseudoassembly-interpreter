#ifndef directiveController

#define directiveController

void executeLine(char (*words)[MAX_WORD_LINE_LENGTH],
                 int *registers, Label *labels,
                 int labelLength,
                 int **memory,
                 MemLabel *memoryLabels,
                 int *currMemLabelLength,
                 int *numberOfVars,
                 char *stateRegister,
                 int *nextLineToExec,
                 bool *isFinished,
                 int *arrowMemory)
{
    if (stringsToBeSame(words[0], directives[0]))
    {
        A_directive(registers, words, *memory, memoryLabels, numberOfVars, stateRegister, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[1]))
    {
        AR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[2]))
    {
        S_directive(registers, words, *memory, memoryLabels, numberOfVars, stateRegister, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[3]))
    {
        SR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[4]))
    {
        M_directive(registers, words, *memory, memoryLabels, numberOfVars, stateRegister, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[5]))
    {
        MR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[6]))
    {
        D_directive(registers, words, *memory, memoryLabels, numberOfVars, stateRegister, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[7]))
    {
        DR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[8]))
    {
        C_directive(registers, words, *memory, memoryLabels, numberOfVars, stateRegister, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[9]))
    {
        CR_directive(registers, words, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[10]))
    {
        J_directive(words, labels, labelLength, nextLineToExec, isFinished);
    }
    else if (stringsToBeSame(words[0], directives[11]))
    {
        JZ_directive(words, labels, labelLength, nextLineToExec, isFinished, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[12]))
    {
        JP_directive(words, labels, labelLength, nextLineToExec, isFinished, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[13]))
    {
        JN_directive(words, labels, labelLength, nextLineToExec, isFinished, stateRegister);
    }
    else if (stringsToBeSame(words[0], directives[14]))
    {
        L_directive(registers, words, *memory, memoryLabels, numberOfVars, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[15]))
    {
        LA_directive(registers, words, *memory, memoryLabels, numberOfVars, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[16]))
    {
        LR_directive(registers, words);
    }
    else if (stringsToBeSame(words[0], directives[17]))
    {
        ST_directive(registers, words, *memory, memoryLabels, numberOfVars, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[18]))
    {
        DC_directive(words, *nextLineToExec, labels, labelLength, memory, memoryLabels, currMemLabelLength, numberOfVars, arrowMemory);
    }
    else if (stringsToBeSame(words[0], directives[19]))
    {
        DS_directive(words, *nextLineToExec, labels, labelLength, *memory, memoryLabels, currMemLabelLength, numberOfVars, arrowMemory);
    }
    else
        printUnDirective();

    *nextLineToExec = *nextLineToExec + 1;
}
#endif