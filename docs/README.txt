# Pseudoassembly-interpreter
Author: Szymon Sieradzki

Program executes pseudoasembler code provided in .txt file using C.

## Recommended tools

- gcc compiler
- mingw bash terminal

## Avaiable Scripts

In the project directory, run:

### `gcc -o interpreter main.c`

Compiles app in order to use it. Gcc compiler might be sufficient.
App should be strictly run in full-windowed size on at least 1920x1080p display. 

### `./interpreter`

Runs compiled app in terminal. App will ask you for .txt file containing pseudoassebly code.  
If none is providen it will choose `sample.txt`. Default source path for pseudoassembly code is `src/`.

# Choosing mode

Interpreter provides two modes of execution: `default` and `debug`. 
Choosing first of them means code being executed at once. Results are shown before app finish it work. 
Debug mode executes code line by line and lets you interact by typing certain commands.

## Debug available commands

### `[Enter]`

Execution skips two next directive.

### `skip`

App switches to default mode and execute rest of code at once.

### `exit`

Exit command terminates current app proccess.

# Interface construction

Interface consists of 3 parts: Code, Registers, Memory.

### `Code` 

Code part is displayed in the left and shows code loaded from source file.
There is an arrow `->` indicating which command will execute next.

### `Registers`

Registers part is displayed in the middle of terminal. 
It shows values stored in certain registers and status registers value at the bottom.

### `Memory`

Memory part is displayed in the right of terminal. 
It shows programs memory informations. For each instance it shows address of cell in computer's memory, label assigned to cell and value stored there in that sequence. There is also an arrow `->` indicating which label of memory last directive asked for. If directive doesn't ask for label, arrow doesn't change its position.