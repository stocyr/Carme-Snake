/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : main.c                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : main file for game                                          */
/*                                                                           */
/*  Procedures : main(), init_game(), randomize_food(), delay()              */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 03.12.2012  File created                                    */
/*                                                                           */
/*  File       : main.c                                                      */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/


#include "main.h"
#include "graphics.h"
#include "snake_controller.h"
#include "GUI.h"
#include "carme.h"
#include "bitopera.h"
#include "interrupt_ivo.h"
#include "interrupt.h"
//#include "randomc.h"

/* global variables */

volatile enum direction snake_direction;
volatile int timer_irq_flag = 0;

location food;
location field_size;
int level;


void init_game(enum direction init_dir)
{

}

int randomize()
{
	// chosen by fair dice roll.
	// guaranteed to be random.
	// http://xkcd.com/221/
	return 4;
}

location randomize_location()
{
	location pos;

	//pos.x = RanGen.IRandom(0, PLAYGROUND_X_MAX);
	//pos.y = RanGen.IRandom(0, PLAYGROUND_Y_MAX);

	pos.x = (GUI_GetTime() + randomize())%PLAYGROUND_X_MAX;
	pos.y = (GUI_GetTime() + randomize())%PLAYGROUND_X_MAX;

	return pos;
}

location randomize_food()
{
	location food;
	do
	{
		food = randomize_location();
	}
	while(check_snake_collision(food));

	return food;
}

void delay(int ms)
{
	///Timer starten - muesme dr timer i dere funktion starte, oder geit me eifach ga luege ob scho e interrupt isch cho, de ischme im schlimschte fau e ms z früeh fertig... hingäge ergäb se so e subere takt wo immer glich läng isch, we dr räscht vom code chürzer aus 1 ms geit...


	start_timer();
	while(ms > 0)
	{

		while(!timer_irq_flag);
		timer_irq_flag = 0;
		ms--;

	}
}
void restore_interruptstate(int old_state)
{
	/* Stellt den alten Interrupt-Zustand wieder her */
	if(old_state == 0)
	{
		enable_interrupts();
	}
	else
	{
		disable_interrupts();
	}
}


int main()
{
    int level = 1;
    int game_over = 0;

	init_graphics();		//Function um Grafik Lib zu initialisieren, gibt evtl später mal Errorcode zurück...
    init_counter();

    //CRandomMersenne RanGen(GUI_GetTime());

    while(1)
    {
    	disable_interrupts();
    	draw_field();
    	enable_interrupts();

    	init_snake();

    	start_timer();

    	// warten bis eine taste gedrückt wird, welche den initialen zustand von snake_direction ändert
		//while(snake_direction == 57); --> später wieder reinnehmen, wenn uart modul fertig.

		// jetzt food zeichnen
		food = randomize_food();
		draw_food(food);

		enable_interrupts();

		do
		{
			switch(step_forward(check_initial_state()))
			{
			case COLLISION:
				// send_max_score_and_level();
				level = 1;
				game_over = 1;
				break;
			case FOOD:
				food = randomize_food();
				disable_interrupts();
				draw_food(food);
				enable_interrupts();
				break;
			case NOTHING:
				break;
			}

			delay(200);
		}
		while(game_over != 1);

		game_over = 0;
    }

    return 0;
}
