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
/*   t_error			(*event_show)(i_event); */
/*   t_error			(*event_notify)(i_event); */
/*   t_error			(*event_reserve)(i_event, */
/* 						 t_uint32, */
/* 						 u_event_handler); */
/*   t_error			(*event_release)(i_event); */
/*   t_error			(*event_init)(void); */
/*   t_error			(*event_clean)(void); */
d_event				event_dispatch =
  {
    NULL,
    NULL,
    NULL,
    NULL,
    ia32_event_init,
    NULL
  };

//static unsigned char idt[256][8];
static struct s_idt_entry gl_idt[256];

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

/* #define _handler_(_num_, _string_)	\ */
/* void int_##_num_()			\ */
/* {					\ */
/*   printf(_string_);			\ */
/*   while (1)				\ */
/*     ;					\ */
/* } */

/* _handler_(0, "Divide Error"); */
/* _handler_(1, "Debug Exceptions"); */
/* _handler_(2, "Intel reserved"); */
/* _handler_(3, "Breakpoint"); */
/* _handler_(4, "Overflow"); */
/* _handler_(5, "Bounds Check"); */
/* _handler_(6, "Invalid Opcode"); */
/* _handler_(7, "Coprocessor Not Available"); */
/* _handler_(8, "Double Fault"); */
/* _handler_(9, "Coprocessor Segment Overrun"); */
/* _handler_(10, "Invalid TSS"); */
/* _handler_(11, "Segment Not Present"); */
/* _handler_(12, "Stack Exception"); */
/* _handler_(13, "General Protection Exception(Triple Fault)"); */
/* _handler_(14, "Page Fault"); */
/* _handler_(16, "Coprocessor Error"); */

void int_32()
{
  int id = 32;
  o_event* o;
  event_get(id, &o);
  t_uint32 addr;
  SCR2(addr);
  ((t_event_handler2)o->handler.function)(id, addr);;
  printf("int_32");
  while (1)
    ;
}

struct s_idt_entry
{
  t_uint8	field[8];
}__attribute__((packed));

struct s_idt_ptr
{
  t_uint16	limit;
  t_uint32	base;
}__attribute__((packed));

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
  set_gate(0, (t_uint32)int_0, kcs);
  set_gate(1, (t_uint32)int_1, kcs);
  set_gate(2, (t_uint32)int_2, kcs);
  set_gate(3, (t_uint32)int_3, kcs);
  set_gate(4, (t_uint32)int_4, kcs);
  set_gate(5, (t_uint32)int_5, kcs);
  set_gate(6, (t_uint32)int_6, kcs);
  set_gate(7, (t_uint32)int_7, kcs);
  set_gate(8, (t_uint32)int_8, kcs);
  set_gate(9, (t_uint32)int_9, kcs);
  set_gate(10, (t_uint32)int_10, kcs);
  set_gate(11, (t_uint32)int_11, kcs);
  set_gate(12, (t_uint32)int_12, kcs);
  set_gate(13, (t_uint32)int_13, kcs);
  set_gate(14, (t_uint32)int_14, kcs);
  set_gate(16, (t_uint32)int_16, kcs);
  set_gate(32, (t_uint32)int_32, kcs);
  return ERROR_NONE;
}
