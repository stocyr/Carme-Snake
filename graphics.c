/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : graphics.c                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : graphics functions for snake game                           */
/*                                                                           */
/*  Procedures : draw_snake_head(), clear_nake_tail(), draw_field(),         */
/*               draw_food()                                                 */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 03.12.2012  File created                                    */
/*                                                                           */
/*  File       : graphics.c                                                  */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/
/**
 * \file graphics.c
 * Enthält Grafikfunktionen für das LCD auf dem CARME Kit.
 */

#include <GUI.h>

#include "graphics.h"


/**
 * Initialisiert die GUI Funktionen der mitgelieferten CARME GUI Library.
 */
void init_graphics(void)
{
	GUI_Init();
}


/**
 * Zeichnet ein Snake-Glied.
 * @param pos gibt die Rasterposition an, an der gezeichnet werden soll
 */
void draw_snake_head(location head)
{
	GUI_SetColor(SNAKECOLOR);
	GUI_DrawCircle(PLAYGROUND_TO_LCD(head.x), PLAYGROUND_TO_LCD(head.y), SNAKERAD);
}

/**
 * Löscht ein Snake-Glied.
 * @param pos gibt die Rasterposition an, an der ein Snake-Glied gelöscht werden soll
 */
void clear_snake_tail(location tail)
{
	GUI_SetColor(BACKCOLOR);
	GUI_DrawCircle(PLAYGROUND_TO_LCD(tail.x), PLAYGROUND_TO_LCD(tail.y), SNAKERAD);
}


/**
 * Zeichnet das Spielfeld.
 * Die Hintergrundfarbe ist mit Makros in der Datei \file graphics.h definiert.
 */
void draw_field(void)
{
	GUI_SetColor(BACKCOLOR);
	GUI_FillRect(0, 0, GUI_GetScreenSizeX(), GUI_GetScreenSizeY());
}


/**
 * Zeichnet Futter.
 * @param pos gibt die Rasterposition an, an der gezeichnet werden soll
 */
void draw_food(location food)
{
	GUI_SetColor(FOODCOLOR);
	GUI_DrawCircle(PLAYGROUND_TO_LCD(food.x), PLAYGROUND_TO_LCD(food.y), SNAKERAD);
}
