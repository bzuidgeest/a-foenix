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
 *      System level: initialization, cleanup, etc.
 *
 *      By Shawn Hargreaves.
 *
 *      See readme.txt for copyright information.
 */


#ifndef ALLEGRO_SYSTEM_H
#define ALLEGRO_SYSTEM_H

#include "allegro/base.h"
//#include "unicode.h"
//#include "config.h"



struct RGB;
struct BITMAP;
struct GFX_VTABLE;
struct GFX_MODE;

#define ALLEGRO_ERROR_SIZE 256

extern char allegro_id[];
extern char allegro_error[];

extern int os_type;
extern int os_version;
extern int os_revision;
extern int os_multitasking;

#define SYSTEM_AUTODETECT  0
#define SYSTEM_NONE        AL_ID('N','O','N','E')

#define MAKE_VERSION(a, b, c) (((a)<<16)|((b)<<8)|(c))

// AL_FUNC(int, _install_allegro_version_check, (int system_id, int *errno_ptr,
//    AL_METHOD(int, atexit_ptr, (AL_METHOD(void, func, (void)))), int version));

// AL_INLINE(int, install_allegro, (int system_id, int *errno_ptr,
//    AL_METHOD(int, atexit_ptr, (AL_METHOD(void, func, (void))))),
// {
//    return _install_allegro_version_check(system_id, errno_ptr, atexit_ptr, \
//       MAKE_VERSION(ALLEGRO_VERSION, ALLEGRO_SUB_VERSION, ALLEGRO_WIP_VERSION));
// })

// #define allegro_init()  _install_allegro_version_check(SYSTEM_AUTODETECT, &errno, \
//    (int (*)(void (*)(void)))atexit, \
//    MAKE_VERSION(ALLEGRO_VERSION, ALLEGRO_SUB_VERSION, ALLEGRO_WIP_VERSION))

void allegro_exit(void);

void allegro_message(const char *msg, ...);
void get_executable_name(char *output, int size);
int set_close_button_callback(void proc(void));


void check_cpu (void);

typedef struct SYSTEM_DRIVER
{
   int  id;
   char *name;
   char *desc;
   char *ascii_name;
   int (*init)(void);
   void (*exit)(void);
   void (*get_executable_name)(char *output, int size);
   int (*find_resource)(char *dest, char *resource, int size);
   void (*set_window_title)(char *name);
   int (*set_close_button_callback)(void (*proc)(void));
   void (*message)(char *msg);
   void (*assert)(char *msg);
   void (*save_console_state)(void);
   void (*restore_console_state)(void);
   struct BITMAP * (*create_bitmap)(int color_depth, int width, int height);
   void (*created_bitmap)(struct BITMAP *bmp);
   struct BITMAP * (*create_sub_bitmap)(struct BITMAP *parent, int x, int y, int width, int height);
   void (*created_sub_bitmap)(struct BITMAP *bmp, struct BITMAP *parent);
   int (*destroy_bitmap)(struct BITMAP *bitmap);
   void (*read_hardware_palette)(void);
   void (*set_palette_range)(struct RGB *p, int from, int to, int retracesync);
   struct GFX_VTABLE * (*get_vtable)(int color_depth);
   int (*set_display_switch_mode)(int mode);
   void (*display_switch_lock)(int lock, int foreground);
   int (*desktop_color_depth)(void);
   int (*get_desktop_resolution)(int *width, int *height);
   void (*get_gfx_safe_mode)(int *driver, struct GFX_MODE *mode);
   void (*yield_timeslice)(void);
   void *(*create_mutex)(void);
   void (*destroy_mutex)(void *handle);
   void (*lock_mutex)(void *handle);
   void (*unlock_mutex)(void *handle);
   _DRIVER_INFO * (*gfx_drivers)(void);
   _DRIVER_INFO * (*digi_drivers)(void);
   _DRIVER_INFO * (*midi_drivers)(void);
   _DRIVER_INFO * (*keyboard_drivers)(void);
   _DRIVER_INFO * (*mouse_drivers)(void);
   _DRIVER_INFO * (*joystick_drivers)(void);
   _DRIVER_INFO * (*timer_drivers)(void);
} SYSTEM_DRIVER;


extern SYSTEM_DRIVER system_none;
extern SYSTEM_DRIVER * system_driver;
extern _DRIVER_INFO _system_driver_list[];


extern int (*keyInterrupt)(void);

//#include "inline/system.inl"

#endif          /* ifndef ALLEGRO_SYSTEM_H */


