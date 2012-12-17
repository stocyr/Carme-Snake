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
//#include "interrupt_ivo.h"
//#include "interrupt.h"
#include "marsenne.h"

/* global variables */

volatile enum direction snake_direction = 'r';
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
    //init_counter();
    //init_uart();








	// UART initialisieren:
	//
	// 8 bit Daten
	// 1 Stop bit
	// no parity
	// 9600 baud
	//

	// Clock einschalten
	CKEN |= (1<<6);	// uart clock einschalten

	// UART selbst ausschalten
	FFLCR &= ~(1<<7);	// DLAB löschen
	FFIER &= ~(1<<6);	// UUE ausschalten

	// Alternate function register
	GAFR1_L |= (1<<4);	// Pin 34: RxD
	GAFR1_L &= ~(1<<5);	// Pin 34: RxD
	GAFR1_L |= (1<<15);	// Pin 39: TxD
	GAFR1_L &= ~(1<<14);	// Pin 39: TxD

	// Data Direction:
	GPDR1 &= ~(1<<2);	// Pin 34 als RxD -> Input
	GPDR1 |= (1<<7);	// Pin 39 als TxD -> Output

	// FIFO ausschalten
	FFFCR = 0;

	// Modem control ausschalten
	FFMCR = 0;

	// Infrarot ausschalten
	FFISR = 0;

	// Auto Baudrate ausschalten
	FFABR = 0;

	// BAUD rate
	FFLCR |= (1<<7);	// DLAB setzen
	FFDLL = 96;			// Bausrate: 9600
	FFDLH = 0;

	// Line control konfigurieren
	FFLCR = 0;			// 1 stop bit, kein parity bit
	FFLCR |= (1<<0);	// 8bit übertragung
	FFLCR |= (1<<1);	// 8bit übertragung

	// UART selbst einschalten
	FFLCR &= ~(1<<7);	// DLAB löschen
	FFIER = (1<<6);	// UUE einschalten


	IPR1 = 26;
	bitset(IPR1, 31);
	IPR0 = 22;
	bitset(IPR0, 31);






    //CRandomMersenne RanGen(GUI_GetTime());
    //init_genrand(GUI_GetTime());

    while(1)
    {
    	disable_interrupts();
    	draw_field();
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

			//delay(130);
		}
		while(game_over != 1);

		game_over = 0;
    }

    return 0;
}
