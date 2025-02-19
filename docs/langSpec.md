# Pseudoassmebly specification

This file contains explanation of every directive implementation. 

## Introduction

Pseudoassembly executes line by line (except of jumps). Every line has a single command containing: 
- label (optional)
- directive
- first param
- second param (optional)

Command operates on fast access memory cells called registers (`<R>`) numerated from 0 to 15 normal memory cells (`<M>`) and eventually labels (`<L>`). Every cell requires 4 bytes of storage and saves integer type variable. Normal memory cells can be accessed two ways: using label assigned two cell during its declaration or using 
`address expression`.

## Status register
Status register is special type of register containg program status. There are 4 possible statuses:
- `00` means zero integer was returned
- `01` means positive integer was returned
- `10` means negative integer was returned
- `11` means some error occured

Arythmetic directives changes status register depending on value got from targeted register.
Arythmetic directives are A, AR, S, SR, M, MR, D, DR, C, CR.

## Address expression
After loading memory cell address to register (using `LA`), it is possible to access value stored in memory using syntax `S(R)` where S is integer representing how many bytes we want to shift and R is register contatining memory address. For example 4(0) allows us to get value stored in second memory cell after one that address is loaded to register 0.

## Directives

- `A <R> <M>` 
Increases value stored in R by M.

- `AR <R1> <R2>` 
Increases value stored in R1 by R2.

- `S <R> <M>`
Decreases value stored in R by M.

- `SR <R1> <R1>`
Decreases value stored in R1 by R2.


- `M <R> <M>`
Multiplies value stored in R by M.

- `MR <R1> <R2>`
Multiplies value stored in R1 by R2.

- `D <R> <M>`
Divides value stored in R by M.
Dividing by zero returns `11` status.

- `DR <R1> <R2>`
Divides value stored in R1 by R2.
Dividing by zero returns `11` status.
- `C <R> <M>`
Substracts M from R without changing any of the values. Result is passed to status.

- `CR <R1> <R2>`
Substracts R2 from R1 without changing any of the values. Result is passed to status.

- J `<L>` 
Searches for label `<L>` and makes next command executed to be one with this label. Providing label `KONIEC` immediately ends program execution.

- JZ `<L>` 
If status register is `00` searches for label `<L>` and makes next command executed to be one with this label else skips to next command. Providing label `KONIEC` immediately ends program execution.

- JP `<L>` 
If status register is `01` searches for label `<L>` and makes next command executed to be one with this label else skips to next command. Providing label `KONIEC` immediately ends program execution.

- JN `<L>` If status register is `10` searches for label `<L>` and makes next command executed to be one with this label else skips to next command. Providing label `KONIEC` immediately ends program execution.

- L `<R>` `<M>` 
Sets value stored in R to M.

- LA `<R>` `<M>` 
Sets value stored in R to M's address in computer memory.

- LR `<R1>` `<R2>` 
Sets value stored in R1 to R2.

- ST `<R>` `<M>` 
Sets value stored in M to R.

- `<L>` DC INTEGER(`<V>`) 
Allocates single memory cell with label `<L>` and value `<V>`.

- `<L>` DS INTEGER 
Allocates single memory cell with label `<L>` (value is not defined).

- `<L>` DC `<X>`*INTEGER(`<V>`) 
Allocates `<X>` memory cells with label `<L>` on first of them and value `<V>`in each of them.

- `<L>` DS `<X>`*INTEGER 
Allocates `<X>` memory cells with label `<L>` on first of them (values are not defined).


