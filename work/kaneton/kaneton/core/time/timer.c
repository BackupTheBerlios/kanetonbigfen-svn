/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/time/timer.c
 *
 * created       renaud voltz   [sun feb 12 23:04:54 2006]
 * updated       matthieu bucchianeri   [wed feb  7 10:38:43 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements the timer manager.
 * a timer is parameterised around three properties: the task it belongs to,
 * its delay and its repeat mode. When its delay (in 1/100 of sec) has expired,
 * a message is sent to the task taskid before behaving as follow:
 * a) if the timer repeat is set to TIMER_REPEAT_ENABLE, the timer is
 *    automaticaly reset to its original delay.
 * b) if the timer repeat is set to TIMER_REPEAT_DISABLE, then the timer is
 *    released.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

machdep_include(timer);

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the timer manager variable.
 */

m_timer*		timer = NULL;

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

/*
 * initialize the timer manager.
 *
 * steps:
 *
 * 1) allocate and initialize the timer manager.
 * 2) initialize the object identifier.
 * 3) try to reserve a statistic object.
 * 4) call the machine dependent code.
 */

t_error			timer_init(void)
{

  /*
   * 1)
   */

  if ((timer = malloc(sizeof(m_timer))) == NULL)
    {
      cons_msg('!', "timer: cannot allocate memory for the timer manager "
               "structure\n");

      return ERROR_UNKNOWN;
    }

  memset(timer, 0x0, sizeof(m_timer));

  /*
   * 2)
   */

  if (id_build(&timer->id) != ERROR_NONE)
    {
      cons_msg('!', "timer: unable to initialize the identifier object\n");

      return ERROR_UNKNOWN;
    }

  timer->timeref = 0;

  /*
   * 3)
   */

  STATS_RESERVE("timer", &timer->stats);

  /*
   * 4)
   */

  if (machdep_call(timer, timer_init) != ERROR_NONE)
    return ERROR_UNKNOWN;

  return ERROR_NONE;
}

/*
 * destroy the timer manager.
 *
 * steps:
 *
 * 1) call the machine dependent code.
 * 2) release the statistics object.
 * 3) destroy the identifier object.
 * 4) free the timer manager's structure memory.
 */

t_error			timer_clean(void)
{
  /*
   * 1)
   */

  if (machdep_call(timer, timer_clean) != ERROR_NONE)
    return ERROR_UNKNOWN;

  /*
   * 2)
   */

  STATS_RELEASE(timer->stats);

  /*
   * 3)
   */

  if (id_destroy(&timer->id) != ERROR_NONE)
    {
      cons_msg('!', "timer: unable to destroy the identifier object\n");

      return ERROR_UNKNOWN;
    }

  /*
   * 4)
   */

  free(timer);

  return ERROR_NONE;
}

