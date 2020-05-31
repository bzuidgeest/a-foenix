/*         ______   ___    ___ 
 *        /\  _  \ /\_ \  /\_ \ 
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___ 
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      DOS keyboard module.
 *
 *      By Shawn Hargreaves.
 *
 *      See readme.txt for copyright information.
 */


//#include <conio.h>

#include "allegro.h"
#include "fmxkeyboard.h"
#include "interrupt.h"
#include "../include/allegro/internal/aintern.h"
#include "../include/allegro/platform/aintdos.h"

#define KEYBOARD_INT    9

static int leds_ok = TRUE;

static int in_a_terrupt = FALSE;

static int extended_key = FALSE;

static int pcdos_key_init(void);
static void pcdos_key_exit(void);
static void pcdos_set_leds(int leds);
static void pcdos_set_rate(int delay, int rate);


KEYBOARD_DRIVER keydrv_pcdos =
{
   KEYDRV_PCDOS,
   '\0',
   '\0',
   "PC keyboard (DOS)",
   FALSE,
   pcdos_key_init,
   pcdos_key_exit,
   NULL,
   pcdos_set_leds,
   pcdos_set_rate,
   NULL, NULL,
   _pckey_scancode_to_ascii,
   _pckey_scancode_to_name
};



/* list the available drivers */
_DRIVER_INFO _keyboard_driver_list[] =
{
   { KEYDRV_PCDOS,   &keydrv_pcdos,    TRUE  },
   { 0,              NULL,             0     }
};



/* kb_wait_for_write_ready:
 *  Wait for the keyboard controller to set the ready-for-write bit.
 */
//inline
static int kb_wait_for_write_ready(void)
{
   int timeout = 4096;

   while ((timeout > 0) && (KBD_STATUS & 2))
      timeout--;

   return (timeout > 0);
}



/* kb_wait_for_read_ready:
 *  Wait for the keyboard controller to set the ready-for-read bit.
 */
//inline
static int kb_wait_for_read_ready(void)
{
   int timeout = 16384;

   while ((timeout > 0) && (!(KBD_STATUS & 1)))
      timeout--;

   return (timeout > 0);
}



/* kb_send_data:
 *  Sends a byte to the keyboard controller. Returns 1 if all OK.
 */
//inline
static int kb_send_data(unsigned char data)
{
   int resends = 4;
   int timeout, temp;

   do {
      if (!kb_wait_for_write_ready())
	 return 0;

      KBD_OUT_BUF = data;
      timeout = 4096;

      while (--timeout > 0) {
	 if (!kb_wait_for_read_ready())
	    return 0;

	 temp = KBD_IN_BUF;

	 if (temp == KB_ACK)
	    return 1;

	 if (temp == KB_RESEND)
	    break;
      }
   } while ((resends-- > 0) && (timeout > 0));

   return 0;
}



/* pcdos_set_leds:
 *  Updates the LED state.
 */
static void pcdos_set_leds(int leds)
{

	if (!leds_ok)
		return;

	if (!kb_send_data(0xED)) {
		kb_send_data(0xF4);
		leds_ok = FALSE;
	}
	else if (!kb_send_data((leds>>8) & 7)) {
		kb_send_data(0xF4);
		leds_ok = FALSE;
	}
	write(4, " led5", 5);

	return;
}


/* pcdos_set_rate:
 *  Sets the key repeat rate.
 */
static void pcdos_set_rate(int delay, int rate)
{
   if (!leds_ok)
      return;

   if (delay < 375)
      delay = 0;
   else if (delay < 625)
      delay = 1;
   else if (delay < 875)
      delay = 2;
   else
      delay = 3;

   rate = MID(0, (rate-33) * 31 / (500-33), 31);

   DISABLE();

   if ((!kb_send_data(0xF3)) || (!kb_send_data((delay << 5) | rate)))
      kb_send_data(0xF4);

   ENABLE();
}



/* keyint:
 *  Hardware level keyboard interrupt (int 9) handler.
 */
static int keyint(void)
{
   int code = KBD_IN_BUF;

   in_a_terrupt = TRUE;

   _handle_pckey(code);

   in_a_terrupt = FALSE;

   #ifdef ALLEGRO_DJGPP

      /* three-finger salute for killing the program */
      if (three_finger_flag) {
	 if (((code == 0x4F) || (code == 0x53)) &&
	     (_key_shifts & KB_CTRL_FLAG) && (_key_shifts & KB_ALT_FLAG)) {
	    asm (
	       "  movb $0x79, %%al ; "
	       "  call ___djgpp_hw_exception "
	    : : : "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory"
	    );
	 }

	 /* also handle ctrl+break, like the standard djgpp libc */
	 if ((code == 0x46) && (extended_key) &&
	     (_key_shifts & KB_CTRL_FLAG)) {
	    asm (
	       "  movb $0x1B, %%al ; "
	       "  call ___djgpp_hw_exception "
	    : : : "%eax", "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory"
	    );
	 }
      }

   #endif

   extended_key = (code == 0xE0);

	// signals End Of Interrupt to PIC on dos.
   //outportb(0x20, 0x20);
   return 0;
}



/* pcdos_key_init:
 *  Installs the keyboard handler.
 */
static int pcdos_key_init(void)
{
	char temp;
   //int s1, s2, s3;
write(4, "init1", 5);
   _pckeys_init();
  write(4, "init4", 5); 
   /* read the current BIOS keyboard state */
//    while (kbhit())
//       simulate_keypress(getch());

//    //_farsetsel(_dos_ds);

// //    s1 = _farnspeekb(0x417);
// //    s2 = _farnspeekb(0x418);
// //    s3 = _farnspeekb(0x496);

//    _key_shifts = 0;

//    if (s1 & 1) { _key_shifts |= KB_SHIFT_FLAG; key[KEY_RSHIFT]   = TRUE; }
//    if (s1 & 2) { _key_shifts |= KB_SHIFT_FLAG; key[KEY_LSHIFT]   = TRUE; }
//    if (s2 & 1) { _key_shifts |= KB_CTRL_FLAG;  key[KEY_LCONTROL] = TRUE; }
//    if (s2 & 2) { _key_shifts |= KB_ALT_FLAG;   key[KEY_ALT]      = TRUE; }
//    if (s3 & 4) { _key_shifts |= KB_CTRL_FLAG;  key[KEY_RCONTROL] = TRUE; }
//    if (s3 & 8) { _key_shifts |= KB_ALT_FLAG;   key[KEY_ALTGR]    = TRUE; }

//    if (s1 & 16) _key_shifts |= KB_SCROLOCK_FLAG;
//    if (s1 & 32) _key_shifts |= KB_NUMLOCK_FLAG;
//    if (s1 & 64) _key_shifts |= KB_CAPSLOCK_FLAG;

//    key_shifts = _key_shifts;
write(4, "init7", 5);
	// Assign keyboard interrupt.
	keyInterrupt = &keyint;
	// unmask keyboard interrupt
	temp = INT_MASK_REG1 | 0xFE;
	INT_MASK_REG1 = temp;

   //_install_irq(KEYBOARD_INT, keyint);
write(4, "init8", 5);
   pcdos_set_leds(_key_shifts);
write(4, "init9", 5);
   return 0;
}



/* pcdos_key_exit:
 *  Removes the keyboard handler.
 */
static void pcdos_key_exit(void)
{
//    int s1, s2, s3;

//    _remove_irq(KEYBOARD_INT);

   /* transfer state info back to the BIOS */
   //_farsetsel(_dos_ds);

//    s1 = _farnspeekb(0x417) & 0x80;
//    s2 = _farnspeekb(0x418) & 0xFC;
//    s3 = _farnspeekb(0x496) & 0xF3;

//    if (key[KEY_RSHIFT])   { s1 |= 1; }
//    if (key[KEY_LSHIFT])   { s1 |= 2; }
//    if (key[KEY_LCONTROL]) { s2 |= 1; s1 |= 4; }
//    if (key[KEY_ALT])      { s1 |= 8; s2 |= 2; }
//    if (key[KEY_RCONTROL]) { s1 |= 4; s3 |= 4; }
//    if (key[KEY_ALTGR])    { s1 |= 8; s3 |= 8; }

//    if (_key_shifts & KB_SCROLOCK_FLAG) s1 |= 16;
//    if (_key_shifts & KB_NUMLOCK_FLAG)  s1 |= 32;
//    if (_key_shifts & KB_CAPSLOCK_FLAG) s1 |= 64;

//    _farsetsel(_dos_ds);

//    _farnspokeb(0x417, s1);
//    _farnspokeb(0x418, s2);
//    _farnspokeb(0x496, s3);
}

