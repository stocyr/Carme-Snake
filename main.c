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
#include "GUI.h"
#include "carme.h"
#include "bitopera.h"
#include "interrupt_ivo.h"
#include "interrupt.h"

/* global variables */

volatile enum direction snake_direction;
volatile int timer_irq_flag = 0;

location food;
location field_size;
int level;


void init_game(enum direction init_dir)
{

}

location randomize_food()
{
	location food = {4,4};
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
	location food;
    location field_size;
    int level;
    int i = 0;

	init_graphics();		//Function um Grafik Lib zu initialisieren, gibt evtl später mal Errorcode zurück...
    init_counter();
    enable_interrupts();
    start_timer();




    draw_field();
    field_size.x = 100;
    field_size.y = 200;


    for(i=0;i<40;i++){
    	delay(100);
    	field_size.x += 2;
    draw_snake_head(field_size);
    }

    GUI_DispStringAt("begin: ", 0, 0);
    GUI_DispCharAt(timer_irq_flag+'0', 7*8, 0*16);
    while(!timer_irq_flag);
    GUI_DispStringAt("flag: ", 0, 1);
    GUI_DispCharAt(timer_irq_flag+'0', 6*8, 1*16);
    timer_irq_flag = 0;

    while(1); //für immer warten
    /////////////////////////////////////////

    return 0;
}
