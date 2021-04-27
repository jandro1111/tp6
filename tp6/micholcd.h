#pragma once
#ifndef MICHO_H
#define MICHO_H
#include<string>
#include<iostream>
#include"allegro.h"
#include"basicLCD.h"

#define MAX 32

class micholcd :public basicLCD {
public:
	micholcd();
	~micholcd();
	virtual bool lcdInitOk();
	virtual lcdError& lcdGetError();
	virtual bool lcdClear();
	virtual bool lcdClearToEOL();
	virtual bool lcdMoveCursorUp();
	virtual bool lcdMoveCursorDown();
	virtual bool lcdMoveCursorRight();
	virtual bool lcdMoveCursorLeft();
	virtual bool lcdSetCursorPosition(const cursorPosition pos);
	virtual cursorPosition lcdGetCursorPosition();
	virtual basicLCD& operator<<(const unsigned char word);
	virtual basicLCD& operator<<(const char* word);
	void dispmoveleft(void);//corre todos los caracteres del display uno a la izquierda (0,0), y el de mas a la izquierda lo desaparece

private:
	cursorPosition cursor;
	lcdError share;
	char display[MAX];
	void redraw();
};





#endif
