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


init_counter:
# CTR0 Interrupt initialisieren
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


init_uart:



interrupt_handler:
#ICHP enthält die ID der interruptauslösenden Quelle
# OSCR0 auf 0 setzen wenn Interrupt ausgelöst wurde
# OSSR löschen um Interrupt zurückzusetzen


