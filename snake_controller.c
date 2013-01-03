/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : snake_controller.c                             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : controlls the snake actions                                 */
/*                                                                           */
/*  Procedures : step_forward(), check_wall_collision(),                     */
/*               check_snake_collision(), check_food_collision()             */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 03.12.2012  File created                                    */
/*                                                                           */
/*  File       : snake_controller.c                                          */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/
/**
 * \file snake_controller.c
 * Steuert das Verhalten der Schlange.
 * Das Zeichnen der Schlange ist aber Sache des Moduls 'graphics'.
 * Und der Spielablauf wird im Modul 'main' gesteuert.
 */

#include "main.h"
#include "graphics.h"
#include "snake_controller.h"

/**
 * Diese Variable ist ein Ringbuffer, der alle Positionen der Schlange enthält.
 * Die Variablen 'head', 'tail' und 'size' gehören auch dazu.
 */
location snake[SNAKE_BUFFER];

int head = 0;	///< Head des Ringbuffers 'snake[]'.
int tail = 0;	///< Tail des Ringbuffers 'snake[]'.
int size = 0;	///< Länge der Schlange im Ringbuffer 'snake[]'.
/**
 * Enthält die Länge der Schlange während dem Aufstarten.
 * Die Schlange beginnt als einzelnes Glied und wächst dann in die Richtung,
 * in die der Spieler das erste Mal gedrückt hat. Diese wachsende Länge wird
 * mit dieser Variable gespeichert. Schlussendlich ist dann nur noch die variable
 * 'size' des Ringbuffers dafür zuständig.
 */
int startup_size = INITIAL_SIZE;

enum result step_forward(int initial)
{
	location new_pos;
	new_pos.x = snake[head].x;
	new_pos.y = snake[head].y;

	switch(snake_direction)
		{
		case RIGHT:
			new_pos.x++;
			break;
		case UP:
			new_pos.y--;
			break;
		case LEFT:
			new_pos.x--;
			break;
		case DOWN:
			new_pos.y++;
			break;
		}

	// wenn eine kollision passieren würde, kollisipon zurückliefern, nicht mehr fahren.
	if(check_wall_collision(new_pos) || check_snake_collision(new_pos))
	{
		return COLLISION;
	}

	// head erhöhen
	head++;
	head %= SNAKE_BUFFER;
	snake[head].x = new_pos.x;
	snake[head].y = new_pos.y;
	draw_snake_head(snake[head]);

	if(initial)
	{
		size++;
	}

	// wenn auf FOOD getroffen, FOOD zurückkliefern
	if(check_food_collision(new_pos))
	{
		// länge von Snake erhöhen
		if(initial)
		{
			startup_size++;
		}
		else
		{
			size++;
		}
		return FOOD;
	}
	else
	{
		if(!initial)
		{
			// länge bleibt gleich. Tail löschen:
			clear_snake_tail(snake[tail]);
			// tail nachrutschen
			tail++;
			tail %= SNAKE_BUFFER;
		}
		return NOTHING;
	}
}


int check_wall_collision(location pos)
{
	// wenn innerhalb der definierten Array-grenzen:
	if((pos.x < PLAYGROUND_X_MAX && pos.x >= 0) &&
	   (pos.y < PLAYGROUND_Y_MAX && pos.y >= 0))
	{
		// false zurückgeben
		return 0;
	}
	else
	{
		// true zurückgeben
		return 1;
	}
}


int check_snake_collision(location pos)
{
	int i;
	location proove;

	for(i = 0; i < size; i++)
	{
		proove.x = snake[(tail+i)%SNAKE_BUFFER].x;
		proove.y = snake[(tail+i)%SNAKE_BUFFER].y;
		if(proove.x == pos.x && proove.y == pos.y)
		{
			return 1;
		}
	}
	return 0;
}


int check_food_collision(location pos)
{
	return food.x == pos.x && food.y == pos.y;
}


int check_initial_state()
{
	return size < startup_size;
}

void init_snake()
{
	head = 0;
	tail = 0;
	size = 1;
	snake[head].x = PLAYGROUND_X_MAX / 2;
	snake[head].y = PLAYGROUND_Y_MAX / 2;

	draw_snake_head(snake[head]);
}
