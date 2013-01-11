#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : snake_controller.c                             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : controlls the snake actions                                 */
/*                                                                           */
/*  Procedures : step_forward(), eat(), check_wall_collision(),              */
/*               check_snake_collision(), check_food_collision()             */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 03.12.2012  File created                                    */
/*                                                                           */
/*  File       : snake_controller.h                                          */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/
/**
 * \file snake_controller.h
 * Enthält Prototypen für das Modul 'snake_controller'.
 */

#include "main.h"

/* global variables */
extern int size;

/* prototypes */
enum result step_forward(int initial);
void eat(location food);
int check_wall_collision(location pos);
int check_snake_collision(location pos);
int check_food_collision(location pos);
int check_initial_state();
void init_snake();

#endif
