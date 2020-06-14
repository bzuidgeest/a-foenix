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
 *      Timer routines.
 *
 *      By Shawn Hargreaves.
 *
 *      See readme.txt for copyright information.
 */


#ifndef ALLEGRO_TIMER_H
#define ALLEGRO_TIMER_H

#include "allegro/base.h"

#define TIMERS_PER_SECOND     1193181L
#define SECS_TO_TIMER(x)      ((long)(x) * TIMERS_PER_SECOND)
#define MSEC_TO_TIMER(x)      ((long)(x) * (TIMERS_PER_SECOND / 1000))
#define BPS_TO_TIMER(x)       (TIMERS_PER_SECOND / (long)(x))
#define BPM_TO_TIMER(x)       ((60 * TIMERS_PER_SECOND) / (long)(x))

typedef struct TIMER_DRIVER
{
   int  id;
   const char *name;
   const char *desc;
   const char *ascii_name;
   int (*init) (void);
   void (*exit) (void);
   int (*install_int) (void (*proc) (void), long speed);
   void (*remove_int) (void (*proc) (void));
   int (*install_param_int) (void (*proc) (void *param), void *param, long speed);
   void (*remove_param_int) (void (*proc) (void *param), void *param);
   int (*can_simulate_retrace) (void);
   void (*simulate_retrace) (int enable);
   void (*rest) (unsigned int tyme, void (*callback)(void));
} TIMER_DRIVER;


extern TIMER_DRIVER *timer_driver;
extern _DRIVER_INFO _timer_driver_list[];

int install_timer (void);
void remove_timer (void);

int install_int_ex (void (*proc) (void), long speed);
int install_int (void (*proc) (void), long speed);
void remove_int (void (*proc) (void));

int install_param_int_ex (void (*proc) (void *param), void *param, long speed);
int install_param_int (void (*proc) (void *param), void *param, long speed);
void remove_param_int (void (*proc) (void *param), void *param);

extern volatile int retrace_count;

void rest (unsigned int tyme);
void rest_callback (unsigned int tyme, void (*callback) (void));

#endif          /* ifndef ALLEGRO_TIMER_H */

