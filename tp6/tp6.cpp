// tp6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"lcd.h"
using namespace std;
int main()
{
    mylcd prueba;
    basicLCD* prueba1 = &prueba;
    prueba <<"mucho texto This file contains the 'main' function. Program execution begins and ends there.";
    prueba.printdisp();
    prueba << 'h' << 'o' << 'l' << 'a';
    prueba.printdisp();
    prueba << "mucho texto";
    prueba.printdisp();
    prueba.lcdMoveCursorUp();
    prueba.lcdClearToEOL();
    prueba << "algo";
    prueba.printdisp();
    prueba.lcdClear();
    prueba << "esto anda bien";
    prueba.printdisp();
    prueba.printcursor();
}

