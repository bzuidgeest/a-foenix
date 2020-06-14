#ifndef TIMER_H
#define TIMER_H

// TIMER0
#define TIMER0_CTRL_REG		(*(unsigned char *)0x000160)	// (Write - Control, Read Status)
#define TIMER0_CHARGE_L		(*(volatile unsigned char *)0x000161)	// Use if you want to Precharge and countdown
#define TIMER0_CHARGE_M		(*(volatile unsigned char *)0x000162)    
#define TIMER0_CHARGE_H		(*(volatile unsigned char *)0x000163) 
// Compare Block
#define TIMER0_CMP_REG		(*(volatile unsigned char *)0x000164) 
#define TIMER0_CMP_L		(*(volatile unsigned char *)0x000165)	// Load this Value for Countup
#define TIMER0_CMP_M		(*(volatile unsigned char *)0x000166) 
#define TIMER0_CMP_H		(*(volatile unsigned char *)0x000167) 

// TIMER1
#define TIMER1_CTRL_REG		(*(unsigned char *)0x000168) 
#define TIMER1_CHARGE_L		(*(volatile unsigned char *)0x000169)	// Use if you want to Precharge and countdown
#define TIMER1_CHARGE_M		(*(volatile unsigned char *)0x00016A) 
#define TIMER1_CHARGE_H		(*(volatile unsigned char *)0x00016B) 
// Compare Block
#define TIMER1_CMP_REG		(*(volatile unsigned char *)0x00016C) 
#define TIMER1_CMP_L		(*(volatile unsigned char *)0x00016D) 
#define TIMER1_CMP_M		(*(volatile unsigned char *)0x00016E) 
#define TIMER1_CMP_H		(*(volatile unsigned char *)0x00016F) 

// Control Register Definitions
#define TMR_EN				0x01
#define TMR_SCLR			0x02
#define TMR_SLOAD			0x04	// Use SLOAD is
#define TMR_UPDWN			0x08	// 1 = Up, 0 = Down

// Compare register
#define TMR_CMP_RECLR		0x01	// set to one for it to cycle when Counting up
#define TMR_CMP_RELOAD		0x02	// Set to one for it to reload when Counting Down

#define TMR_0_1_Clock 14318000

#endif /* TIMER_H */

