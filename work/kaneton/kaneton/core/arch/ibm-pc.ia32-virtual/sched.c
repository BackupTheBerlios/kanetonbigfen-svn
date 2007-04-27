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
    NULL,
    ia32_sched_switch,
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

t_error			ia32_sched_switch(i_thread elected)
{
   SCHED_ENTER(sched);

   if (elected == 0)
     cons_msg('!', "Switched to Kernel Thread \n", elected);
   else
     cons_msg('+', "Switched to Thread %i \n", elected);

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

