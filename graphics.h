#ifndef GRAPHICS_H
#define GRAPHICS_H
/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : main.h                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Header for graphic functions                                */
/*                                                                           */
/*  Procedures : draw_snake_head(), clear_nake_tail(), draw_field(),         */
/*               draw_food()                                                 */
/*                                                                           */
/*  Author     : M.B�rtschi                                                  */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*  History    : 05.12.2012  File created                                    */
/*                                                                           */
/*  File       : graphics.h                                                  */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/
#include <GUI.h>

#include "main.h"

/* Makkros */
#define BACKCOLOR GUI_BLUE
#define SNAKECOLOR GUI_BLACK
#define FOODCOLOR GUI_RED
#define SNAKERAD 1

/* Globale Variablen */

void init_graphics();

void draw_snake_head();

void clear_snake_tail();

void draw_field();


void draw_food();

#endif
