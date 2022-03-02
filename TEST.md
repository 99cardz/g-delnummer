# Test

## Unit-Tests

Jede signifikate Funktion wird im programm `test.cpp` mit einigen test-cases getestet.

Compilieren: `g++ -std=c++11 test.cpp Primes.cpp Translator.cpp GNumber.cpp -o test -Wall`.
Ausführen: `./test`.

## Integrations-Tests 

Die Benutzung des Programms wurde durchwegs auf mögliche Fehler bei der Ein- & Ausgabe getestet.


## Error-Handling

-   Bei Eingabe von Falschen Zeichen wird der Benutzer auf diese hingewiesen.
-   Es wird Kontrolliert ob die Zeichen 0 und s in den Zuweisungen zu finden sind.
    Falls sie nicht enthalten sind, wird der Benutzer darauf hingewiesen. Da die Zeichen
    in diesem Fall vom Programm hinzugeführt werden, wird ein `std::out_of_range` Fehler 
    bei der Suche nach dem correspondierenden Wert ausgeschlossen.
-   Die Funktion convert_to_numbers() wird nur aufgerufen, sofern alle zeichen dem Übersetzer 
    bekannt sind. Somit wird ein `std::out_of_range` Fehler ausgeschlossen.
