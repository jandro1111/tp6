#include "micholcd.h"
using namespace std;

/*
basicLCD::basicLCD() {

}
basicLCD::~basicLCD() {

}
*/
/// micho lcd Constructor
micholcd::micholcd() {
	cursor.column = 0;
	cursor.row = 0;
	for (int i = 0; i < MAX; ++i) {
		display[i] = 0;
	}
}

//Destructor
micholcd::~micholcd() {

}

//OK?
bool micholcd::lcdInitOk() {
	return true;
}

//ERROR?
lcdError& micholcd::lcdGetError() {
	return this->share;
}

//Limpio display
bool micholcd::lcdClear() {
	for (int i = 0; i < MAX; ++i) {
		display[i]= 0;
	}
	cursor.column = 0;
	cursor.row = 0;
	redraw();
	return true;
}

//Borrra hasta el cursor
bool micholcd::lcdClearToEOL() {
	for (int i = cursor.column; i < (MAX/2); ++i) {
		display[cursor.row * (MAX/2) + i] = 0;
	}
	cursor.column = 0;
	redraw();
	return true;
}


basicLCD& micholcd::operator<<(const unsigned char word)
{
	if ((this->cursor.row == 1) && (this->cursor.column == ((MAX / 2)-1))) {
		if ((word >= ' ') && (word <= '~')) {
			this->display[(this->cursor.row * (MAX / 2)) + (this->cursor.column)] = word;
		}
	}
	else {
		if ((word >= ' ') && (word <= '~')) {
			this->display[(this->cursor.row * (MAX / 2)) + (this->cursor.column)] = word;
			if (this->lcdMoveCursorRight()) {
			}
			else {
				this->lcdMoveCursorDown();
				this->cursor.column = 0;
			}
		}
	}
	redraw();
	return *this;
}


basicLCD& micholcd::operator<<(const char* word)
{
	for (int i = 0; word[i] != '\0'; ++i) {
		if ((this->cursor.row && this->cursor.column == ((MAX/2) - 1)) && this->display[(this->cursor.row * MAX / 2) + (this->cursor.column)] != '/0') {
			this->dispmoveleft();
			this->display[(this->cursor.row * MAX / 2) + (this->cursor.column)] = word[i];
		}
		else {
			this->display[(this->cursor.row * (MAX / 2)) + (this->cursor.column)] = word[i];
			if (this->lcdMoveCursorRight()) {
			}
			else {
				this->lcdMoveCursorDown();
				this->cursor.column = 0;
			}
		}
	}
	redraw();
	return *this;
}


bool micholcd::lcdMoveCursorUp() {
	bool estado = true;
	cursorPosition temp;
	temp.row = cursor.row;
	temp.row--;
	if (temp.row != 1 && temp.row != 0) {
		estado = false;
	}
	else {
		cursor.row = temp.row;
	}
	return estado;
}


bool micholcd::lcdMoveCursorDown() {
	bool estado = true;
	cursorPosition temp;
	temp.row = cursor.row;
	temp.row++;
	if (temp.row != 1 && temp.row != 0) {
		estado = false;
	}
	else {
		cursor.row = temp.row;
	}
	return estado;
}


bool micholcd::lcdMoveCursorRight() {
	bool estado = true;
	cursorPosition temp;
	temp.column = cursor.column;
	temp.column++;
	if (temp.column >= (MAX / 2) || temp.column < 0) {
		estado = false;
	}
	else {
		cursor.column = temp.column;
	}
	return estado;
}


bool micholcd::lcdMoveCursorLeft() {
	bool estado = true;
	cursorPosition temp;
	temp.column = cursor.column;
	temp.column--;
	if (temp.column >= (MAX / 2) || temp.column < 0) {
		estado = false;
	}
	else {
		cursor.column = temp.column;
	}
	return estado;
}


bool micholcd::lcdSetCursorPosition(const cursorPosition pos) {
	bool estado = true;
	if (pos.row != 1 && pos.row != 0) {
		estado = false;
	}
	else {
		cursor.row = pos.row;
	}
	if (estado == false) {
		return estado;
	}
	else {
		if (pos.column >= (MAX / 2) || pos.column < 0) {
			estado = false;
		}
		else {
			cursor.column = pos.column;
		}
	}
	return estado;
}


cursorPosition micholcd::lcdGetCursorPosition() {
	return this->cursor;
}

void micholcd::dispmoveleft() {
	for (int i = 0; i < MAX; ++i) {
		if ((i + 1) == MAX) {
			display[i] = 0;
		}
		else{
			display[i] = display[i + 1];
		}
	}
}


void micholcd::redraw(){
	string temp = "";
	string tem = "";
	for (int i = 0; i < MAX; ++i) {
		cout << display[i];
		if (i < (MAX / 2)) {
			temp += display[i];
		}
		else {
			tem += display[i];
		}
	}
	cout << endl;
	al_clear_to_color(al_map_rgb(0, 0,255));
	ALLEGRO_FONT* fuentemicho = NULL;
	fuentemicho = al_load_ttf_font("fuentemicho.TTF", 40, 0);
	al_draw_text(fuentemicho, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, temp.c_str());
	al_draw_text(fuentemicho, al_map_rgb(255, 255, 255), 0, 46, ALLEGRO_ALIGN_LEFT, tem.c_str());
	al_flip_display();
}
