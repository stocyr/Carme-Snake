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

#include main.h

/* prototypes */
result step_forward();
void eat(location food);
int check_wall_collision(location field_size);
int check_snake_collision();
int check_food_collision(location food);

#endif