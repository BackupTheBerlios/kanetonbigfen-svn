/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/sched/sched.c
 *
 * created       matthieu bucchianeri   [sat jun  3 22:36:59 2006]
 * updated       matthieu bucchianeri   [wed feb  7 15:10:15 2007]
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

machdep_include(sched);

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * scheduler manager variable.
 */

m_sched*		sched = NULL;

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

t_error			sched_current(i_thread*			thread)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			sched_add(i_thread			thread)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			sched_remove(i_thread			thread)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			sched_update(i_thread			thread)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

/*
 * this function initialises the scheduler manager.
 *
 * steps:
 *
 * 1) allocate and initialises the scheduler manager structure.
 * 2) try to reserve a statistics object.
 * 3) call the machine-dependent code.
 */

t_error			sched_init(void)
{
  /*
   * 1)
   */

  if ((sched = malloc(sizeof(m_sched))) == NULL)
    {
      cons_msg('!', "sched: cannot allocate memory for the scheduler "
	       "manager structure\n");

      return (ERROR_UNKNOWN);
    }

  memset(sched, 0x0, sizeof(m_sched));

  sched->quantum = SCHED_QUANTUM_INIT;
  sched->cpus = ID_UNUSED;

  /*
   * 2)
   */

  STATS_RESERVE("sched", &sched->stats);

  /*
   * 3)
   */

  if (machdep_call(sched, sched_init) != ERROR_NONE)
    return (ERROR_UNKNOWN);

  return (ERROR_NONE);
}

/*
 * this function just reinitialises the scheduler manager.
 *
 * steps:
 *
 * 1) call the machine-dependent code.
 * 2) release the stats object.
 * 3) free the scheduler manager structure's memory.
 */

t_error			sched_clean(void)
{
  /*
   * 1)
   */

  if (machdep_call(sched, sched_clean) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

  /*
   * 2)
   */

  STATS_RELEASE(sched->stats);

  /*
   * 3)
   */

  free(sched);

  return (ERROR_NONE);
}

