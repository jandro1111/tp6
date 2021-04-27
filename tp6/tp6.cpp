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
        PanaLCD prueba(2, 16, 100, 100);
        mylcd prueba2;

        basicLCD* lcds[3] = { (basicLCD*)&prueba, (basicLCD*)&prueba2, nullptr };
        *lcds[0] << "mucho texto This file contains the 'main' function. Program execution begins and ends there.";
        al_rest(2.0);
        *lcds[0] << 'h' << 'o' << 'l' << 'a';
        lcds[0]->lcdSetCursorPosition(cursorPosition{ 2, 5 });
        al_rest(2.0);
        *lcds[0] << "pepefrgygfhfghffgb,bmbmbmbmbmbh";
        al_rest(2.0);
        lcds[0]->lcdMoveCursorUp();
        lcds[0]->lcdSetCursorPosition(cursorPosition{ 1, 5 });
        lcds[0]->lcdClearToEOL();
        *lcds[0] << "algo";
        al_rest(2.0);
        lcds[0]->lcdClear();
        *lcds[0] << "esto anda bien";
        al_rest(2.0);


        
        *lcds[1] << "mucho texto This file contains the 'main' function. Program execution begins and ends there.";
        prueba2.printdisp();
        al_rest(2.0);
        *lcds[1] << 'h' << 'o' << 'l' << 'a';
        prueba2.lcdSetCursorPosition(cursorPosition{ 2, 5 });
        prueba2.printdisp();
        al_rest(2.0);        
        *lcds[1] << "pepefrgygfhfghffgb,bmbmbmbmbmbh";
        prueba2.printdisp();
        al_rest(2.0);
        lcds[1]->lcdMoveCursorUp();
        lcds[1]->lcdSetCursorPosition(cursorPosition{ 1, 5 });
        lcds[1]->lcdClearToEOL();
        *lcds[1] << "algo";
        prueba2.printdisp();
        al_rest(2.0);
        lcds[1]->lcdClear();
        *lcds[1] << "esto anda bien";
        prueba2.printdisp();
        al_rest(2.0);
        prueba2.printcursor();

        destroy_allegro();
    }
    return 0;
}

