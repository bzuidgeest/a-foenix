///
/// Register address and constant definitions for the keyboard interface
///

// Register addresses
#define KBD_STATUS		(*(volatile unsigned char *)0xAF1064)	// Read status
#define KBD_CMD_BUF		(*(volatile unsigned char *)0xAF1064)	// Write command
#define KBD_OUT_BUF 	(*(volatile unsigned char *)0xAF1060)	// Write value (for command)
#define KBD_IN_BUF		(*(volatile unsigned char *)0xAF1060)	// Read input
//#define KBD_DATA_BUF	(*(volatile unsigned char *)0xAF1060)

#define KBD_PORT_A		(*(volatile unsigned char *)0xAF1060)
#define KBD_PORT_B		(*(volatile unsigned char *)0xAF1061)

// Status
#define OUT_BUF_FULL    0x01 	// 1 on output buffer full
#define INPT_BUF_FULL	0x02	// 1 on input buffer full
#define SYS_FLAG		0x04	// 1 on succesfull self test of keyboard.
#define CMD_DATA		0x08	// 1 if last write was to command buffer
#define KEYBD_INH       0x10	// 1 if keyboard lock (inhibit) is on.
#define TRANS_TMOUT	    0x20	// 1 if output buffer is full. May indicate no keyboard.
#define RCV_TMOUT		0x40	// 1 if input from keyboard timed out.
#define PARITY_ERROR	0x80	// Parity error on last byte.

// Keyboard Commands
// #define KB_MENU			0xF1
// #define KB_ENABLE		0xF4
// #define KB_MAKEBREAK    0xF7
// #define KB_ECHO			0xFE
// #define KB_RESET		0xFF
// #define KB_LED_CMD		0xED
#define KBD_ENA			0xAE
#define KBD_DIS			0xAD
#define KBD_SELFTEST	0xAA
#define KBD_INTFTEST	0xAB


// Keyboard responses
// #define KB_OK			0xAA
#define KB_ACK			0xFA
// #define KB_OVERRUN		0xFF
#define KB_RESEND		0xFE
// #define KB_BREAK		0xF0
// #define KB_FA			0x10
// #define KB_FE			0x20
// #define KB_PR_LED		0x40

// Lock Key Flags
#define KB_SCROLL_LOCK 	0x01
#define KB_NUM_LOCK		0x02
#define KB_CAPS_LOCK	0x04

// Special key flags
//KB_CTRL_C 0x80             / CTRL-C was pressed
//KB_CREDITS 0x60            / Credits key was pressed
