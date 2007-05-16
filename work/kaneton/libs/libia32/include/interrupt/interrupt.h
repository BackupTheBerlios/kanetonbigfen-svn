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

t_uint32 global_esp;
t_uint32 global_ebp;

#define REST_CONTEXT							\
  "pop %edi\n\t"							\
  "pop %esi\n\t"							\
  "pop %edx\n\t"							\
  "pop %ecx\n\t"							\
  "pop %ebx\n\t"							\
  "pop %eax\n\t"							\
  "pop %gs\n\t"								\
  "pop %fs\n\t"								\
  "pop %es\n\t"								\
  "pop %ds\n\t"

#define SAVE_CONTEXT							\
  "push %ds\n\t"							\
  "push %es\n\t"							\
  "push %fs\n\t"							\
  "push %gs\n\t"							\
  "push %eax\n\t"							\
  "push %ebx\n\t"							\
  "push %ecx\n\t"							\
  "push %edx\n\t"							\
  "push %esi\n\t"							\
  "push %edi\n\t"


#define CTX_SIZE ( 8 * 4 )
#define STACK_SIZE ( CTX_SIZE + 3 * 4 )

#define ESP2VAR								\
  "mov %esp, global_esp\n\t"						\
  "mov %ebp, global_ebp\n\t"

#define VAR2ESP								\
  "mov global_esp, %esp\n\t"						\
  "mov global_ebp, %ebp\n\t"

#define PUT_CR3								\
  "mov gl_cr3_dest, %eax\n\t"						\
  "mov %eax, %cr3\n\t"

#define IF_FROM_KERNEL_LAND						\
  "mov 48(%esp), %eax\n\t"						\
  "\n\t"\
  ".endif nop\n\t"

#define PUSH_CR3							\
  "mov %cr3, %eax\n\t"							\
  "push %eax\n\t"

#define POP_CR3								\
  "pop %eax\n\t"							\
  "mov %eax, %cr3\n\t"

#define MEMCOPY_TOSTACKINT						\
  "push $40\n\t"							\
  "push global_esp\n\t"					\
  "push gl_stack_int\n\t"						\
  "call memcpy\n\t"							\
  "pop %eax\n\t"							\
  "pop %eax\n\t"							\
  "pop %eax\n\t"



/* memcpy(void*                            dest, */
/*                                const void*                      src, */
/*                                size_t                           n) */
//ao_thread_named;

/*       SET_ESP								\ */
/*       MEMCOPY_TOSTACKINT						\ */
//     PUSH_CR3								\
//      POP_CR3								\

#define MOV_TO(_val_, _reg_)						\
  asm("mov $" _val_ ", %##_reg_")

t_uint32 gl_cr3_dest;

#define __handler__(_id_)						\
  void int_##_id_();							\
  asm(".globl int_" #_id_ "\n\t"					\
      "int_" #_id_ ":\n\t"						\
      SAVE_CONTEXT							\
      PUSH_CR3								\
      ESP2VAR								\
      "push $" #_id_ "\n\t"						\
      "call event_call\n\t"						\
      "addl $4, %esp\n\t"						\
      VAR2ESP								\
      POP_CR3								\
      REST_CONTEXT							\
      "iret")

#define __handler2__(_id_)					       \
  void int_##_id_();						       \
  asm(".globl int_" #_id_ "\n\t"				       \
      "int_" #_id_ ":\n\t"					       \
      SAVE_CONTEXT						       \
      "push $" #_id_ "\n\t"					       \
      "movl %esp, %edi\n\t"					       \
      "call event_call\n\t"					       \
      "addl $4, %esp\n\t"					       \
      REST_CONTEXT						       \
      "iret")

//      "push 40(%esp)\n\t"
#define __handler_error__(_id_)					       \
  void int_##_id_();						       \
  asm(".globl int_" #_id_ "\n\t"				       \
      "int_" #_id_ ":\n\t"					       \
      SAVE_CONTEXT						       \
      "pushl $" #_id_ "\n\t"					       \
      "movl %esp, %edi\n\t"					       \
      "call event_call_error\n\t"				       \
      "addl $4, %esp\n\t"					       \
      REST_CONTEXT						       \
      "iret")

//"push %esp\n\t"						       \
//      "push 40(%esp)\n\t"					       \

/* # define SAVE_CONTEXT()			\ */
/*   asm volatile("push %eax\n\t"		\ */
/*   	       "push %ebx\n\t"		\ */
/*   	       "push %ecx\n\t"		\ */
/*   	       "push %edx\n\t"		\ */
/* 	       "push %esi\n\t"		\ */
/* 	       "push %edi\n\t") */

/* # define RESTORE_CONTEXT()		\ */
/*   asm volatile("pop %edi\n\t"		\ */
/*                "pop %esi\n\t"		\ */
/*                "pop %edx\n\t"		\ */
/*                "pop %ecx\n\t"		\ */
/*                "pop %ebx\n\t"		\ */
/* 	       "pop %eax\n\t") */

# define ADJUST_STACK()			\
  asm volatile("mov %ebp, %esp\n\t"	\
	       "pop %ebp")

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
