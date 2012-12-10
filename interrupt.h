/*
 * Interrupt.h
 *
 *  Created on: 25.05.2012
 *      Author: Marcel
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define SET_IRQ_HANDLER(Handler) \
   *((unsigned long *)0xA0000018) = 0xEA000000 | \
  (( ((long *)Handler) - ((long *)0xA0000018) - 2) & 0x00FFFFFF)

extern int x;
//void timer_interrupt_handler(void) __attribute__((interrupt("IRQ")));
void init_interrupt(void);
#endif /* INTERRUPT_H_ */
