/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : uCfunctions.s                                  Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : contains all hardware based functions                       */
/*                                                                           */
/*  Procedures : interrupthandler, timerinit, UARTinit                       */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 03.12.2012  File created                                    */
/*                                                                           */
/*  File       : uCfunctions.s                                               */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/


.include "../startup/pxa270.s"

.global init_counter
.global interrupt_handler
.global enable_interrupts
.global disable_interrupts
.global get_interrupt_state

.extern timer_iqr_flag
.extern snake_direction

.text


init_counter:
STMFD 	sp!, {r0-r1, lr} 		@ save context
# CTR0s Interrupt initialisieren
# ICMR = ICMR | (1<<26); Interrupt freigeben
LDR r0,=ICMR
LDR r1,[r0]
ORR r1,r1,#(1<<26)		@ Bit 26 setzen
STR r1, [r0]
# ICLR = ICLR & ~(1<<26); IRQ auslösen
LDR r0,=ICLR
LDR r1,[r0]
BIC r1,r1,#(1<<26)
STR r1, [r0]
# IPR0 = IPR0 | 26; Timer Interrupt als Priorität 0 (höchste) festlegen
LDR r0,=IPR0
LDR r1,[r0]
AND r1,r1,#0xFFFFFFC0
ORR r1,r1,#26		@ 26 hineinschreiben
STR r1, [r0]
# OSMR0 = 3250000; Match Register so setzen, dass sich 1ms Tackt ergibt
LDR r1,=3250000
LDR r0,=OSMR0
STR r1,[r0]
# OIER = OIER | 1; Interrupt für OSMR0 freigeben
LDR r0,=OIER
LDR r1,[r0]
ORR r1,r1,#1
STR r1, [r0]
# CKEN = CKEN | (1<<9); OsTimer Unit Clock enable
LDR r0,=CKEN
LDR r1,[r0]
ORR r1,r1,#(1<<9)		@ Bit 9 setzen
STR r1, [r0]

LDMFD 	sp!, {r0-r1, pc}^ 		@ restore context, return


init_uart:



interrupt_handler:
#ICHP enthält die ID der interruptauslösenden Quelle

STMFD 	sp!, {r0-r2, lr} 		@ save context

# kommt der Interrupt vom Timer?
LDR r0,=ICHP
LDR r1,[r0]
MOV r2,#13						@ Timer Interrupt ID = ??????? -> 13 ersetzen
BNE r0,r1,no_timer_irq			@ step over if NO timer irq was thrown

# OSCR0 auf 0 setzen wenn Interrupt ausgelöst wurde
LDR r0,=OSCR0
MOV r1,#0
STR r1,[r0]

# Timer flag (wird in C-Funktionen genutzt) setzen
LDR r0,=timer_iqr_flag
MOV r1,#1
STR r1,[r0]

B

no_timer_irq:
# kommt der interupt von UART?
MOV r1,#11						@ Timer Interrupt ID = ??????? -> 11 ersetzen
BNE r0,r1, no_uart_interrupt

# UART Verarbeitung: je nach erhaltenem Zeichen wird die Variable snake_direction anders gesetzt.
LDR r0,=UART_ZEICHEN_REGISTER
LDR r1,[r0]

LDR r0,=snake_direction

STR r1,[r0]

no_uart_interrupt:
# hier kommen evtl. weitere interrupt ID's

# END
end_interrupt_handler:

# OSSR löschen um Interrupt zurückzusetzen
LDR r0,=OSSR
MOV r1,#0
STR r1,[r0]

# restore context, return
LDMFD 	sp!, {r0-r1, pc}^


enable_interrupts:


disable_interrupts:


get_interrupt_state:

