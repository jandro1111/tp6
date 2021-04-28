// tp6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "mylcd.h"
#include "PanaLCD.h"
#include"micholcd.h"

using namespace std;
int main()
{
    if (init_allegro()) {
        cout << "fallo alegro init"<<endl;
    }
    else {
        PanaLCD prueba(2, 16, 100, 100);
        mylcd prueba2;
        micholcd prueba3;
        basicLCD* lcds[3] = { (basicLCD*)&prueba, (basicLCD*)&prueba2, (basicLCD*)&prueba3 };//(basicLCD*)&prueba3
        
        
        //lcd de micho//
        *lcds[2] << "mucho texto This file contains the 'main' function. Program execution begins and ends there.";
        al_rest(2.0); 
        *lcds[2] << 'h' << 'h' << 'h' << 'h';
        al_rest(2.0);
        lcds[2]->lcdSetCursorPosition(cursorPosition{ 1, 4 });     
        *lcds[2] << "ppppppppppppppppppppppppppppppp";
        al_rest(2.0);
        lcds[2]->lcdMoveCursorUp();
        lcds[2]->lcdSetCursorPosition(cursorPosition{ 0, 4 });
        lcds[2]->lcdClearToEOL();
        al_rest(2.0);
        *lcds[2] << "llll";
        al_rest(2.0);
        lcds[2]->lcdClear();
        *lcds[2] << "esto anda bien";
        al_rest(5.0);
        



        
        //lcd de agus//
        *lcds[0] << "mucho texto This file contains the 'main' function. Program execution begins and ends there.";
        al_rest(2.0);
        *lcds[0] << 'h' << 'h' << 'h' << 'h';
        al_rest(2.0);
        lcds[0]->lcdSetCursorPosition(cursorPosition{ 1, 4 });
        *lcds[0] << "ppppppppppppppppppppppppppppppp";
        al_rest(2.0);
        lcds[0]->lcdMoveCursorUp();
        lcds[0]->lcdSetCursorPosition(cursorPosition{ 0, 4 });
        lcds[0]->lcdClearToEOL();
        al_rest(2.0);
        *lcds[0] << "llll";
        al_rest(2.0);
        lcds[0]->lcdClear();
        *lcds[0] << "esto anda bien";
        al_rest(5.0);
        

        //lcd de jandro//
        
        *lcds[1] << "mucho texto This file contains the 'main' function. Program execution begins and ends there.";
        al_rest(2.0);
        *lcds[1] << 'h' << 'h' << 'h' << 'h';
        al_rest(2.0);
        lcds[1]->lcdSetCursorPosition(cursorPosition{ 1, 4 });   
        *lcds[1] << "ppppppppppppppppppppppppppppppp";
        al_rest(2.0);
        lcds[1]->lcdMoveCursorUp();
        lcds[1]->lcdSetCursorPosition(cursorPosition{ 0, 4 });
        lcds[1]->lcdClearToEOL();
        *lcds[1] << "llll";
        al_rest(2.0);
        lcds[1]->lcdClear();
        *lcds[1] << "esto anda bien";
        al_rest(2.0);

        destroy_allegro();
    }
    return 0;
}

