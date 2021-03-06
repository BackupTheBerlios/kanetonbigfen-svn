/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /home/buckman/kaneton/libs/libia32/include/interrupt/ipi.h
 *
 * created       matthieu bucchianeri   [mon aug 21 15:03:41 2006]
 * updated       matthieu bucchianeri   [mon aug 21 15:05:06 2006]
 */

#ifndef IA32_INTERRUPT_IPI_H
#define IA32_INTERRUPT_IPI_H	1

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include "../misc/types.h"

/*
 * ---------- types -----------------------------------------------------------
 */

typedef enum
  {
	ipi_all,
	ipi_all_but_me
  }	t_ia32_ipi_dest;

#endif
