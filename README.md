# gödelnummer
**Uni Assingment WS 2021/22 HTWK Leipzig**

A C++ program that computes a Gödel number from a given string of characters with assigned values.

Files are not divided into folders as per requirement.

https://en.wikipedia.org/wiki/Gödel_numbering 

## ```Primes```
Primes are loaded at the program's start from a file. There are up to 60.000 primes provided from a file, but if they are exhausted, the next ones are calculated. Which is kind of unnecessary, but it removes a nasty ```try catch```.

## ```Translator```
Handles all sanitation, validation, converting of input term.

Characters that you want to include in your term can be assigned to numbers in the file ```zuweisungen.txt```. 

## ```GNumber```
Since Gödel numbers can get gigantic, a custom Number Class implementing some arithmetic oparators is needed.
The number is stored as a ```std::string``` in base 10, to mitigate the need to convert to base 10 each time the number is to be printed to the console.

Using the [long-multiplication](https://en.wikipedia.org/wiki/Multiplication_algorithm#Long_multiplication) algorythm.

Each new factor can be accumulated with the ```add_factor(prime, value)``` method.
