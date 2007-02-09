/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/libs/libia32/interrupt/interrupt.c
 *
 * created       renaud voltz   [thu feb 23 10:49:43 2006]
 * updated       matthieu bucchianeri   [wed feb  7 13:34:51 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements exception and irq handling on ia32 architecture.
 * both exceptions and irq's are called interrupts in the machine-dependent
 * code of kaneton.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

// FIXME: lot of code has beed removed here
