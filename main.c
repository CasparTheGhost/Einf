#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


char* number_to_binary(char* number, int base)
{
    int i, k, input;
    // Heap Allokation von 32 Bytes f?r das Char array, damit der String nach Ende der Funktion nicht gel?scht wird
    char* binary_res = malloc(32);
    //Setzt alle chars von binary_res auf ' '. Sonst h?tte binary_res random chars
  
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

    //Der Pointer zum String wird zur?ckgegeben
    return binary_res;
}

int from_binary_to_decimal(char* binary) {
    int decimal = 0;
    //F?r positive Zahlen
    if (binary[0] == '0') {
        //Ziffern von rechts nach links durchgehen
        for (int i = 32; i >= 0; i--) {
            //Wenn Ziffer 1 ist, dann entsprechende Potenz von 2 addieren
            if (binary[i] == '1') {
                decimal += pow(2, 32 - i - 1);
            }
        }
    }
    //F?r negative Zahlen
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

//Separiert die Bin?rzahl nach 4 Bits mit einem Leerzeichen
void print_binary_pretty(char* string) {
    printf("Binary: ");
    for (int i = 0; i < 32; i++) {
        printf("%c", string[i]);
        if ((i + 1) % 4 == 0)
            printf(" ");
    }
    printf("\n");
}


//argument_count = Anzahl an Argumenten, die der main(...) ?bergeben werden.
//args[] String Array gef?llt mit Argumenten
int main(int argument_count, char* args[]) {
    
    //Hacker Farben in der Konsole
    system("color 02");

    // Ist die Anzahl der Argumente von der Funktion main(...) gleich 3 ?
    if (argument_count == 3) {

        //Speicherung des return Pointers der Funktion number_to_binay(...)
        //Die Argumente des Funktionsaufrufes sind die 2. und 3. Argumente der Hautpfunktion
        //Atoi kovertiert den String args[2] zu einem int
        char* binary = number_to_binary(args[1], atoi(args[2]));

        //Der String, auf den der Pointer binary zeigt, wird ausgegeben
        printf("\n32 Bit Representation:\n\n");

        //Aufruf der Funktion print_binary_pretty
        print_binary_pretty(binary);

        //Speicherung vom return wert der Funktion in die Variable binary_to_decimal
        int binary_to_decimal = from_binary_to_decimal(binary);

        //Ausgabe von binary_to_decimal mit printf Formatierung
        printf("Decimal: %d\n", binary_to_decimal);    
        printf("Hexadecimal: %0x\n", binary_to_decimal);
        printf("Octal: %o\n", binary_to_decimal);

        //Der Arbeitsspeicher auf dem Heap, der mit malloc() allokiert wurde, wird jetzt wieder freigegeben
        free(binary);
    }
    // Sonst: Ausgabe der Nutzungsansweisungen
    else
        printf("Usage: %s <number> <base>", args[0]);

    return 0;
}