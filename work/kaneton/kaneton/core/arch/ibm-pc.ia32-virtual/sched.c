/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/arch/ibm-pc.ia32-virtual/sched.c
 *
 * created       matthieu bucchianeri   [sat jun  3 22:45:19 2006]
 * updated       matthieu bucchianeri   [wed feb  7 10:47:21 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

/*
 * ---------- extern ----------------------------------------------------------
 */

extern m_sched*		sched;


/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the address space manager dispatch.
 */

d_sched			sched_dispatch =
  {
    ia32_sched_quantum,
    ia32_sched_yield,
    ia32_sched_switch,
    NULL,
    NULL,
    NULL,
    ia32_sched_init,
    NULL,
  };

/*
 * ---------- functions -------------------------------------------------------
 */


// FIXED: lot of code has been removed here
t_error			ia32_sched_quantum(t_quantum quantum)
{
    SCHED_ENTER(sched);

  if (timer_delay(sched->timerid, quantum) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

    SCHED_LEAVE(sched, ERROR_NONE);
}

extern t_uint32 gl_stack_int;

#define MYMEMCPY(src, dst, size) memcpy(dst, src, size)

t_error			ia32_sched_switch(i_thread elected)
{
  printf(".");
  SCHED_ENTER(sched);
  if (elected != 0)
    cons_msg('+', "Switching to Thread %i \n", elected);
  else
    cons_msg('!', "Switching to Kernel Thread \n", elected);
  if (elected == sched->current)
    return ERROR_NONE;
 /*  o_thread* th; */
/*   o_task* otsk; */
/*   o_as*	oas; */
  o_thread *Osrc;
  o_thread *Odest;
  ao_thread_named *src;
  ao_thread_named *dest;
  set_get(sched->threads, sched->current, (void**)&Osrc);
  set_get(sched->threads, elected, (void**)&Odest);
  src = &(Osrc->machdep.named);
  dest = &(Odest->machdep.named);
/*   t_uint32 esp_int = gl_stack_int - STACK_SIZE - 4; */
  t_uint32 esp_src = src->esp + 4;//global_esp - 4;
  t_uint32 esp_dest = dest->esp + 4 - STACK_SIZE;
/*   MYMEMCPY(esp_src, esp_int, STACK_SIZE); //met tout dans la stack int */
  src->esp = global_esp;
  MYMEMCPY((void *)esp_src, src, STACK_SIZE); //sauvegarde le contexte
  asm volatile("mov %0,%%eax\n\t"
	       "mov %%eax, %%cr3"
	       :
	       : "m"(dest->cr3));
  //il faut switcher sur l'as cible
/*   MYMEMCPY(dest, esp_int, STACK_SIZE); //restaure le contexte */
/*   printf("[src=%i|int=%i|dest=%i]", esp_src, esp_int, esp_dest); */
/*   printf("[dest=%i]", esp_dest); */
  global_esp = esp_dest - 4;
  //((char*)(global_esp))[100] = 42;
  //printf("[has set]");
  printf("[leaving]");
  MYMEMCPY(dest, (void *)esp_dest - STACK_SIZE, STACK_SIZE);
  sched->current = elected;
  SCHED_LEAVE(sched, ERROR_NONE);
}


// You have to implement the machine-dependent part doing the context switching.
// The architecture-dependent part of the scheduler is also responsible of
// calling the sched switch periodically. This is typically done with a timer.
// Hint: the special case of the kernel main thread must be considered. The
// scheduler must create a kernel thread (corresponding to the execution context
// in the kernel). Think twice about it, there is a very simple implementation.

// FIXME: lot of code has been removed here


void ia32_sched_yield()
{
  //printf(".");
  //sched_yield(0);
}

t_error ia32_sched_init()
{

  return ERROR_NONE;
}

