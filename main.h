#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

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
/* Makkros*/
#define SNAKE_BUFFER	100		// max. Grösse für Schlange

/* Enumerations */

// direction
enum direction {RIGHT, UP, LEFT, DOWN};


enum result {NOTHING, FOOD, COLLISION};



/* Structs */

// location
typedef struct {
	int x;
	int y;
} location;


/* global variables */
//extern volatile enum direction snake_direction;
volatile enum direction snake_direction;
volatile int timer_iqr_flag;

extern int snake[SNAKE_BUFFER];
extern int head;
extern int tail;
extern int size;

extern location food;
extern location field_size;
extern int level;

/* function prototype for asm_soubrutines */
extern init_counter();
extern start_timer();

extern enable_interrupts();
extern disable_interrupts();
extern int get_interrupt_state();

#endif
