#pragma once
#ifndef _LCD_H
#define _LCD_H
#include<string>
#include<iostream>
#include"allegro.h"
#include"basicLCD.h"

#define FILMAX 2
#define COLMAX 16
#define FONTPATH "7SDD.ttf"

class mylcd :public basicLCD {
public:
	mylcd();
	~mylcd();
	bool lcdInitOk();
	lcdError& lcdGetError();
	bool lcdClear();
	bool lcdClearToEOL();
	bool lcdMoveCursorUp();
	bool lcdMoveCursorDown();
	bool lcdMoveCursorRight();
	bool lcdMoveCursorLeft();
	bool lcdSetCursorPosition(const cursorPosition pos);
	cursorPosition lcdGetCursorPosition();
	basicLCD& operator<<(const unsigned char c);//este el de char
	basicLCD& operator<<(const char* c);//este es el de string
	
private:

	void printdisp(void);

	ALLEGRO_FONT* font;
	cursorPosition cursor;//row 0-1 column 0-19
	lcdError estado;
	char disp[FILMAX][COLMAX];
};





#endif