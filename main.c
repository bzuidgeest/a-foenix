#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include "../foenixLibrary/mytypes.h"
#include "../foenixLibrary/vicky.h"
#include "../foenixLibrary/timer.h"
#include "../foenixLibrary/interrupt.h"

#include "include/allegro.h"

void *heap_start = (void * )0x190000, *heap_end = (void * )0x240000;


#define UART1 (*(unsigned char *)0xAF13F8)
#define UART1X (*(unsigned char *)0xAF13FD)
char debugStringBuffer[200];
int debugBufferLength = 0;

char spinner[] = {'|', '/', '-', '\\', '|', '/', '-', '\\'};
char spinnerState = 0;
int reg = 0;

void IRQHandler(void)              
{          
	

	// if (reg = (INT_PENDING_REG0 & FNX0_INT02_TMR0))
	// {
		
	// 	textScreen[6] = spinner[spinnerState];
	// 	if (spinnerState < 7)
	// 		spinnerState++;
	// 	else
	// 	{
	// 		spinnerState = 0;
	// 	}

	// 	//disk_timerproc();

	// 	reg = INT_PENDING_REG0 & FNX0_INT02_TMR0;
	// 	INT_PENDING_REG0 = reg;
	// }   

	// if (reg = (INT_PENDING_REG3 & FNX3_INT02_IDE))
	// {
		
	// 	textScreen[10] = spinner[spinnerStateDisk];
	// 	if (spinnerStateDisk < 7)
	// 		spinnerStateDisk++;
	// 	else
	// 	{
	// 		spinnerStateDisk = 0;
	// 	}

	// 	printf("interrupt %d", IDE_CMD_STAT);

	// 	reg = INT_PENDING_REG3 & INT_PENDING_REG3;
	// 	INT_PENDING_REG3 = reg;
	// }   
	textScreen[10] = spinner[spinnerState];
	if (spinnerState < 7)
		spinnerState++;
	else
	{
		spinnerState = 0;
	}

	if (reg = (INT_PENDING_REG1 & FNX1_INT00_KBD))
	{
		
		

		//printf("interrupt %d\n", (*keyInterrupt)());
		(*keyInterrupt)();
		//textScreen[15] = (*(volatile unsigned char *)0xAF1060);

		reg = INT_PENDING_REG1 & FNX1_INT00_KBD;
		INT_PENDING_REG1 = reg;
	}   

	//(*keyInterrupt)();

	//printf("interrupt");
}

void COPHandler(void)              
{             
	printf("COP");
}

void BRKHandler(void)              
{             
	printf("break");
	while(1) {};
}

int main()
{
	char buf[128];
	int k;
	char temp;
	//if (allegro_init() != 0)
	//return 1;
	
	install_keyboard();
	// install_timer();

	// if (set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) != 0) {
	// if (set_gfx_mode(GFX_SAFE, 640, 480, 0, 0) != 0) {
	// 	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	// 	allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
	// return 1;
	// }

	// enable text mode
	MASTER_CTRL_REG_L = Mstr_Ctrl_Text_Mode_En;

	// Emulator workarround for screen
	//set the display size - 128 x 64
	COLS_PER_LINE = 80;
	LINES_MAX = 60;
	//set the visible display size - 80 x 60
  	COLS_VISIBLE = 80;
	LINES_VISIBLE = 60;

	//INT_MASK_REG3 = 0xFB; // unmask harddisk;

	INT_MASK_REG0 = 0xFF;
	INT_MASK_REG1 = 0xFE; // Unmask keyboard

	// enable interrupts
	enableInterrupts();

	setEGATextPalette();
	clearTextScreen(' ', 0xD, 0x2);

	VKY_TXT_CURSOR_X_REG = 0;
	VKY_TXT_CURSOR_Y_REG = 0;

	BORDER_X_SIZE = 0;
	BORDER_Y_SIZE = 0;
    // Create the stack

    // Clear variables
    //memset(variableStack, 0, 512 * 15);
	//write(0, "xxxxxxxxxxxxxxx", 10);
	while(1)
	{
		// set text
	// textScreen[0] = 'H';
	// textScreen[1] = 'e';
	// textScreen[2] = 'l';
	// textScreen[3] = 'l';
	// textScreen[4] = 'o';
		if (keypressed() == 1)
		{
			k = readkey();

			// if ((k & 0xff) == 'd')     /* by ASCII code */
	 		// 	printf("You pressed '%c'\n", (k & 0xff));
			// else
			// {
			// 	printf("You pressed something else '%c'\n", (k & 0xff));
			// }
			// printf ("%c\n", (k & 0xff));
			buf[0] = (k & 0xff);
			write(0, buf, 1);
			
		}
	
	// textScreen[5] = 'W'; 
	// textScreen[6] = 'o';
	// textScreen[7] = 'r';
	// textScreen[8] = 'l';
	// textScreen[9] = 'd';
	}

} 





/* printf functions */

void _abort(void) {

}

int close(int fd) {
    return 0;
}

int creat(const char *_name, int _mode) {
    return 0;
}


long lseek(int fd, long pos, int rel) {
    return 0;
}

int open(const char * _name, int _mode) {
    return 0;
}

size_t read(int fd, void *buffer, size_t len) {
    return 0;
}

int unlink(const char *filename) {
    return 0;
}

size_t write(int fd, void *buffer, size_t len) {
    size_t count;

	if(fd < 3)
	{
		for (count = 0; count < len; count++)
		{
			if (((unsigned char *)buffer)[count] == '\n')
			{
				VKY_TXT_CURSOR_X_REG = 0;
				VKY_TXT_CURSOR_Y_REG++;

				if (VKY_TXT_CURSOR_Y_REG == LINES_VISIBLE)
				{
					VKY_TXT_CURSOR_Y_REG = 0;
				}

				continue;
			}

			textScreen[(0x80 * VKY_TXT_CURSOR_Y_REG) + VKY_TXT_CURSOR_X_REG] = ((unsigned char *)buffer)[count];
			
			//textScreenColor[(0x80 * VKY_TXT_CURSOR_Y_REG) + VKY_TXT_CURSOR_X_REG] = 0xE0;
			/*
			textScreenColor[(0x80 * VKY_TXT_CURSOR_Y_REG) + VKY_TXT_CURSOR_X_REG] = color;
			color += 16;
			if (color == 0xF0)
				color = 0x10;*/
			
			VKY_TXT_CURSOR_X_REG++;
			
			if (VKY_TXT_CURSOR_X_REG == COLS_VISIBLE)
			{
				VKY_TXT_CURSOR_X_REG = 0;
				VKY_TXT_CURSOR_Y_REG++;
				
				if (VKY_TXT_CURSOR_Y_REG == LINES_VISIBLE)
				{
					VKY_TXT_CURSOR_Y_REG = 0;
				}
			}
		}
	}
	else
	{
		// for (count = 0; count < len; count++)
		// {
		// 	UART1 = ((unsigned char *)buffer)[count];
		// }
		for (count = 0; count < len; count++)
		{
			while(!(UART1X & 0x20))
			{
			}
			UART1 = ((unsigned char *)buffer)[count];
		}
	}
	
    return len;
}

//
// Missing STDLIB.H function
//
int    isatty(int fd) {
    // descriptors 0, 1 and 2 are STDIN_FILENO, STDOUT_FILENO and STDERR_FILENO
    return fd < 3;
}

/* end of printf functions */

/* Helpers */
/*
foenix variant of strdup as the included version in the compiler library crashes my code.
https://stackoverflow.com/questions/37132549/implementation-of-strdup-in-c-programming
*/
char *f_strdup(char *src)
{
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}
