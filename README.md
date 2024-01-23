# Project1-ComputerSystems2

To build a lexical analyzer for a programming language. Note that you are not (yet) to build a parser for the language, seeing as you have not been given a language specification (i.e. grammar)

Author: Eric Hansson

- What platform you developed your solution on (i.e Linux, OS/X, Windows (God forbid!), ...) <br>
Arch Linux

- any special details on how to compile your project <br>
Used a Makefile which creates a executable called `tokenify`, this is done by running this command:
```
make
```
- any special details on how to run your project <br>
To run the program you need to give the program a input file:
```
./tokenify <input>
```
- any known bugs your project has, and possible fixes to those bugs <br>
There is not any know bug in the program.

- an overview of how you solved the project. <br>
For the project I focused in implementing on piece at a time. Which meant building up the tabel correctly for each piece.
When I implemented one part I would try it out with a simple test case for that implementation. When everything was put
togeheter I tried more difficult test casesl.
