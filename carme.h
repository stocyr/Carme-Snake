/*
 * carme.h
 *
 *  Created on: 04.05.2012
 *      Author: cyril
 */

#ifndef CARME_H_
#define CARME_H_

#define vulp (volatile unsigned long *)
#define cvp(x) (vulp(x))
#define uvp(x) (*cvp(x))


#define GPLR3 uvp(0x40100000)

// UART
#define FFRBR uvp(0x40100000)
#define FFTHR uvp(0x40100000)
#define FFIER uvp(0x40100004)
#define FFDLL uvp(0x40100000)
#define FFDLH uvp(0x40100004)
#define FFFCR uvp(0x40100008)
#define FFLCR uvp(0x4010000C)
#define FFMCR uvp(0x40100010)
#define FFLSR uvp(0x40100014)
#define FFISR uvp(0x40100020)
#define FFABR uvp(0x40100028)

#define GPDR1 uvp(0x40E00010)
#define GAFR1_L uvp(0x40E0005C)
#define CKEN uvp(0x41300004)
 // Interröpt
#define ICMR uvp(0x40D00004)
#define ICLR uvp(0x40D00008)
#define IPR0 uvp(0x40D0001C)
#define ICHP uvp(0x40D00018)

// Täimer
#define OSMR0 uvp(0x40A00000)
#define OSCR0 uvp(0x40A00010)
#define OIER  uvp(0x40A0001C)
#define OSSR  uvp(0x40A00014)


#define TASTER GPLR3
#define LEDS uvp(0x0C003000)

#define T0 (1<<3)
#define T1 (1<<5)
#define T2 (1<<6)
#define T3 (1<<7)

#define L0 (1<<0)
#define L1 (1<<1)
#define L2 (1<<2)
#define L3 (1<<3)

#endif /* CARME_H_ */
