/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/libs/libia32/include/interrupt/pic.h
 *
 * created       renaud voltz   [wed mar 15 10:49:45 2006]
 * updated       matthieu bucchianeri   [wed feb  7 14:01:26 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 *
 */

#ifndef IA32_INTERRUPT_PIC_H
#define IA32_INTERRUPT_PIC_H

// FIXME: some declarations has beed removed here

# define PIC_ACK(irq)			\
  {					\
    if (irq < 8 && irq != 2)		\
      OUTB(0x20, 1 << 5);		\
    else				\
      {					\
	OUTB(0x20, 1 << 5);		\
	OUTB(0xA0, 1 << 5);		\
      }					\
  }

#endif

void init_pics();
