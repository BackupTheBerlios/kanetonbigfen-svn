/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/libs/libia32/include/interrupt/interrupt.h
 *
 * created       renaud voltz   [fri feb 17 16:48:22 2006]
 * updated       matthieu bucchianeri   [wed feb  7 14:01:22 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 *
 */

#ifndef IA32_INTERRUPT_INTERRUPT_H
#define IA32_INTERRUPT_INTERRUPT_H       1

// FIXME: some declarations has beed removed here

# define SAVE_CONTEXT()		\
  asm volatile("push %eax\n\t"		\
  	       "push %ebx\n\t"		\
  	       "push %ecx\n\t"		\
  	       "push %edx\n\t"		\
	       "push %esi\n\t"		\
	       "push %edi\n\t")

# define RESTORE_CONTEXT()		\
  asm volatile("pop %edi\n\t"		\
               "pop %esi\n\t"		\
               "pop %edx\n\t"		\
               "pop %ecx\n\t"		\
               "pop %ebx\n\t"		\
	       "pop %eax\n\t")

# define ADJUST_STACK()			\
  asm volatile("mov %ebp, %esp\n\t"	\
	       "pop %ebp")

#define __handler__(_num_)				\
static void int_##_num_()				\
{							\
  SAVE_CONTEXT();					\
  int id = _num_;					\
  if (id >=32 && id < 48)				\
    PIC_ACK(id-32);					\
  o_event* o;						\
  if (event_get(id, &o) == ERROR_NONE)			\
  {							\
    t_uint32 addr;					\
    SCR2(addr);						\
    ((t_event_handler2)o->handler.function)(id, addr);	\
  }							\
  if (_num_ <= 16)					\
    OUTB(0x20, 0x20);					\
  RESTORE_CONTEXT();					\
  ADJUST_STACK();					\
  asm volatile("iret");					\
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

#endif
