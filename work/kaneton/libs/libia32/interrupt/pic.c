/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/libs/libia32/interrupt/pic.c
 *
 * created       matthieu bucchianeri   [tue dec 20 13:44:58 2005]
 * updated       matthieu bucchianeri   [wed feb  7 13:34:53 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this  file  implements   the  management  of  the   programmable  interrupt
 * controller  (PIC 8259A)  on  ia32  architecture.
 *
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

// FIXME: lot of code has beed removed here

void init_pics()
{
  // see http://inferno.cs.univ-paris8.fr/~am/tutorial/os/tutorial07.html
  //ICW1 (init)
  OUTB(0x20, 0x11);
  OUTB(0xA0, 0x11);

  //ICW2 debut irq (32/32+8)
  OUTB(0x21, 0x20); //08 ?
  OUTB(0xA1, 0x28); //70?

  //ICW3 slave/master on
  OUTB(0x21, 0x04);
  OUTB(0xA1, 0x02);

  //ICW4 x86
  OUTB(0x21, 0x01);
  OUTB(0xA1, 0x01);

  //OCW
  OUTB(0x21, 0xFF);
  OUTB(0xA1, 0xFF);
}

void irq_enable(int i)
{
  int mask;
  int tomask = 1 << i;
  if (i < 8)
    {
      INB(0x21, mask);
      OUTB(0x21, mask & ~tomask);
    }
  else
    {
      tomask = 1 << (i-8);
      irq_enable(2);
      INB(0xA1, mask);
      OUTB(0xA1, mask & ~tomask);
    }
}

void irq_disable(int i)
{
  int mask;
  int tomask = 1 << i;
  if (i < 8)
    {
      INB(0x21, mask);
      OUTB(0x21, mask | tomask);
    }
  else
    {
      tomask = 1 << (i-8);
      INB(0xA1, mask);
      OUTB(0xA1, mask | tomask);
      if ((mask | tomask) == 0xFF)
	irq_disable(2);
    }

}
