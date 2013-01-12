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
 * Diese Variable ist ein Ringbuffer, der alle Positionen der Schlange enth�lt.
 * Die Variablen 'head', 'tail' und 'size' geh�ren auch dazu.
 */
location snake[SNAKE_BUFFER];

int head = 0;	///< Head des Ringbuffers 'snake[]'.
int tail = 0;	///< Tail des Ringbuffers 'snake[]'.
int size = 0;	///< L�nge der Schlange im Ringbuffer 'snake[]'.


/**
 * Geht mit der Schlange einen Schritt in die eingeschlagene Richtung weiter.
 * Pr�ft dabei, ob entweder auf Futter gestossen wurde, oder ob eine Kollision
 * vorliegt. <br>
 *
 * Flowchart:
 * <img src="../../step_forward_Flowchart.png">
 *
 * @return gibt das Ergebnis dieses Schrittes zur�ck:
 * Entweder passierte gar nichts, die Schlange traf auf Futter oder es gab eine
 * Kollision
 */
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

	// wenn eine kollision passieren w�rde, kollision zur�ckliefern, nicht mehr fahren.
	if(check_wall_collision(new_pos) || check_snake_collision(new_pos))
	{
		return COLLISION;
	}

	// head erh�hen
	head++;
	head %= SNAKE_BUFFER;
	snake[head].x = new_pos.x;
	snake[head].y = new_pos.y;
	draw_snake_head(snake[head]);

	// wenn auf FOOD getroffen, FOOD zur�ckkliefern
	if(check_food_collision(new_pos))
	{
		// l�nge von Snake erh�hen
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

	if(initial)
	{
		// L�nge steigt am Anfang von 1 bis auf startup_size
		// (Schlange baut sich auf)
		size++;
	}
	else
	{
		// L�nge bleibt gleich. Tail l�schen:
		clear_snake_tail(snake[tail]);
		// Tail nachrutschen
		tail++;
		tail %= SNAKE_BUFFER;

		// bei nachgerutschtem Tail nochmal den Tail neu zeichnen (�sthetik)
		draw_snake_head(snake[tail]);
	}

	return NOTHING;
}


/**
 * �berpr�ft, ob eine Position ausserhalb des Spielfeldes ist.
 * @param pos �bergibt die zu pr�fende Position
 * @return liefert bei Kollision (= ausserhalb) 1, sonst 0
 */
int check_wall_collision(location pos)
{
	// wenn innerhalb der definierten Array-grenzen:
	if((pos.x < PLAYGROUND_X_MAX && pos.x >= 0) &&
	   (pos.y < PLAYGROUND_Y_MAX && pos.y >= 0))
	{
		// false zur�ckgeben
		return 0;
	}
	else
	{
		// true zur�ckgeben
		return 1;
	}
}


/**
 * �berpr�ft, ob eine Position sich auf der Schlange befindet.
 * @param pos �bergibt die zu pr�fende Position
 * @return liefert bei Kollision (= auf der Schlange) 1, sonst 0
 */
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


/**
 * �berpr�ft, ob sich Futter an einer einer gewissen Position befindet.
 * @param pos �bergibt die zu pr�fende Position
 * @return liefert bei Kollision (= auf dem Futter) 1, sonst 0
 */
int check_food_collision(location pos)
{
	return food.x == pos.x && food.y == pos.y;
}


/**
 * �berpr�ft, ob die Schlange sich noch im Aufstartmodus befindet.
 * Das heisst, sie hat noch nicht die volle L�nge von 'INITIAL_SIZE' erreicht.
 * @return liefert 1, wenn noch im Aufstartmodus, sonst 0
 */
int check_initial_state()
{
	return size < startup_size;
}


/**
 * Initialisiert den Ringbuffer der Schlange.
 */
void init_snake()
{
	head = 0;
	tail = 0;
	size = 1;
	snake[head].x = PLAYGROUND_X_MAX / 2;
	snake[head].y = PLAYGROUND_Y_MAX / 2;

	draw_snake_head(snake[head]);
}
