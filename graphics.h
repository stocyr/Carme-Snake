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
/*  Procedures : draw_snake_head(), clear_snake_tail(), draw_field(),        */
/*               draw_food()                                                 */
/*                                                                           */
/*  Author     : M.Bärtschi                                                  */
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
/**
 * \file graphics.h
 * Enthält Makros und Prototypen für das Modul 'graphics.
 */

#include <GUI.h>

#include "main.h"

/* Makros */
#define BACKCOLOR GUI_BLUE			///< Hintergrundfarbe des Spielfeldes.
#define SNAKECOLOR GUI_BLACK		///< Farbe der Schlange.
#define FOODCOLOR GUI_RED			///< Farbe des Futters.
#define SNAKERAD 5					///< Radius der Schlangenglieder.
#define ELEMENT 10					///< Rasterbreite eines Schlangengliedes oder Futters in Pixel.
#define PLAYGROUND_X_MAX	32		///< Breite des Spielfeldes in Rastern.
#define PLAYGROUND_Y_MAX	24		///< Höhe des Spielfeldes in Rastern.
#define PLAYGROUND_TO_LCD(x) (x*ELEMENT+ELEMENT/2)	///< Umrechnungsmakrofunktion für Rasterposition -> Pixelposition.

/* prototypes */
void init_graphics();
void draw_snake_head();
void clear_snake_tail();
void draw_field();
void draw_food();

#endif
