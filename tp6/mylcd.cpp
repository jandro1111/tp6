#include "mylcd.h"
using namespace std;
/// basic lcd

basicLCD::basicLCD() {

}
basicLCD::~basicLCD() {

}
/// my lcd
mylcd::mylcd() {
	cursor.column = 0;
	cursor.row = 0;
	for (int i = 0; i < FILMAX; ++i) {
		for (int j = 0; j < COLMAX; ++j) {
			disp[i][j] = 0;
		}
	}
}
mylcd::~mylcd() {

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
	return succed;
}
bool mylcd::lcdClearToEOL() {
	bool succed = true;
	for (int j = 0; j < COLMAX; ++j) {
		disp[cursor.row][j] = 0;
	}
	cursor.column = 0;
	return succed;
}
basicLCD& mylcd::operator<<( const unsigned char c)
{
	if ((this->cursor.row==1) && (this->cursor.column==19)) {//no avanzo el cursor
		if ((c >= ' ') && (c <= '~')) {//si es un caracter imprimible
			this->disp[this->cursor.row][this->cursor.column] = c;
		}
	}else{//modifico el cursor
		if ((c >= ' ') && (c <= '~')) {//si es un caracter imprimible
			this->disp[this->cursor.row][this->cursor.column] = c;
			if (this->lcdMoveCursorRight()) {//si pude moverlo a la derecha
			}
			else {//si no lo muevo abajo
				this->lcdMoveCursorDown();
				this->cursor.column = 0;
			}
		}
	}
	return *this;
}
basicLCD& mylcd::operator<<(const char* c)
{
	for (int i = 0; c[i] != '\0';++i) {
		if ((this->cursor.row==(FILMAX-1)&& this->cursor.column==(COLMAX-1))&& this->disp[this->cursor.row][this->cursor.column]!='/0') {//si tengo el display lleno
			this->dispmoveleft();
			this->disp[this->cursor.row][this->cursor.column] = c[i];
		}
		else {
			this->disp[this->cursor.row][this->cursor.column] = c[i];
			if (this->lcdMoveCursorRight()) {//si pude moverlo a la derecha
			}
			else {//si no lo muevo abajo
				this->lcdMoveCursorDown();
				this->cursor.column = 0;
			}
		}
	}
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
	return succed;
}
cursorPosition mylcd::lcdGetCursorPosition() {
	return cursor;
}
void mylcd::printdisp() {
	for (int i = 0; i < FILMAX; ++i) {
		for (int j = 0; j < COLMAX; ++j) {
			cout << disp[i][j];
		}
		cout << endl;
	}
}
void mylcd::dispmoveleft() {
	for (int i = 0; i < FILMAX; ++i) {
		for (int j = 0; j < COLMAX; ++j) {
			if (j + 1 == COLMAX) {
				if (i + 1 == FILMAX) {//si estoy en el 1 19
					disp[i][j] = 0;
				}
				else {//estoy en el 0 19
					disp[i][j] = disp[i + 1][0];
				}
			}
			else {
				disp[i][j] = disp[i][j + 1];
			}
		}
	}
}
void mylcd::printcursor() {
	cout << "row: " << cursor.row << " column: " << cursor.column << endl;
}
// error lcd
lcdError::lcdError() {
	errorcode = 0;
	errordesc = "OK";
	errorname = "OK";
}
std::string lcdError::getErrorName() {
	return errorname;
}
std::string lcdError::getErrorDescription() {
	return errordesc;
}
unsigned long lcdError::getErrorCode() {
	return errorcode;
}