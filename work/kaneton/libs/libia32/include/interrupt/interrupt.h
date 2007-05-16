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

#define REST_CONTEXT							\
  "pop %eax\n\t"							\
  "mov %eax, %cr3\n\t"							\
  "pop %ebp\n\t"							\
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
  "push %edi\n\t"							\
  "push %ebp\n\t"							\
  "mov %cr3, %eax\n\t"							\
  "push %eax\n\t"

#define CTX_SIZE ( 10 * 4 )
#define STACK_SIZE ( CTX_SIZE + 3 * 4 )

#define ESP2VAR								\
  "mov %esp, global_esp\n\t"

#define VAR2ESP								\
  "mov global_esp, %esp\n\t"

#define PUSH_CR3							\
  "mov %cr3, %eax\n\t"							\
  "push %eax\n\t"

#define POP_CR3								\
  "pop %eax\n\t"							\
  "mov %eax, %cr3\n\t"

#define MOV_TO(_val_, _reg_)						\
  asm("mov $" _val_ ", %##_reg_")

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

# define ADJUST_STACK()			\
  asm volatile("mov %ebp, %esp\n\t"	\
	       "pop %ebp")

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
