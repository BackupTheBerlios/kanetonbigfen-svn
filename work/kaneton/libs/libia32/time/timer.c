/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/libs/libia32/time/timer.c
 *
 * created       renaud voltz   [mon feb 27 04:20:33 2006]
 * updated       matthieu bucchianeri   [wed feb  7 13:35:11 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this  file  implements   the  management  of  the   progammable   interval
 * timer  (PIT 8254)  on  ia32  architecture.
 *
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

// FIXME: lot of code has beed removed here

void ia32_pit_init()
{
  OUTB(0x43, 0x34); //00 11 010 0
  OUTB(0x40, 0xA9); //least
  OUTB(0x40, 0x04); //most, 1khz
}
