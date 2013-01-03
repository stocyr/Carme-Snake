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
/**
 * \file main.c
 * Hauptdatei des Projekts.
 * Diese Datei enthält die spielsteuernden Funktionen.
 */

#include "main.h"
#include "graphics.h"
#include "snake_controller.h"
#include "GUI.h"
#include "carme.h"
#include "bitopera.h"
#include "marsenne.h"

/* global variables */
/**
 * Globale Variable, welche vom Interrupthandler über UART aktualisiert wird.
 * Die Variable ist das Interface zur UART Schnittstelle. Sie enthält die Richtung,
 * in die die Schlange steuern soll. Wird per PC Tastatur gesteuert und dann per
 * UART zum CARME Kit gesendet. <p>
 * Bevor überhaupt eine Taste gedrückt wurde hat die Variable den Wert '?', damit
 * man erkennen kann, wenn dann erstmals ein r, o, l oder u hereinkommt.
 */
volatile enum direction snake_direction = '?';
/**
 * Globale Variable, welche vom Interrupthandler über den Timer gesetzt wird.
 * Alle 1ms wird das Flag vom Interrupt des Timers gesetzt. Damit werden genaue
 * Zeitverzögerungen möglich.
 */
volatile int timer_irq_flag = 0;

location food;			///< Enthält die Position des Futters
int level;				///< Enthält den Level des Spiels

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
	static int x = 0;

	//pos.x = genrand_real2()*PLAYGROUND_X_MAX;
	//pos.y = genrand_real2()*PLAYGROUND_Y_MAX;

	pos.x = PLAYGROUND_X_MAX / 2 + 8 + ((x++)%2)*7;
	pos.y = PLAYGROUND_Y_MAX / 2;

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

/**
 * kurzbeschreibung.
 * lange beschreibung.
 * @param ms Wieviele Millisekunden gewartet werden soll
 * @return: nix
 */
void delay(int ms)
{

	start_timer();
	timer_irq_flag = 0;
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
    init_uart();
    init_counter();

    //CRandomMersenne RanGen(GUI_GetTime());
    //init_genrand(GUI_GetTime());

    while(1)
    {
    	disable_interrupts();
    	draw_field();
    	snake_direction = '?';
    	enable_interrupts();
    	/* Nach däm enable gheit er grad i timerinterrupt
    	 * u nachem Interrupt füehrt er us unerklärleche gründ disable interrupts
    	 * us u niermer weis werum...
    	 *
    	 *
    	 */

    	init_snake();

    	//start_timer();

    	// warten bis eine taste gedrückt wird, welche den initialen zustand von snake_direction ändert
		while(snake_direction == 63); //--> später wieder reinnehmen, wenn uart modul fertig.

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

			delay(130);
		}
		while(game_over != 1);

		game_over = 0;
    }

    return 0;
}
