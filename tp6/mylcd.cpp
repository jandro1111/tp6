#include "mylcd.h"
using namespace std;

/// my lcd
mylcd::mylcd() : estado("OK", "Ok", OK) {
	cursor.column = 0;
	cursor.row = 0;
	for (int i = 0; i < FILMAX; ++i) {
		for (int j = 0; j < COLMAX; ++j) {
			disp[i][j] = 0;
		}
	}
	font = al_load_ttf_font(FONTPATH, 36, 0);
	if (font == NULL)
	{
		estado = lcdError("INITERR", "Error al cargar fuente", INITERR);
	}
}
mylcd::~mylcd() {
	al_destroy_font(font);
}
bool mylcd::lcdInitOk() {
	return 1;
}
lcdError& mylcd::lcdGetError() {
		return estado;
}
bool mylcd::lcdClear() {
	bool succed = true;
	for (int i = 0; i < FILMAX; ++i) {
		for (int j = 0; j < COLMAX; ++j) {
			disp[i][j] = 0;
		}
	}
	cursor.column = 0;
	cursor.row = 0;
	printdisp();
	return succed;
}
bool mylcd::lcdClearToEOL() {
	bool succed = true;
	for (int j = cursor.column; j < COLMAX; ++j) {
		disp[cursor.row][j] = 0;
	}
	printdisp();
	return succed;
}
basicLCD& mylcd::operator<<( const unsigned char c)
{
	if ((c >= ' ') && (c <= '~')) {//si es un caracter imprimible
		this->disp[this->cursor.row][this->cursor.column] = c;
		if (this->lcdMoveCursorRight()) {//si pude moverlo a la derecha
		}
		else {//si no lo muevo abajo
			if (this->lcdMoveCursorDown()) {
				this->cursor.column = 0;
			}
			else {//si no sigo por el 0 0
				this->cursor.column = 0;
				this->cursor.row = 0;
			}			
		}
		printdisp();
	}
	return *this;
}
basicLCD& mylcd::operator<<(const char* c)
{
	int ini = 0;
	int counter = 0;
	for (int i = 0; c[i] != '\0';++i) {
		++counter;
	}
	if (counter > FILMAX * COLMAX) {
		ini = (counter - FILMAX * COLMAX);
	}
	for (; c[ini] != '\0';++ini) {
		this->disp[this->cursor.row][this->cursor.column] = c[ini];
		if (!this->lcdMoveCursorRight()) //si no pude moverlo a la derecha
		{//lo muevo abajo
			if (this->lcdMoveCursorDown()) {
				this->cursor.column = 0;
			}
			else {//si no sigo por el 0 0
				this->cursor.column = 0;
				this->cursor.row = 0;
			}
		}
	}
	printdisp();
	return *this;
}

bool mylcd::lcdMoveCursorUp() {
	bool succed = true;
	cursorPosition aux;
	aux.row = cursor.row;
	aux.row--;
	if (aux.row >=FILMAX || aux.row < 0) {//es diferente de 0-19
		succed = false;
	}
	else {
		cursor.row = aux.row;
	}
	return succed;
}
bool mylcd::lcdMoveCursorDown() {
	bool succed = true;
	cursorPosition aux;
	aux.row = cursor.row;
	aux.row++;
	if (aux.row >= FILMAX || aux.row < 0) {//es diferente de 0-19
		succed = false;
	}
	else {
		cursor.row = aux.row;
	}
	return succed;
}
bool mylcd::lcdMoveCursorRight() {
	bool succed = true;
	cursorPosition aux;
	aux.column = cursor.column;
	aux.column++;
	if (aux.column >=COLMAX || aux.column < 0) {//es diferente de 0-19
		succed = false;
	}
	else {
		cursor.column = aux.column;
	}
	return succed;
}
bool mylcd::lcdMoveCursorLeft() {
	bool succed = true;
	cursorPosition aux;
	aux.column = cursor.column;
	aux.column--;
	if (aux.column >=COLMAX || aux.column < 0) {//es diferente de 0-19
		succed = false;
	}
	else {
		cursor.column = aux.column;
	}
	return succed;
}
bool mylcd::lcdSetCursorPosition(const cursorPosition pos) {
	bool succed = true;
	if (pos.row >=FILMAX || pos.row < 0) {//es diferente de 0-1
		succed = false;
	}
	else {
		cursor.row = pos.row;
	}
	if (succed == false) {//si ya fallo en setear la fila salgo
		return succed;
	}
	else {
		if (pos.column >=COLMAX || pos.column < 0) {//es diferente de 0-19
			succed = false;
		}
		else {
			cursor.column = pos.column;
		}
	}
	printdisp();
	return succed;
}
cursorPosition mylcd::lcdGetCursorPosition() {
	return cursor;
}
void mylcd::printdisp() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	string aux=""; 
	string aux1 = "";
	ALLEGRO_FONT* font = NULL;
	font = al_load_ttf_font("7SDD.ttf", 36, 0); //HAY CREAR UN FONT PARA CADA TAMA?O DE LETRA :frowning: 
	for (int i = 0; i < FILMAX; ++i) {
		cout << " * ";
		for (int j = 0; j < COLMAX; ++j) {
			cout << disp[i][j];
			if (i == 0) {
				aux += disp[i][j];
			}
			else {
				aux1 += disp[i][j];
			}
		}
		cout << endl;
	}
	cout << endl << endl;
	al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, aux.c_str());
	al_draw_text(font, al_map_rgb(255, 255, 255), 0 , 30, ALLEGRO_ALIGN_LEFT, aux1.c_str());
	al_flip_display();
}

