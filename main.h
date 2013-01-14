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
 * Enthält Makros, Structs und gloale Variablen des Projekts.
 * Diese Datei enthält Enumeratoren, Strukturen, Makros und Variablen,
 * welche allgemein für das Projekt wichtig sind. Ausserdem enthält das
 * Interface zu den Assemblerroutinen.
 */

/* Makros*/
#define SNAKE_BUFFER		100		///< Maximal mögliche Länge der Schlage im Ringbuffer.
#define INITIAL_SIZE		4		///< Länge der Schlange bei Begin des Spiels.

/* Enumerations */
/**
 * Dieser Enumerator dient zur Aufschlüsselung der Zeichen von der UART0 Schnittstelle.
 * Er definiert dadurch auch gleich das Protokoll: Je nachdem, welches Zeichen von der
 * Schnittstelle ankommt, wird es als die jeweilige Richtung interpretiert.
 */
enum direction {RIGHT = 'r', UP = 'u', LEFT = 'l', DOWN = 'd'};
/**
 * Dieser Enumerator wird von der Funktion 'step_forward' gebraucht.
 * Sie signalisiert damit, was passiert ist, nachdem die Schlange einen Schritt vorwärts gemacht hat.
 * Entweder passierte nicht, die Schlange schnappte sich ein Futter oder sie kollidierte mit sich selbst oder der Wand.
 */
enum result {NOTHING, FOOD, COLLISION};


/* Structs */
/**
 * Diese Struktur wird benutzt, um Positionsdaten in einer Variable zu speichern.
 * Sie kann Pixelkoordinaten *oder* Rasterkoordinaten enthalten!
 */
typedef struct location {
	int x;
	int y;
} location;


/* global variables */
extern volatile enum direction snake_direction;
extern volatile int timer_irq_flag;

extern location food;
extern int startup_size;

/* function prototypes for asm_soubrutines */
extern void init_counter();		///< Initialisiert den Timer auf Hardwarestufe.
extern void init_uart();		///< Initialisiert die UART1 Schnittstelle auf Hardwarestufe.
extern void start_timer();		///< Startet den Timer auf Hardwarestufe.

extern void write_byte(char byte);	///< Schreibt ein Byte über die UART0 Schnittstelle.

extern void enable_interrupts();	///< Schaltet Interrupts auf Hardwarestufe ein.
extern void disable_interrupts();	///< Schaltet Interrupts auf Hardwarestufe aus.
extern void interrupt_handler();	///< Interrupt handler, der UART- und Timerinterrupt behandelt.
extern int get_interrupt_state();	///< Liefert zurück, ob Interrupts eingeschaltet sind oder nicht.

#endif
