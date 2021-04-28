#include "PanaLCD.h"

PanaLCD::PanaLCD(int rows, int columns, int offsetX, int offsetY) : lcdText(" "),
                                        cursorPos{ 1, 1},
                                        rowQuant(rows),
                                        columnQuant(columns),
                                        screenOffsetX(offsetX),
                                        screenOffsetY(offsetY)
{
    this->lcdText.resize(rowQuant* columnQuant, ' ');
    this->lcdClear();
}

bool PanaLCD::lcdInitOk()
{
    return false;
}

lcdError& PanaLCD::lcdGetError()
{
    return this->error;
}

bool PanaLCD::lcdClear()
{
    this->lcdText.replace(0 , this->rowQuant * this->columnQuant, this->rowQuant * this->columnQuant, ' ');
    this->cursorPos = cursorPosition{ 0, 0 };
    this->redraw();
    return true;
}

bool PanaLCD::lcdClearToEOL()
{
    try
    {
        this->lcdText.replace((this->cursorPos.row * columnQuant + this->cursorPos.column), this->columnQuant - this->cursorPos.column, this->columnQuant - this->cursorPos.column, ' ');
    }
    catch (const std::exception&)
    {
        
        return false;
    }

    redraw();
    return true;
}

basicLCD& PanaLCD::operator<<(const unsigned char c)
{
    unsigned char auxChar = c;
    if (c > 126 || c < 32)
    {
        auxChar = ' ';
    }

    this->lcdText.replace(this->cursorPos.row * columnQuant + this->cursorPos.column, 1, 1, auxChar);

    if (!this->lcdMoveCursorRight())
    {
        if (this->lcdMoveCursorDown())
        {
            cursorPos.column = 0;
        }
        else
        {
            cursorPos = cursorPosition{ 0, 0 };
        }
    }

    redraw();
    return *this;
}

basicLCD& PanaLCD::operator<<(const char* c)
{
    std::string auxString(c);
    if (auxString.length() > (rowQuant * columnQuant - (this->cursorPos.row * columnQuant + this->cursorPos.column + 1)))
    {
        this->lcdText.replace((this->cursorPos.row * columnQuant + this->cursorPos.column),
            rowQuant * columnQuant - (this->cursorPos.row * columnQuant + this->cursorPos.column),
            auxString,
            auxString.length() - (rowQuant * columnQuant - (this->cursorPos.row * columnQuant + this->cursorPos.column)), //- 2,
            auxString.length());
        cursorPos = cursorPosition{ rowQuant-1, columnQuant-1 };
    }
    else
    {
        this->lcdText.replace((this->cursorPos.row * columnQuant + this->cursorPos.column), auxString.length(), auxString);
        cursorPos.row += auxString.length() / columnQuant;
        cursorPos.column += auxString.length() % columnQuant;
    }
    redraw();
    return *this;
}

bool PanaLCD::lcdMoveCursorUp()
{
    if (cursorPos.row == 0 )
    {
        return false;
    }
    else
    {
        cursorPos.row--;
    }
    return true;
}

bool PanaLCD::lcdMoveCursorDown()
{
    if (cursorPos.row == rowQuant-1)
    {
        return false;
    }
    else
    {
        cursorPos.row++;
    }
    return true;
}

bool PanaLCD::lcdMoveCursorRight()
{
    if (cursorPos.column == columnQuant-1)
    {
        return false;
    }
    else
    {
        cursorPos.column++;
    }
    return true;
}

bool PanaLCD::lcdMoveCursorLeft()
{
    if (cursorPos.column == 0)
    {
        return false;
    }
    else
    {
        cursorPos.column--;
    }
    return true;
}

bool PanaLCD::lcdSetCursorPosition(const cursorPosition pos)
{
    if ((pos.row < 0 || pos.row >= rowQuant) || (pos.column < 0 || pos.column >= columnQuant))
    {
        return false;
    }
    else
    {
        this->cursorPos = pos;
    }
    redraw();
    return false;
}

cursorPosition PanaLCD::lcdGetCursorPosition()
{
    return cursorPosition();
}

bool PanaLCD::redraw()
{
    std::string auxStr;

    al_clear_to_color(al_map_rgb(255, 255, 255));

    ALLEGRO_FONT* font = NULL;
    font = al_load_ttf_font("7SDD.ttf", 36, 0); //HAY CREAR UN FONT PARA CADA TAMA�O DE LETRA :frowning: 
 
    for (int i = 0; i < rowQuant; ++i) {
        auxStr = this->lcdText.substr(i * columnQuant, columnQuant);
        al_draw_text(font, al_map_rgb(0, 0, 0), screenOffsetX, screenOffsetY + i* al_get_font_line_height(font), ALLEGRO_ALIGN_LEFT, auxStr.c_str());
    }
    al_draw_text(font, al_map_rgb(0, 0, 255), screenOffsetX + cursorPos.column * al_get_text_width(font, " "), screenOffsetY + cursorPos.row * al_get_font_line_height(font), ALLEGRO_ALIGN_LEFT, lcdText.substr(cursorPos.row * columnQuant + cursorPos.column, 1).c_str());
    al_flip_display();

    std::cout << lcdText << std::endl;
    return false;
}
