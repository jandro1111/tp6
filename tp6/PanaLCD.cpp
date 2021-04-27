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
    this->cursorPos = cursorPosition{ 1, 1 };
    this->redraw();
    return true;
}

bool PanaLCD::lcdClearToEOL()
{
    try
    {
        this->lcdText.replace(((this->cursorPos.row - 1) * columnQuant + this->cursorPos.column) - 1, this->columnQuant - this->cursorPos.column + 1, this->columnQuant - this->cursorPos.column + 1, ' ');
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
    this->lcdText.replace(((this->cursorPos.row - 1) * columnQuant + this->cursorPos.column) - 1, 1, 1, c);

    if (!this->lcdMoveCursorRight())
    {
        if (this->lcdMoveCursorDown())
        {
            cursorPos.column = 1;
        }
        else
        {
            cursorPos = cursorPosition{ 1, 1 };
        }
    }

    redraw();
    return *this;
}

basicLCD& PanaLCD::operator<<(const char* c)
{
    std::string auxString(c);
    if (auxString.length() > (rowQuant * columnQuant - ((this->cursorPos.row - 1) * columnQuant + this->cursorPos.column)))
    {
        this->lcdText.replace(((this->cursorPos.row - 1) * columnQuant + this->cursorPos.column) - 1, rowQuant * columnQuant - ((this->cursorPos.row - 1) * columnQuant + this->cursorPos.column) + 1, auxString, auxString.length() - (rowQuant * columnQuant - ((this->cursorPos.row - 1) * columnQuant + this->cursorPos.column)) - 1, auxString.length());
        cursorPos = cursorPosition{ 1, 1 };
    }
    else
    {
        this->lcdText.replace(((this->cursorPos.row - 1) * columnQuant + this->cursorPos.column) - 1, auxString.length(), auxString);
        cursorPos.row += auxString.length() / columnQuant;
        cursorPos.column += auxString.length() % columnQuant;
    }
    redraw();
    return *this;
}

bool PanaLCD::lcdMoveCursorUp()
{
    if (cursorPos.row == 1 )
    {
        return false;
    }
    else
    {
        cursorPos.row--;
    }
    redraw();
    return true;
}

bool PanaLCD::lcdMoveCursorDown()
{
    if (cursorPos.row == rowQuant)
    {
        return false;
    }
    else
    {
        cursorPos.row++;
    }
    redraw();
    return true;
}

bool PanaLCD::lcdMoveCursorRight()
{
    if (cursorPos.column == columnQuant)
    {
        return false;
    }
    else
    {
        cursorPos.column++;
    }
    redraw();
    return true;
}

bool PanaLCD::lcdMoveCursorLeft()
{
    if (cursorPos.column == 1)
    {
        return false;
    }
    else
    {
        cursorPos.column--;
    }
    redraw();
    return true;
}

bool PanaLCD::lcdSetCursorPosition(const cursorPosition pos)
{
    if ((pos.row <= 0 || pos.row > rowQuant) || (pos.column <= 0 || pos.column > columnQuant))
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
    font = al_load_ttf_font("7SDD.ttf", 36, 0); //HAY CREAR UN FONT PARA CADA TAMAÑO DE LETRA :frowning: 
 
    for (int i = 0; i < rowQuant; ++i) {
        auxStr = this->lcdText.substr(i * columnQuant, columnQuant);
        al_draw_text(font, al_map_rgb(0, 0, 0), screenOffsetX, screenOffsetY + i* al_get_font_line_height(font), ALLEGRO_ALIGN_LEFT, auxStr.c_str());
    }
    al_draw_text(font, al_map_rgb(0, 0, 255), screenOffsetX + (cursorPos.column - 1) * al_get_text_width(font, " "), screenOffsetY + (cursorPos.row - 1) * al_get_font_line_height(font), ALLEGRO_ALIGN_LEFT, lcdText.substr((cursorPos.row - 1) * columnQuant + cursorPos.column - 1, 1).c_str());
    al_flip_display();
    return false;
}
