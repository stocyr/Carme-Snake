/*******************************************************************************

    Titel:      Makros für Bitoperationen an Registern

    File:       bitOpera.h
    Funktionen: bitset(), bitclr(), bittgl(),
                bitpats(), bitpatc(), bitpatt(),
                bittst(),
                quers(), odd(),
                bar()

    Hardware:   -
    Verfasser:  Cyril Stoller
    Datum:      27.03.2008
    Version:    1.5

*******************************************************************************/
/**
 * \file bitopera.h
 * Stellt Makros für das Bitweise Manipulieren von Registern zur Verfügung
 *
 */
#ifndef _BITOPERA_
#define _BITOPERA_

#define bitset(Reg,BitNr) Reg |= (1<<BitNr)                   //1. bit = bit0!
#define bitclr(Reg,BitNr) Reg &= (~(1<<BitNr))                //1. bit = bit0!
#define bittgl(Reg,BitNr) Reg ^= (1<<BitNr)                   //1. bit = bit0!

#define bitpats(Reg,Pattern) Reg |= Pattern
#define bitpatc(Reg,Pattern) Reg &= (~Pattern)
#define bitpatt(Reg,Pattern) Reg ^= Pattern

#define bittst(Reg,BitNr) (Reg & (1<<BitNr))                  //1. bit = bit0!

// wird sehr selten gebraucht -> nur definieren wenn nötig:
/*
unsigned char quersumme(unsigned char Reg)
{
	unsigned char x;
	unsigned char cnt = 0;
	for(x = 0; x < 8; x++)
		if(bitTst(Reg, x)) cnt++;       //wenn das aktuelle nicht 0 ist, cnt++

	return cnt;
}
*/

#define odd(Reg) Quersumme(Reg) % 2

#define bar(Reg,max,val) Reg = 0xFF>>(8-val/(max/8))

#endif // #ifndef _BITOPERA_
