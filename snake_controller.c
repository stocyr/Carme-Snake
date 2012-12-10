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

#include "main.h"
#include "snake_controller.h"

location snake[SNAKE_BUFFER];
int head = 0;
int tail = 0;
int size = 0;
int startup_size = INITIAL_SIZE;

enum result step_forward(int initial)
{
	location new_pos = snake[head];

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
	head = (++head)%SNAKE_BUFFER;
	snake[head] = new_pos;
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
		if(initial)
		{
			// länge bleibt zwar gleich. Tail löschen:
			clear_snake_tail(snake[tail]);
			// tail nachrutschen
			tail = (++tail)%SNAKE_BUFFER;
		}
		return NOTHING;
	}
}


enum result step_forward_initial()
{
	location new_pos = snake[head];

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
	head = (++head)%SNAKE_BUFFER;
	snake[head] = new_pos;
	draw_snake_head(snake[head]);

	size++;
	// wenn auf FOOD getroffen, FOOD zurückkliefern
	if(check_food_collision(new_pos))
	{
		// länge von Snake erhöhen
		startup_size++;
		return FOOD;
	}
	else
	{
		return NOTHING;
	}
}


int check_wall_collision(location pos)
{
	// wenn innerhalb der definierten Array-grenzen:
	if((pos.x < PLAYGROUND_X_MAX && pos.x >= 0) &&
	   (pos.y < PLAYGROUND_Y_MAX && pos.y >= 0))
	{
		// true zurückgeben
		return 1;
	}
	else
	{
		// false zurückgeben
		return 0;
	}
}


int check_snake_collision(location pos)
{
	int i;
	location proove;

	for(i = 0; i < size; i++)
	{
		proove = snake[(tail+i)%SNAKE_BUFFER];
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
}
