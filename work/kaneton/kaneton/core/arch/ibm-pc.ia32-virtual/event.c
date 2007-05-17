/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/arch/ibm-pc.ia32-virtual/event.c
 *
 * created       renaud voltz   [mon feb 13 01:05:52 2006]
 * updated       matthieu bucchianeri   [wed feb  7 10:46:43 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements dependent code for the events on ia32 with paging
 * architecture.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>
#include <core/event.h>

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the event manager dispatch.
 */

d_event				event_dispatch =
  {
    NULL,
    NULL,
    ia32_event_reserve,
    ia32_event_release,
    ia32_event_init,
    NULL
  };

struct s_idt_entry gl_idt[256];

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

#include "handler_def.inc" // __handler__(0...);

t_error ia32_event_init(void)
{
  int			i;
  int			j;

  for (j = 0; j < 256; ++j)
    for (i = 0; i < 8; ++i)
      gl_idt[j].field[i] = 0x00;

  struct s_idt_ptr	idtr;

  idtr.limit = 256 * 8;
  idtr.base = (unsigned int) gl_idt;
  LIDT(idtr);
  t_uint16		kcs;
  if (gdt_build_selector(PMODE_GDT_CORE_CS, ia32_prvl_supervisor, &kcs) == ERROR_UNKNOWN)
    return ERROR_UNKNOWN;
  #include "set_gate.inc" //event_reserve(0..., EVENT_FUNCTION, (u_event_handler)int_0...);
  init_pics();
  asm volatile("sti");
  return ERROR_NONE;
}

t_error			ia32_event_reserve(i_event		id,
					   t_uint32		type,
					   u_event_handler	handler)
{
  handler = handler;
  if (type == EVENT_FUNCTION)
    {
      if (id >= 32 && id < 48)
	irq_enable(id - 32);
      return ERROR_NONE;
    }
  return ERROR_UNKNOWN;
}

t_error			ia32_event_release(i_event id)
{
  if (id >= 32 && id < 48)
    irq_disable(id - 32);
  return ERROR_NONE;
}
