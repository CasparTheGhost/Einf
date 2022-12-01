#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


char* number_to_binary(char* number, int base)
{
    int i, k, input;
    // Heap Allokation von 32 Bytes für das Char array, damit der String nach Ende der Funktion nicht gelöscht wird
    char* binary_res = malloc(32);
    //Setzt alle chars von binary_res auf ' '. Sonst hätte binary_res random chars
  
    //Konvertiert einen char* zu einem long int mit Hilfe der Parameter char const* _String, char** _EndPtr, int _Radix
    //Mehr Informationen auf https://cplusplus.com/reference/cstdlib/strtol/
    long int num = strtol(number, NULL, base);

    for (i = 31; i > -1; i--)
    {
        k = num >> i;
        if (k & 1)
            binary_res[31 - i] = '1';
        else
            binary_res[31 - i] = '0';
    }

    //Der Pointer zum String wird zurückgegeben
    return binary_res;
}

int from_binary_to_decimal(char* binary) {
    int decimal = 0;
    //Für positive Zahlen
    if (binary[0] == '0') {
        //Ziffern von rechts nach links durchgehen
        for (int i = 32; i >= 0; i--) {
            //Wenn Ziffer 1 ist, dann entsprechende Potenz von 2 addieren
            if (binary[i] == '1') {
                decimal += pow(2, 32 - i - 1);
            }
        }
    }
    //Für negative Zahlen
    else {
        //Ziffern von rechts nach links durchgehen
        for (int i = 32; i >= 0; i--) {
            if (binary[i] == '0') {
                //Wenn Ziffer 0 ist, dann entsprechende Potenz von 2 addieren
                decimal += pow(2, 32 - i - 1);
            }
        }
        //Zahl negieren
        decimal = ~decimal;
    }
    return decimal;
}

void print_binary_pretty(char* string) {
    printf("Binary: ");
    for (int i = 0; i < 32; i++) {
        printf("%c", string[i]);
        if ((i + 1) % 4 == 0)
            printf(" ");
    }
    printf("\n");
}


int main(int argc, char* argv[]) {
    
    //Hacker Farben in der Konsole
    system("color 02");

    // Ist die Anzahl der Argumente von der Funktion main(...) gleich 3 ?
    if (argc == 3) {

        //Speicherung des return Pointers der Funktion number_to_binay(...)
        //Die Argumente des Funktionsaufrufes sind die 2. und 3. Argumente der Hautpfunktion
        char* binary = number_to_binary(argv[1], atoi(argv[2]));

        //Der String, auf den der Pointer binary zeigt, wird ausgegeben
        printf("\n32 Bit Representation:\n\n");
        print_binary_pretty(binary);
        int binary_to_decimal = from_binary_to_decimal(binary);
        printf("Decimal: %d\n", binary_to_decimal);
        printf("Hexadecimal: %0x\n", binary_to_decimal);
        printf("Octal: %o\n", binary_to_decimal);

        //Der Arbeitsspeicher auf dem Heap, der mit malloc() allokiert wurde, wird jetzt wieder freigegeben
        free(binary);
    }
    // Sonst: Ausgabe der Nutzungsansweisungen
    else
        printf("Usage: %s <number> <base>", argv[0]);

    return 0;
}