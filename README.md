# gödelnummer

**Uni Assingment WS 2021/22 HTWK Leipzig**

https://en.wikipedia.org/wiki/Gödel_numbering 

## Primes
Primes are loaded at programm start from a file. Provided are up to 60.000 primes, and if they are exhausted, next ones are Calculated. Wich is kind of unnessesery but it removes a nasty ```try catch```.

## Translator
Handles all input sanitation to turning the input into a usable string. Checks for valid input.

## GNumber
Custom Number Type to allow Bigger Integers than uint64. Only methematical operation implemented is Multiplication using  the [long-multiplication](https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication) algorythm.
