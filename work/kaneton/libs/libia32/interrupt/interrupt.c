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

extern struct s_idt_entry gl_idt[256];

void			set_gate(t_uint8	number,
				 t_uint32	offset,
				 t_uint16	segment_selector)
{
  unsigned short        offsetH;
  unsigned short        offsetL;

  offsetH = (offset >> 16) & 0xFFFF;
  offsetL = offset & 0xFFFF;
  gl_idt[number].field[0] = offsetL & 0xFF;
  gl_idt[number].field[1] = (offsetL >> 8) & 0xFF;
  gl_idt[number].field[2] = segment_selector & 0xFF;
  gl_idt[number].field[3] = (segment_selector >> 8) & 0xFF;
  gl_idt[number].field[4] = 0;
  gl_idt[number].field[5] = 0x8E; //1 00 0 1 110
  gl_idt[number].field[6] = offsetH & 0xFF;
  gl_idt[number].field[7] = (offsetH >> 8) & 0xFF;
}

void event_call(int id)
{
/*   t_uint32 esp; */
/*   asm volatile("movl %%edi, %0\n" */
/*                : "=m" (esp) */
/*                ); */
  /* printf("."); */
  if (id >=32 && id < 48)
    PIC_ACK(id-32);
  o_event* o;
  if (event_get(id, &o) == ERROR_NONE)
    {
      t_uint32 addr;
      SCR2(addr);
      ((t_event_handler2)o->handler.function)(id, addr);
    }
  if (id <= 16)
    OUTB(0x20, 0x20);
}



void event_call_error(int id, t_uint32 error)
{
/*   t_uint32 esp; */
/*   asm volatile("movl %%edi, %0\n" */
/*                : "=m" (esp) */
/*                ); */
  printf("e %i", id);
  while (1)
    ;
  o_event* o;
  if (event_get(id, &o) == ERROR_NONE)
    {
      t_uint32 addr;
      SCR2(addr);
      ((t_event_handler2)o->handler.function)(id, addr);
    }
  if (id <= 16)
    OUTB(0x20, 0x20);
}
/* #define __handler__(_num_)				\ */
/* static void int_##_num_()				\ */
/* {							\ */
/*   SAVE_CONTEXT();					\ */
/*   int id = _num_;					\ */
/*   if (id >=32 && id < 48)				\ */
/*     PIC_ACK(id-32);					\ */
/*   o_event* o;						\ */
/*   if (event_get(id, &o) == ERROR_NONE)			\ */
/*   {							\ */
/*     t_uint32 addr;					\ */
/*     SCR2(addr);						\ */
/*     ((t_event_handler2)o->handler.function)(id, addr);	\ */
/*   }							\ */
/*   if (_num_ <= 16)					\ */
/*     OUTB(0x20, 0x20);					\ */
/*   RESTORE_CONTEXT();					\ */
/*   ADJUST_STACK();					\ */
/*   asm volatile("iret");					\ */
/* } */
