#include "gba.h"
#include "gameCharacter.h"

#include "images/selfMaze.h"
#include <stdio.h>

// char *integer_to_char_int(int i) {

//     if (i == 0) {
//         return 48;
//     }
//     while (i != 0) {

//     }
// }

void changeCharPosition(u32 currentButtons, struct character *gameCharacter)
{
    // gameCharacter -> moves += 1;
    // gameCharacter -> moveInChar = gameCharacter -> moves;
    // gameCharacter -> moveInChar = itoa(gameCharacter -> moves, gameCharacter -> moveInChar, 10);

if (KEY_DOWN(BUTTON_DOWN, currentButtons))
    {   
        if (gameCharacter -> topLeftRow == (HEIGHT - gameCharacter -> height)) {
        gameCharacter->posChanged = 0;
        } else {
            gameCharacter->topLeftRow = gameCharacter->topLeftRow + 1;
            gameCharacter->lastpos = 1;
            gameCharacter -> posChanged = 1;
        }
    }
    else if (KEY_DOWN(BUTTON_LEFT, currentButtons))
    {
        if (gameCharacter -> topLeftCol == (0)) {
            gameCharacter -> posChanged = 0;
        } else {
            gameCharacter->topLeftCol -= 1;
            gameCharacter->lastpos = 2;
            gameCharacter -> posChanged = 1;
        }
    }
    else if (KEY_DOWN(BUTTON_RIGHT, currentButtons))
    {
        if (gameCharacter -> topLeftCol == (WIDTH - gameCharacter -> width)) {
            gameCharacter -> posChanged = 0;
        } else {
            gameCharacter->topLeftCol += 1;
            gameCharacter->lastpos = -2;
            gameCharacter -> posChanged = 1;
        }
    }
    else if (KEY_DOWN(BUTTON_UP, currentButtons))
    {
        if (gameCharacter -> topLeftRow == 0) {
            gameCharacter -> posChanged = 0;
        } else {
            gameCharacter->topLeftRow -= 1;
            gameCharacter->lastpos = -1;
            gameCharacter -> posChanged = 1;
        }
    }
    waitForVBlank();
    waitForVBlank();
    waitForVBlank();
}

void drawCharacter(struct character *gameCharacter, const unsigned short image[])
{
    // drawRectDMA(gameCharacter->topLeftRow, gameCharacter->topLeftCol, gameCharacter->width, gameCharacter->height, color);
    // setPixel(gameCharacter -> topLeftRow + 2, gameCharacter -> topLeftCol + 2, BLACK);
    // setPixel(gameCharacter->topLeftRow + 2, gameCharacter->topLeftCol + gameCharacter -> width - 3, BLACK);
    // setPixel(gameCharacter -> topLeftRow + 5, gameCharacter->topLeftCol + 2, BLACK);
    // setPixel(gameCharacter -> topLeftRow + 6, gameCharacter -> topLeftCol + 3, BLACK);
    // setPixel(gameCharacter->topLeftRow + 6, gameCharacter->topLeftCol + 4, BLACK);
    // setPixel(gameCharacter -> topLeftRow + 5, gameCharacter -> topLeftCol + 5, BLACK);

    drawImageDMA(gameCharacter -> topLeftRow, gameCharacter -> topLeftCol, gameCharacter -> width, gameCharacter -> height, image);

    switch (gameCharacter->lastpos)
    {
    case -1: // cover bottom part of character
        DMA[3].src = &maze[((gameCharacter->topLeftRow + gameCharacter->height) * WIDTH) + gameCharacter->topLeftCol];
        DMA[3].dst = &videoBuffer[((gameCharacter->topLeftRow + gameCharacter->height) * WIDTH) + gameCharacter->topLeftCol];
        DMA[3].cnt = gameCharacter->width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
        return;

    case -2: // cover left part of character
        for (int i = (gameCharacter->topLeftRow); i < gameCharacter->height + gameCharacter->topLeftRow; i++)
        {
            DMA[3].src = &maze[(i * WIDTH) + gameCharacter->topLeftCol - 1];
            DMA[3].dst = &videoBuffer[(i * WIDTH) + gameCharacter->topLeftCol] - 1;
            DMA[3].cnt = 1 | DMA_DESTINATION_FIXED | DMA_SOURCE_FIXED | DMA_ON;
        }
        return;

    case 1:
        // volatile u16 colorVal = BLUE;

        // DMA[3].src;
        DMA[3].src = &maze[(gameCharacter->topLeftRow - 1) * WIDTH + gameCharacter->topLeftCol];
        DMA[3].dst = &videoBuffer[(gameCharacter->topLeftRow - 1) * WIDTH + gameCharacter->topLeftCol];
        DMA[3].cnt = gameCharacter->width | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
        return;

    case 2: // cover right
        for (int i = (gameCharacter->topLeftRow); i < gameCharacter->topLeftRow + gameCharacter->height; i++)
        {
            DMA[3].src = &maze[(i * WIDTH) + gameCharacter->topLeftCol + gameCharacter->width];
            DMA[3].dst = &videoBuffer[(i * WIDTH) + gameCharacter->topLeftCol + gameCharacter->width];
            DMA[3].cnt = 1 | DMA_DESTINATION_FIXED | DMA_SOURCE_FIXED | DMA_ON;
        }
        return;
    }
}

int validKeyPress(u32 current, struct character gamecharacter)
{
    if ((KEY_DOWN(BUTTON_DOWN, current)) || (KEY_DOWN(BUTTON_LEFT, current)) || (KEY_DOWN(BUTTON_RIGHT, current)) || (KEY_DOWN(BUTTON_UP, current)))
        {
        gamecharacter.moves += 1;
        return 1;
    }
    else
    {
        return 0;
    }
}

void checkIfDie(struct character *gameCharacter)
{
    // int topPixelPos = ((gameCharacter -> topLeftRow - 1) * WIDTH) + gameCharacter -> topLeftCol;
    if ((gameCharacter -> topLeftRow == 159 - gameCharacter -> height ) && (gameCharacter -> topLeftCol < 222) && (gameCharacter -> topLeftCol > 100)) {
        gameCharacter -> won = 1;
    }


    for (int r = gameCharacter->topLeftRow; r < ((gameCharacter->topLeftRow) + gameCharacter->height); r++)
    {
        for (int c = gameCharacter->topLeftCol; c < ((gameCharacter->topLeftCol) + gameCharacter->width); c++)
        {   
            
            if (maze[(r * WIDTH) + c] == BLACK)
            {
                gameCharacter->won = -1;
                return;
            }
        }
    }
}