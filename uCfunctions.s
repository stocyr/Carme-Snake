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
/*  Author     : M.Bärtschi                                                  */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*  History    : 05.12.2012  File created                                    */
/*                                                                           */
/*  File       : uCfunctions.s                                               */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/


.include "../startup/pxa270.s"

.global init_counter
.global init_uart
.global interrupt_handler
.global write_byte
.global enable_interrupts
.global disable_interrupts
.global get_interrupt_state
.global start_timer

#.data

.extern timer_irq_flag
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
# IPR0 = IPR0 | 26; Timer Interrupt als Priorität 1 (2. höchste) festlegen
LDR r0,=IPR1
LDR r1,[r0]

MOV r1,#26		@ 26 hineinschreiben
ORR r1,r1,#(1<<31)
STR r1, [r0]


# OSMR0 = 3250; Match Register so setzen, dass sich 1ms Tackt ergibt
LDR r1,=3250
LDR r0,=OSMR0
STR r1,[r0]

# OSCR auf 0 setzen wenn Interrupt ausgelöst wurde
LDR r0,=OSCR
MOV r1,#0
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




# uart ralphrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrralph
#
#
#
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

init_uart:
@Clock = Clock | (1 << 6);

LDR r0, =CKEN
LDR r1, [r0]
ORR r1, #(1<<6)
STR r1, [r0]

@LineControl &= ~(1<<7); /*DABL auf 0*/
LDR r0, =FFLCR
LDR r1, [r0]
BIC r1, #(1<<7)
STR r1, [r0]

@InerruptEnable &= ~(1 << 6); /*UUE Bit auf 0*/
LDR r0, =FFIER
LDR r1, [r0]
BIC r1, #(1<<6)
STR r1, [r0]

@LineControl = 0; /*LineControl alles auf 0*/

@LineControl |= (1 << 7); /*DABL auf 1*/

LDR r0, =FFLCR
MOV r1, #0x0
ORR r1, #(1<<7)
STR r1, [r0]

@DivisorLatchLow = 96 & 0xFF; /*Divisor auf 0096 setzen*/

LDR r0, =FFDLL
LDR r1, [r0]
MOV r1, #(96 & 0xFF)
STR r1, [r0]

@DivisorLatchHigh = (96 >> 8) & 0xFF;/*Divisor auf 0096, also hier 00*/

LDR r0, =FFDLH
LDR r1, [r0]
MOV r1, #(96>>8)
AND r1, #0xFF
STR r1, [r0]

@LineControl = 0;
LDR r0, =FFLCR
MOV r1, #0x0
STR r1, [r0]

@FIFOControl &= ~(1<<0); /*FIFO ausschalten (bit 1 auf 0), auch FIFOControl = 0; mˆglich*/

LDR r0, =FFFCR
LDR r1, [r0]
BIC r1, #(1<<0)
STR r1, [r0]

@LineControl |= (1<<0);

/*Word Length Select auf 8bit (0b11)*/

@LineControl |= (1<<1);

/*Word Length Select auf 8bit (0b11)*/

LDR r0, =FFLCR
LDR r1, [r0]
ORR r1, #(1<<0)
ORR r1, #(1<<1)
STR r1, [r0]

@ModemControl = 0;

/*Modem Steuerleitung ausschalten*/

LDR r0, =FFMCR
MOV r1, #0x0
STR r1, [r0]

@InfraredSelection = 0; /*Infrarot ausschalten*/

LDR r0, =FFISR
STR r1, [r0]

@AutoBaudrate |= (1<<0);

/*Auto Baudrate ausschalten*/

LDR r0, =FFABR
LDR r1, [r0]
ORR r1, #(1<<0)
STR r1, [r0]

@GpioPinDirectionRegister &= ~(1<<2); /*als input definiert*/

@GpioPinDirectionRegister |= (1<<7);

/*als output definiert*/

LDR r0, =GPDR1
LDR r1, [r0]
BIC r1, #(1<<2)
ORR r1, #(1<<7)
STR r1, [r0]

@GpioAlternateFunctionSelect |= (1<<4);

@GpioAlternateFunctionSelect |= (1<<15);

@GpioAlternateFunctionSelect &= ~(1<<14);

LDR r0, =GAFR1_L
LDR r1, [r0]
ORR r1, #(1<<4)
ORR r1, #(1<<15)
BIC r1, #(1<<14)
STR r1, [r0]

@InterruptEnable |= (1 << 6); /*UUE Bit auf 1*/

LDR r0, =FFIER
LDR r1, [r0]
ORR r1, #(1<<6)
STR r1, [r0]
MOV pc,lr



/*****************************************************************************/

/*  Ende        : SerielleSchnittstelleInit

                        */

/*****************************************************************************/





init_uart_original:
STMFD 	sp!, {r0-r3, lr} 		@ save context

# UART initialisieren:
# 8 bit Daten
# 1 Stop bit
# no parity
# 9600 baud
# Clock einschalten

# GPIO<34> als RxD wählen -> Alternate Function 1 -> Bit 5,4   = 01
# GPIO<39> als TxD wählen -> Alternate Function 2 -> Bit 15,14 = 10
LDR r1,=GAFR1_L
LDR r2,[r1]
LDR r3,=0x8010		@ wenns nicht geht zuerst noch bit 5 und 14 löschen, sollten aber 0 sein vom Reset
ORR r2,r2,r3
BIC r2,r2,#(1<<5)
BIC r2,r2,#(1<<14)
STR r2,[r1]

# Data Direction:
# GPDR1 &= ~(1<<2);	// Pin 34 als RxD -> Input
LDR r1,=GPDR1
LDR r2,[r1]
BIC r2,r2,#(1<<2)

# GPDR1 |= (1<<7);	// Pin 39 als TxD -> Output
ORR r2,r2,#(1<<7)
STR r2,[r1]


# CKEN |= (1<<6);	// uart clock einschalten
LDR r0,=CKEN
LDR r1,[r0]
ORR	r1,r1,#(1<<6)
STR r1,[r0]

# UART Interrupt als Priorität 0 setzen
LDR r0,=IPR0
MOV r2,#22
ORR r2,r2,#(1<<31)
STR r2,[r0]

# UART selbst ausschalten
# FFLCR &= ~(1<<7);	// DLAB löschen
LDR r0,=FFLCR
LDR r1,[r0]
BIC r1,r1,#(1<<7)
STR r1,[r0]
# FFIER &= ~(1<<6);	// UUE ausschalten
LDR r1,=FFIER
LDR r2,[r1]
BIC r2,r2,#(1<<6)
STR r2,[r1]

# FIFO ausschalten
# FFFCR = 0;
LDR r1,=FFFCR
MOV r2,#0
STR r2,[r1]
# Modem control ausschalten
# FFMCR = 0;
LDR r1,=FFMCR
MOV r2,#0
STR r2,[r1]
# Infrarot ausschalten
# FFISR = 0;
LDR r1,=FFISR
MOV r2,#0
STR r2,[r1]
# Auto Baudrate ausschalten
# FFABR = 0;
LDR r1,=FFABR
MOV r2,#0
STR r2,[r1]
# BAUD rate
# FFLCR |= (1<<7);	// DLAB setzen
LDR r0,=FFLCR
LDR r1,[r0]
ORR r1,r1,#(1<<7)
STR r1,[r0]
# FFDLL = 96;			// Bausrate: 9600
LDR r1,=FFDLL
MOV r2,#96
STR r2,[r1]
# FFDLH = 0;
LDR r1,=FFDLH
MOV r2,#0
STR r2,[r1]
# Line control konfigurieren
# FFLCR = 0;			// 1 stop bit, kein parity bit
MOV r1,#0
# FFLCR |= (1<<0);	// 8bit übertragung
ORR r1,r1,#(1<<0)
# FFLCR |= (1<<1);	// 8bit übertragung
ORR r1,r1,#(1<<1)

# UART selbst einschalten
# FFLCR &= ~(1<<7);	// DLAB löschen
BIC r1,r1,#(1<<7)
STR r1,[r0]
# FFIER = (1<<6);	// UUE einschalten, Interrupts von RX enablen (bit RAVIE)
LDR r1,=FFIER
LDR r2,[r1]
ORR r2,r2,#(1<<6)
ORR r2,r2,#(1<<0)
STR r2,[r1]

LDMFD 	sp!, {r0-r3, pc}^ 		@ restore context, return



interrupt_handler:
#ICHP enthält die ID der interruptauslösenden Quelle
SUB lr, lr, #4 						@ adjust link register for return address
STMFD 	sp!, {r0-r1, r12, lr} 		@ save context


# kommt der interupt von UART?
LDR r0,=ICHP
LDR r1,[r0]
MOV r1,r1, LSR #16
AND r1, r1, #63
CMP r1,#22					@ UART Interrupt ID = |FFUART Id = 22 | BTUART ID = 23 | STUART ID = 24 |
# BNE no_uart_interrupt <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< einkomentieren wenn Interrupt, nicht pollen
# UART Verarbeitung: je nach erhaltenem Zeichen wird die Variable snake_direction anders gesetzt.

# FFLCR &= ~(1<<7);	// DLAB löschen
LDR r0,=FFLCR
LDR r1,[r0]
BIC r1,r1,#(1<<7)
STR r1,[r0]

# Abfragen ob Daten bereit -> FFLSR Bit 0 = 1?
LDR r0,=FFLSR
LDR r1,[r0]
TST r1,#(1<<0)
# BNE data_not_ready Weis nicht ob notwendig <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< einkomentieren wenn Interrupt, nicht pollen
# Daten bereit -> Richtung einlesen
LDR r0,=FFRBR
LDR r1,[r0]

# Richtungsvariable laden
LDR r0,=snake_direction
# Richtung prüfen
CMP r1,#'r'
BEQ case_right
CMP r1,#'l'
BEQ case_left
CMP r1,#'u'
BEQ case_up
CMP r1,#'d'
BEQ case_down
# Keine Übereinstimmung -> default, nichts machen
B end_switch

case_right:
MOV r1,#'r'
STR r1,[r0]
b end_switch

case_left:
MOV r1,#'l'
STR r1,[r0]
b end_switch

case_up:
MOV r1,#'u'
STR r1,[r0]
b end_switch

case_down:
MOV r1,#'d'
STR r1,[r0]
b end_switch

# Variable speichern
end_switch:

data_not_ready:

# B end_interrupt_handler <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< einkomentieren wenn Interrupt, nicht pollen

no_uart_interrupt:
# kommt der Interrupt vom Timer?
LDR r0,=ICHP
LDR r1,[r0]
MOV r1,r1, LSR #16
AND r1, r1, #63
CMP r1,#26				@ Timer Interrupt ID = 26
BNE no_timer_irq				@ step over if NO timer irq was thrown

# OSCR auf 0 setzen wenn Interrupt ausgelöst wurde
LDR r0,=OSCR
MOV r1,#0
STR r1,[r0]

# Timer flag (wird in C-Funktionen genutzt) setzen
LDR r0,=timer_irq_flag
MOV r1,#1
STR r1,[r0]

B end_interrupt_handler

no_timer_irq:
# hier kommen evtl. weitere interrupt ID's

# END
end_interrupt_handler:

# OSSR löschen um Interrupt zurückzusetzen
LDR r0,=OSSR
LDR r1,=0xFFF
STR r1,[r0]

# restore context, return
LDMFD 	sp!, {r0-r1, r12, pc}^



write_byte:
STMFD 	sp!, {r0-r2, lr} 		@ save context
# Parameter in r0 sichern
MOV r0,r2

# FFLCR &= ~(1<<7);	// DLAB löschen
LDR r0,=FFLCR
LDR r1,[r0]
BIC r1,r1,#(1<<7)
STR r1,[r0]

# warten bis Ausgangsbuffer leer
write_byte_while:
LDR r0,=FFLSR
LDR r1,[r0]
TST r1,#(1<<5)
# wenn Bit gesetzt: busy
BEQ write_byte_while

LDR r0,=FFTHR
LDR r2,[r0]

LDMFD 	sp!, {r0-r2, pc}^ 		@ restore context, return


enable_interrupts:
STMFD 	sp!, {r0-r1, lr} 		@ save context
# OSCR auf 0 setzen
LDR r0,=OSCR
MOV r1,#0
STR r1,[r0]

# OSSR löschen um Interrupt zurückzusetzen
LDR r0,=OSSR
LDR r1,=0xFFF
STR r1,[r0]

# CPSR = CPSR & ~(1<<7)
MRS r0,cpsr					@ mängisch verreiset er da eifach :(
BIC r0,r0,#(1<<7)
MSR cpsr_c,r0				@ macht er nich, wieso???????????????????????????????????????
LDMFD 	sp!, {r0-r1, pc}^ 		@ restore context, return

disable_interrupts:
STMFD 	sp!, {r0, lr} 		@ save context
# CPSR = CPSR | (1<<7)
MRS r0,cpsr
ORR r0,r0,#(1<<7)
MSR cpsr_c,r0
LDMFD 	sp!, {r0, pc}^ 		@ restore context, return


get_interrupt_state:
# Gibt 0 zurück, wenn Interrupts zugelassen sind, sonst einen Wert ungleich 0
STMFD 	sp!, {r0-r1, lr} 		@ save context
MRS r1,cpsr
TST r1,#(1<<7)
BNE	interrupt_active
MOV r0,#1
B end_get_interrupt_state

interrupt_active:
MOV r0,#0
end_get_interrupt_state:
LDMFD 	sp!,{r0-r1, pc}^ 		@ restore context, return

start_timer:
STMFD 	sp!, {r0-r1, lr} 		@ save context
# OSCR auf 0 setzen wenn Interrupt ausgelöst wurde
LDR r0,=OSCR
MOV r1,#0
STR r1,[r0]

LDMFD 	sp!, {r0-r1, pc}^ 		@ restore context, return

