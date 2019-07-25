# Corewar

## About
> _"Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer. These battle programs are written in an abstract assembly language called Redcode."_ (cf. [wiki](https://en.wikipedia.org/wiki/Core_War))

## Description

A team project to build a virtual machine where 'champions' written in an abstract assembly language fight over a defined memory space (full project instructions available [here](https://github.com/kadogams/42_projects/tree/master/corewar/resources/pdfs)).

The project consists of three parts:
- the assembler (asm binary) compiles the abstract assembly language into bytecode, which can be interpreted by the virtual machine
- the virtual machine (corewar binary) reads and executes the instructions in its 'arena'
- the champion (aaa.s source code file) contains a set of instructions written in abstract assembly language to be excetuted by the vm

## THE team
- [ak6o](https://bitbucket.org/%7B344991d2-71c3-4cd6-bf1f-30622ef14e1e%7D/)
- [AlexDef](https://bitbucket.org/%7B5662d1ce-264b-4d2b-a354-1b6599d12034%7D/)
- [bedazheng](https://github.com/bedazheng)
- [kadogams](https://github.com/kadogams)

## Requirements

- Mac OS X (for the MinilibX graphic library)

## Usage

- compile one or more .s files using the asm binary (premade champions available in [_./resouces/champs/_](https://github.com/kadogams/42_projects/tree/master/corewar/resources/champs))
- execute the corewar binary with your warrior(s) as arguments

### asm

```bash
./asm target_file.s
```

### corewar

```bash
./corewar [-a] [-dump N -v N] [-g] [-n N] <champion1.cor> [-n N] <...>
	-a	: Prints output from "aff" (Default is to hide it)
	-n N	: Sets the number of the next player
#### TEXT OUTPUT MODE ##########################################################
	-dump N	: Dumps memory after N cycles then exits
	-v N	: Verbosity levels, can be added together to enable several
			- 0 : Show only essentials
			- 1 : Show lives
			- 2 : Show cycles
			- 4 : Show operations (Params are NOT litteral ...)
			- 8 : Show deaths
			- 16 : Show PC movements (Except for jumps)
#### GRAPHICAL OUTPUT MODE #####################################################
	-g	: Graphical output mode for corewar
```
