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
 *      Debug facilities.
 *
 *      By Shawn Hargreaves.
 *
 *      See readme.txt for copyright information.
 */


#ifndef ALLEGRO_DEBUG_H
#define ALLEGRO_DEBUG_H

#include "allegro/base.h"

void al_assert (const char *file, int linenr);
void al_trace (const char *msg, ...);

void register_assert_handler (int (*handler)(const char *msg));
void register_trace_handler (int (*handler)(const char *msg));


#ifdef DEBUGMODE
   #define ASSERT(condition)     { if (!(condition)) al_assert(__FILE__, __LINE__); }
   #define TRACE                 al_trace
#else
   #define ASSERT(condition)
   #define TRACE                 1 ? (void) 0 : al_trace
#endif

#endif          /* ifndef ALLEGRO_DEBUG_H */


