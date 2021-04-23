// tp6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"mylcd.h"
using namespace std;
int main()
{
    if (init_allegro()) {
        cout << "fallo alegro init"<<endl;
    }
    else {
        al_rest(2.0);

        mylcd prueba;
        prueba << "mucho texto This file contains the 'main' function. Program execution begins and ends there.";
        prueba.printdisp();
        al_rest(2.0);
        prueba << 'h' << 'o' << 'l' << 'a';
        prueba.printdisp();
        al_rest(2.0);
        prueba << "mucho texto";
        prueba.printdisp();
        al_rest(2.0);
        prueba.lcdMoveCursorUp();
        prueba.lcdClearToEOL();
        prueba << "algo";
        prueba.printdisp();
        al_rest(2.0);
        prueba.lcdClear();
        prueba << "esto anda bien";
        prueba.printdisp();
        al_rest(2.0);
        prueba.printcursor();
        destroy_allegro();
    }
    return 0;
}

