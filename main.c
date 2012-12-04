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

/* global variables */
volatile enum direction snake_direction;



location food;
location field_size;
int level;

int main()
{
    init_graphics();		//Function um Grafik Lib zu initialisieren, gibt evtl später mal Errorcode zurück...

	location food;
    location field_size;
    int level;

    ////////////////////////////////////////test
    draw_field();
    field_size.x = 100;
    field_size.y = 200;
    int i = 0;
    draw_snake_head(field_size);
    for(i=0;i<40;i++){
    field_size.x += 2;
    draw_snake_head(field_size);
    }

    while(1); //für immer warten
    /////////////////////////////////////////


    return 0;
}

void init_game(enum direction init_dir)
{

}

location randomize_food()
{

}

void delay(int ms)
{

}

