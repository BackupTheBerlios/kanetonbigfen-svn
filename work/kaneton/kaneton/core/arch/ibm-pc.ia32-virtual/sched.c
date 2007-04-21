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
    ia32_sched_quantum, //t_error			(*sched_quantum)(t_quantum);
    NULL, //t_error			(*sched_yield)(i_cpu);
    NULL, //t_error			(*sched_switch)(i_thread);
    NULL, //t_error			(*sched_add)(i_thread);
    NULL, //t_error			(*sched_remove)(i_thread);
    NULL, //t_error			(*sched_update)(i_thread);
    ia32_sched_init, //t_error		(*sched_init)(void);
    NULL, //t_error			(*sched_clean)(void);
  };

/*
 * ---------- functions -------------------------------------------------------
 */

// You have to implement the machine-dependent part doing the context switching.
// The architecture-dependent part of the scheduler is also responsible of
// calling the sched switch periodically. This is typically done with a timer.
// Hint: the special case of the kernel main thread must be considered. The
// scheduler must create a kernel thread (corresponding to the execution context
// in the kernel). Think twice about it, there is a very simple implementation.

// FIXME: lot of code has been removed here

t_error ia32_sched_quantum()
{
  return ERROR_NONE;
}

t_error ia32_sched_switch(i_thread i)
{
  // does the context switching
  return ERROR_NONE;
}

void ia32_sched_yield()
{
  printf(".");
  //sched_yield(0);
}

t_error ia32_sched_init()
{
  i_timer res = 42;
  timer_reserve(EVENT_FUNCTION,
		TIMER_HANDLER(ia32_sched_yield),
		1,
		TIMER_REPEAT_ENABLE, &res);
  return ERROR_NONE;
}
