/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : main.c                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : main file for game                                          */
/*                                                                           */
/*  Procedures : main(), init_game(), randomize_food()                       */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 03.12.2012  File created                                    */
/*                                                                           */
/*  File       : LaserChess.h                                                */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

#include "main.h"

/* global variables */
volatile direction snake_direction;

int snake[SNAKE_BUFFER];
int head;
int tail;
int size;

location food;
location field_size;
int level;
