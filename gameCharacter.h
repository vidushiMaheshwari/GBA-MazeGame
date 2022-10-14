#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "gba.h"

struct character
{
    int topLeftRow;
    int topLeftCol;
    int height;
    int width;
    int won;
    int moves;
    char *hundereds_val;
    char *tens_val;
    char *units_val;
    int posChanged;
    int lastpos; // -2 -> char moved to right, -1 -> char moved to up, 1 -> char moved down, 2 -> char moved to left
};

void changeCharPosition(u32 currentButtons, struct character *gc);

void drawCharacter(struct character *gc,const unsigned short character[]);

int validKeyPress(u32 current, struct character gc);

void checkIfDie(struct character *gameCharacter);

#endif