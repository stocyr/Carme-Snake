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

/**
 * @mainpage Carme-Snake
 * Dieses Spiel ist eine Snake-Klon. <br>
 * Das Spiel wird auf dem LCD der CARME Kits angezeigt, die Bedienung erfolgt über die Pfeiltasten an einem PC. <br>
 * Das Interface PC <-> CARME erfolgt per RS232 auf den UART0 Port des CARME Kits. <br>
 *
 * <img src="../../DFD_v2.png">
 *
 * @author Cyril Stoller <br> Marcel Bärtschi <br> Peter Ambühl
 */

#include "main.h"
#include "graphics.h"
#include "snake_controller.h"
#include "GUI.h"
#include "carme.h"
#include "bitopera.h"
#include "marsenne.h"

/* macros */
#define START_DELAY 		160	///< Bestimmt die Startgeschwindigkeit der Schlange.
#define DELAY_REDUCTION		40	///< Bestimmt, wie schnell die Geschwindigkeit pro Level erhöht wird.
#define LEVEL_LENGTH		15	///< Länge der Schlange bis Level-Up

/* global variables */
/**
 * Globale Variable, welche vom Interrupthandler über UART0 aktualisiert wird.
 * Die Variable ist das Interface zur UART1 Schnittstelle. Sie enthält die Richtung,
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

/**
 * Enthält die Länge der Schlange während dem Aufstarten.
 * Die Schlange beginnt als einzelnes Glied und wächst dann in die Richtung,
 * in die der Spieler das erste Mal gedrückt hat. Diese wachsende Länge wird
 * mit dieser Variable gespeichert. Schlussendlich ist dann nur noch die variable
 * 'size' des Ringbuffers dafür zuständig.
 */
int startup_size = INITIAL_SIZE;

location food;		///< Enthält die Position des Futters
int level;			///< Enthält den Level des Spiels
int delay_time;		///< Definiert die Geschwindigkeit der Schlange
int game_over;		///< Flag um Spielende einzuleiten
int score;


/**
 * Zufallszahlgenerator.
 * Zufallszahlgenerator aus http://xkcd.com/221/:
 * @return Random number *chosen by fair dice roll.* <p>
 * *guaranteed to be random.*
 */
int randomize()
{
	// chosen by fair dice roll.
	// guaranteed to be random.
	// http://xkcd.com/221/
	return 4;
}


/**
 * Zufallspositionsgenerator.
 * Liefert innerhalb der Spielfeldgrösse eine zufällige Position zurück.
 * @return liefert eine zufällige Position zurück
 */
location randomize_location()
{
	location pos;
	pos.x = genrand_real2()*PLAYGROUND_X_MAX;
	pos.y = genrand_real2()*PLAYGROUND_Y_MAX;

	return pos;
}


/**
 * Zufallspositionsgenerator mit Überprüfung.
 * Liefert eine Zufällige Position innerhalb des Spielfeldes,
 * jedoch *nicht* auf der Schlange drauf.
 * @return liefert eine zufällige Position zurück
 */
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
 * Verzögerungsfunktion.
 * Verzögert den Ablauf um eine gewisse Anzahl Millisekunden (mit Timer-Interrupts).
 * @param ms Gibt an, wieviele Millisekunden gewartet werden soll
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


/**
 * Stellt einen gespeicherten Interruptzustand wieder her.
 * @param old_state gibt den Zustand an, der wiederhergestellt werden soll
 */
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


/**
 * Stellt den Initialzustand bei Spielbegin her.
 * Variablen werden zurückgesetz, Spielfeld neu gezeichnet.
 */
void init_game()
{
    delay_time = START_DELAY;
    level = 1;
    game_over = 0;
    score = 0;
}


/**
 * Stellt den Initialzustand bei Level-Up her.
 * Schlange wird zurückgesetzt, Spielfeld neu gezeichnet.
 */
void init_level()
{
    delay_time = START_DELAY - (level-1)*DELAY_REDUCTION;
    if(delay_time < 60)
	{
		delay_time = 60;
	}
    startup_size = INITIAL_SIZE;

    disable_interrupts();
	draw_field();
	enable_interrupts();

    init_snake();
}


/**
 * Hauptfunktion. Wird als erstes aufgerufen.
 * @return gibt 0 zurück
 */
int main()
{
	init_graphics();		//Function um Grafik Lib zu initialisieren, gibt evtl später mal Errorcode zurück...
    init_counter();

    /**
     * \todo UART Interrupts funktionieren noch nicht.
     * Als Workaround wird nun alle 1ms im Timer-Interrupt-Handler die UART1 Schnittstelle gepollt. <br>
     *
     * Struktogramm:
     * <img src="../../Spielablauf_Struktogramm.png">
     */
    init_uart();

    init_genrand(GUI_GetTime());

    while(1)
    {
    	init_game();
    	init_level();

    	// warten bis eine taste gedrückt wird, welche den initialen Zustand von snake_direction ändert
    	snake_direction = '?';
		while(snake_direction == '?');

		// jetzt food zeichnen
		food = randomize_food();
		draw_food(food);

		enable_interrupts();

		do
		{
			switch(step_forward(check_initial_state()))
			{
			case COLLISION:
				game_over = 1;
				disable_interrupts();
				//write_byte(score);

				FFLCR &= ~(1<<7);			// DLAB löschen für zugriff
				while (!(FFLSR & (1<<5)));	// Solange UART Busy
				FFTHR = score;

				enable_interrupts();
				break;

			case FOOD:
				score++;
				if(size >= 15)
				{
					// wenn Länge = 15: Level-Up
					score += 10;
					level++;
					init_level();
				}
				food = randomize_food();
				disable_interrupts();
				draw_food(food);
				enable_interrupts();
				break;

			case NOTHING:
				break;
			}

			delay(delay_time);
		}
		while(game_over != 1);
    }

    return 0;
}
