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

#include <GUI.h>

#include "graphics.h"

void init_graphics(void)
{
	GUI_Init();
}

void draw_snake_head(location head)
{
	GUI_SetColor(SNAKECOLOR);
	GUI_DrawCircle(head.x, head.y, SNAKERAD);
}

void clear_snake_tail(location tail)
{
	GUI_SetColor(BACKCOLOR);
	GUI_DrawCircle(tail.x, tail.y, SNAKERAD);
}

void draw_field(void)
{
	GUI_SetColor(BACKCOLOR);
	GUI_FillRect(0, 0, GUI_GetScreenSizeX(), GUI_GetScreenSizeY());
}

void draw_food(location food)
{
	GUI_SetColor(FOODCOLOR);
	GUI_DrawCircle(food.x, food.y, SNAKERAD);
}
