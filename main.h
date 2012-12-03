#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : main.h                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Header for main() (main.c)                                  */
/*                                                                           */
/*  Procedures : -                                                           */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 03.12.2012  File created                                    */
/*                                                                           */
/*  File       : main.h                                                      */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

/* Enumerations */

// direction
enum direction {RIGHT, UP, LEFT, DOWN}


/* Structs */

// location
typedef struct {
	int x;
	int y;
} location;


/* global variables */
extern volatile direction snake_direction;

extern int snake[SNAKE_BUFFER];
extern int head;
extern int tail;
extern int size;

extern location food;
extern location field_size;
extern int level;

#endif