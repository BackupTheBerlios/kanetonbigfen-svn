/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/include/core/debug.h
 *
 * created       julien quintard   [mon nov 28 19:37:01 2005]
 * updated       matthieu bucchianeri   [wed feb  7 11:20:00 2007]
 */

#ifndef CORE_DEBUG_H
#define CORE_DEBUG_H		1

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <arch/machdep/machdep.h>

/*
 * ---------- macros ----------------------------------------------------------
 */

#define DEBUG_PARAMS		(1 << 0)
#define DEBUG_AS		(1 << 1)
#define DEBUG_SEGMENT		(1 << 2)
#define DEBUG_SET		(1 << 3)
#define DEBUG_STATS		(1 << 4)
#define DEBUG_REGION		(1 << 5)
#define DEBUG_TASK		(1 << 6)
#define DEBUG_THREAD		(1 << 7)
#define DEBUG_SCHEDULE		(1 << 8)
#define DEBUG_MESSAGE		(1 << 9)
#define DEBUG_CAPABILITY	(1 << 10)
#define DEBUG_INTERFACE		(1 << 11)

#define DEBUG								\
  (CONF_DEBUG)


/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../../core/debug/debug.c
 *      ../../core/debug/cons-text.c
 *      ../../core/debug/serial.c
 */

/*
 * ../../core/debug/debug.c
 */


/*
 * ../../core/debug/cons-text.c
 */

void			cons_clear(void);

void			cons_scroll(t_uint16			lines);

void			cons_attr(t_uint8			attr);

int			cons_print_char(char			c);

void			cons_print_string(char*			string);

void			cons_msg(char				indicator,
				 char*				fmt,
				 ...);

t_error			cons_init(void);

t_error			cons_clean(void);


/*
 * ../../core/debug/serial.c
 */


/*
 * eop
 */

#endif
