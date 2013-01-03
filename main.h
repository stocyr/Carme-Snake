#ifndef MAIN_H
#define MAIN_H

/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : main.h                                         Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Header for main() (main.c)                                  */
/*                                                                           */
/*  Procedures : -                                                           */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 03.12.2012  File created                                    */
/*                                                                           */
/*  File       : main.h                                                      */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/
/**
 * \file main.h
 * Enth�lt Makros, Structs und gloale Variablen des Projekts.
 * Diese Datei enth�lt Enumeratoren, Strukturen, Makros und Variablen,
 * welche allgemein f�r das Projekt wichtig sind. Ausserdem enth�lt das
 * Interface zu den Assemblerroutinen.
 */

/* Makros*/
#define SNAKE_BUFFER		100		// max. Gr�sse f�r Schlang
#define INITIAL_SIZE		4

/* Enumerations */

// direction
enum direction {RIGHT = 'r', UP = 'u', LEFT = 'l', DOWN = 'd'};


enum result {NOTHING, FOOD, COLLISION};



/* Structs */

// location
typedef struct location {
	int x;
	int y;
} location;


/* global variables */
//extern volatile enum direction snake_direction;
extern volatile enum direction snake_direction;
extern volatile int timer_irq_flag;

extern location snake[SNAKE_BUFFER];
extern int head;
extern int tail;
extern int size;

extern location food;
extern location field_size;
extern int level;

/* function prototype for asm_soubrutines */
extern void init_counter();
extern void init_uart();
extern void start_timer();

extern void enable_interrupts();
extern void disable_interrupts();
extern void interrupt_handler();
extern int get_interrupt_state();

#endif
