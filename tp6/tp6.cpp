// tp6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "mylcd.h"
#include "PanaLCD.h"


using namespace std;
int main()
{
    if (init_allegro()) {
        cout << "fallo alegro init"<<endl;
    }
    else {
        PanaLCD prueba(2, 16);
        prueba << "mucho texto This file contains the 'main' function. Program execution begins and ends there.";
        //prueba.printdisp();
        al_rest(2.0);
        prueba << 'h' << 'o' << 'l' << 'a';
        prueba.lcdSetCursorPosition(cursorPosition{ 2, 5 });
        //prueba.printdisp();
        al_rest(2.0);
        prueba << "pepefrgygfhfghffgb,bmbmbmbmbmbh";
        //prueba.printdisp();
        al_rest(2.0);
        //prueba.lcdMoveCursorUp();
        prueba.lcdSetCursorPosition(cursorPosition{ 1, 5 });
        prueba.lcdClearToEOL();
        //prueba << "algo";
        //prueba.printdisp();
        al_rest(2.0);
        prueba.lcdClear();
        prueba << "esto anda bien";
       // prueba.printdisp();
        al_rest(2.0);
       // prueba.printcursor();
        destroy_allegro();
    }
    return 0;
}

