// tp6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "mylcd.h"
#include "PanaLCD.h"
#include"micholcd.h"

using namespace std;
int main()
{

    ALLEGRO_DISPLAY* display;

    if (init_allegro(display)) {
        cout << "fallo alegro init" << endl;
        return 0;
    }
    else {

        basicLCD* lcds[3] = { new PanaLCD(2, 16, 0, 0), new mylcd(), new micholcd() };

        for (size_t i = 0; i < 3; i++)
        {
            //Ingreso cadena de 92 caracteres
            cout << "Ingreso cadena de 92 caract. \"mucho texto This file contains the 'main' function.Program execution begins and ends there.\"" << endl;
            *lcds[i] << "mucho texto This file contains the 'main' function. Program execution begins and ends there.";    
            al_rest(4.0);
            cout << "Inserto cuatro caracteres  \'h\' de a uno encadenando las inserciones. lcd << \'h\' << \'h\' << \'h\' << \'h\'" << endl;
            *lcds[i] << 'h' << 'h' << 'h' << 'h';
            al_rest(4.0);
            cout << "Posiciono el cursor en la 2da fila 5ta columna e inserto una cadena con el abcedario(las 27 letras)" << endl;
            lcds[i]->lcdSetCursorPosition(cursorPosition{ 1, 4 });
            *lcds[i] << "abcdefghijklmnopqrstuvwxyz";
            al_rest(4.0);
            cout << "Muevo el cursor arriba y limpio la linea. Se limpia la 1ra fila desde la 15ta columna en adelante" << endl;
            lcds[i]->lcdMoveCursorUp();
            lcds[i]->lcdClearToEOL();
            al_rest(4.0);
            cout << "Muevo el cursor abajo y limpio la linea. Se limpia la 2ra fila desde la 15ta columna en adelante" << endl;
            lcds[i]->lcdMoveCursorDown();
            lcds[i]->lcdClearToEOL();
            al_rest(4.0);
            cout << "inserto una cadena \"llll\"" << endl;
            *lcds[i] << "llll";
            al_rest(4.0);
            cout << "Limpio el display" << endl;
            lcds[i]->lcdClear();
            al_rest(4.0);
            cout << "Inserto \"esto anda bien\"" << endl;
            *lcds[i] << "esto anda bien";
            cout << endl << "Cambiamos al siguiente display..." << endl;
            al_rest(5.0);
        }
        destroy_allegro(display);
        delete lcds[0];
        delete lcds[1];
        delete lcds[2];
    }
    return 0;
}

