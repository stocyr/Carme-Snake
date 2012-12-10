/**
 ***************************************************************************
 * \file    BSP_STARTUP.c
 ***************************************************************************
 * \brief   Startupcode for the CARME-Board
 *
 * \version	4.0.0.0
 * \date	22.09.06
 * \author	sce2
 *
 *
 ***************************************************************************
 *
 * \svn
 * \li	 \$LastChangedDate: 2008-06-26 13:33:25 +0200 (Do, 26 Jun 2008) $
 * \li	 \$LastChangedRevision: 1783 $
 * \li	 \$LastChangedBy: sce2 $
 * \history
 * \li 22.09.06, V1.0.0.0, sce2, created
 * \li 15.05.07, V4.0.0.0, sce2, problem with FIQ handler fixed timer 7-11,
 * Keyboard and UCB1400 handler added
 * \li 27.04.10, V4.0.0.0, osi1, removed all dependencies from other files
 ***************************************************************************
 */
#include <stdio.h>

#define vulp (volatile unsigned long *)
#define cvp(x) (vulp(x))
#define uvp(x) (*cvp(x))

#define OVI_CCCR      uvp(0x41300000)  /* Core Clock Configuration Register */
#define OVI_CCSR      uvp(0x4130000C)  /* Core Clock Status Register */
#define OVI_GAFR0_L   uvp(0x40E00054)  /* GPIO Alternate Function Select Register GPIO<15:0> */
#define OVI_GAFR0_U   uvp(0x40E00058)  /* GPIO Alternate Function Select Register GPIO<31:16> */
#define OVI_GAFR1_U	  uvp(0x40E00060)  /* GPIO Alternate Function Select Register GPIO<63:48> */
#define OVI_GAFR2_L   uvp(0x40E00064)  /* GPIO Alternate Function Select Register GPIO<79:64> */
#define OVI_GAFR2_U   uvp(0x40E00068)  /* GPIO Alternate Function Select Register GPIO 80 */
#define OVI_GPDR0     uvp(0x40E0000C)  /* GPIO Pin Direction Register GPIO<31:0> */
#define OVI_GPDR1	  uvp(0x40E00010)  /* GPIO Pin Direction Register GPIO<63:32> */
#define OVI_GPDR2     uvp(0x40E00014)  /* GPIO Pin Direction Register GPIO<80:64> */
#define OVI_GPSR0     uvp(0x40E00018)  /* GPIO Pin Output Set Register GPIO<31:0> */
#define OVI_GPSR2     uvp(0x40E00020)  /* GPIO Pin Output Set Register GPIO<80:64> */
#define OVI_MSC0      uvp(0x48000008)  /* Static Memory Control Register 0 */
#define OVI_MSC1      uvp(0x4800000C)  /* Static Memory Control Register 1 */
#define OVI_PSSR      uvp(0x40F00004)  /* Power Manager Sleep Status Register */
#define OVI_PSSR_RDH  (1 << 5)   /* Read Disable Hold */

/*
*********************************************************************************************************
*  function prototypes
**********************************************************************************************************
*/

// external function declaration

/**
 *****************************************************************************
 * \fn unsigned int 	pxa27x_get_freq(void)
 *****************************************************************************
 *\brief
 * TReturn the current lclk requency in units of 1kHz. This code was copied from
 * uboot.
 *****************************************************************************
 * \return      Core frequency
 *****************************************************************************
 *  \author     E. Stucki
 *
 *  \date       22.12.2006
 *
 * \todo		adaption to Code conventions
 *
 * \bug        No bugs known
 *****************************************************************************
 */
unsigned int pxa27x_get_freq(void)
{
	unsigned int freq, n,l, ccsr;

	if (OVI_CCCR & (1 << 31))
		return 13000;
	ccsr =OVI_CCSR;
	l= ccsr & 0x0000001F;	/*	Get L	*/
	n= (ccsr & 0x00000780)>>7;	/*	Get 2N	*/
	if( n <2 )	n=2;
	freq = (13 * l * n * 1000 )>>1;	/*	in kHz*/
	return freq;
}

/**
 *****************************************************************************
 * \fn BSP_STARTUP_init()
 *****************************************************************************
 *\brief
 * startup initialization of the Board. This function is called
 * 				  befor the main function.
 *****************************************************************************
 * \return      	none
 *****************************************************************************
 *  \author     E. Stucki
 *
 *  \date       10.10.2006
 *
 *****************************************************************************
 */
void BSP_STARTUP_init() {

	OVI_MSC0 &= ~0xffff0000;	// clear all flags for CS1 (CAN controller)
	OVI_MSC0 |= 0x7ff40000; 	// VLIO mode, 32 bit

	OVI_MSC1 &= ~0xffff0000;	// clear all flags for CS3 (CPLD controller)
	OVI_MSC1 |= 0x7ff40000;		// VLIO mode, 32 bit

	// initialize nCS<1,2,3,4> signals (for flash memory)
	OVI_GPSR0 	|= 0x00008000;	// nCS<1>
	OVI_GPDR0 	|= 0x00008000;	// nCS<1>
	OVI_GPSR2 	|= 0x0001c000;	// nCS<2,3,4>
	OVI_GPDR2 	|= 0x0001c000;	// nCS<2,3,4>

	OVI_GAFR0_L &= ~0xc0000000;	// nCS<1>
	OVI_GAFR2_L &= ~0xf0000000;	// nCS<2,3>
	OVI_GAFR2_U &= ~0x00000003;	// nCS<4>

	OVI_GAFR0_L |= 0x80000000;	// nCS<1>
	OVI_GAFR2_L |= 0xa0000000;	// nCS<2,3>
	OVI_GAFR2_U |= 0x00000002;	// nCS<4>

	// RDY (GPIO18)
	OVI_GPDR0 &= ~(1<<18);            // RDY (GPIO18) as input
	OVI_GAFR0_U &= ~(0x00000030);
	OVI_GAFR0_U |= 0x00000010;        // alternate function 1(RDY)

    // nPWE (GPIO49)
	OVI_GPDR1 |= (1<<17);			// nPWE (GPIO49) as output
	OVI_GAFR1_U &= ~(0x0000000c);
	OVI_GAFR1_U |= 0x00000008;		// alternate function 2(nPWE)

	OVI_PSSR |= OVI_PSSR_RDH;				// clears the Read Disable Hold bit

	// switch of linebuffering for stdout
	setvbuf(stdout, NULL, _IONBF, 0);
	// switch of linebuffering for stdin
	setvbuf(stdin, NULL, _IONBF, 0);
	// switch of linebuffering for stderr
	setvbuf(stderr, NULL, _IONBF, 0);

}
