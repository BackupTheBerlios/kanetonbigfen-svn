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

// FIXED: lot of code has been removed here
t_error			sched_dump(void)
{
  t_state		state;
  o_as*			o;
  o_thread*		data;
  t_setsz		size;
  t_iterator		i;

  SCHED_ENTER(sched);

cons_msg('#', "----[ SCHEDULER Dump ]----\n");
cons_msg('#', "- Quantum : %qd          -\n", sched->quantum);
cons_msg('#', "- Current thread : %qd   -\n", sched->current);
cons_msg('#', "- Timerid : %qd          -\n", sched->timerid);

    if (set_size(sched->threads, &size) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

  /*
   * 2)
   */

  cons_msg('#', "dumping %qu thread(s):\n", size);

  set_foreach(SET_OPT_FORWARD, sched->threads, &i, state)
    {
      if (set_object(sched->threads, i, (void**)&data) != ERROR_NONE)
	SCHED_LEAVE(sched, ERROR_UNKNOWN);

      if (thread_show(data->threadid) != ERROR_NONE)
	SCHED_LEAVE(sched, ERROR_UNKNOWN);
    }

  SCHED_LEAVE(sched, ERROR_NONE);
}

t_error			sched_quantum(t_quantum quantum)
{
  SCHED_ENTER(sched);

  sched->quantum = quantum;

  SCHED_LEAVE(sched, ERROR_NONE);
}

t_error			sched_current(i_thread*			thread)
{
  SCHED_ENTER(sched);
  // FIXED: some code was removed here
  *thread = sched->current;

  SCHED_LEAVE(sched, ERROR_NONE);
}

t_error			sched_add(i_thread			thread)
{
  // FIXED: some code was removed here
  o_thread*			th;

  SCHED_ENTER(sched);

 if (thread_get(thread, &th) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

 /*
  * Add the thread
  */
  if (set_add(sched->threads, (void*)th) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

  SCHED_LEAVE(sched, ERROR_NONE);
}

t_error			sched_remove(i_thread			thread)
{
  // FIXED: some code was removed here
  SCHED_LEAVE(sched, ERROR_NONE);

  if (set_remove(sched->threads, thread) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

  SCHED_LEAVE(sched, ERROR_NONE);
}

t_error			sched_update(i_thread			thread)
{
  // FIXED: some code was removed here
  o_thread*			th;
  o_thread*			sched_th;

  SCHED_ENTER(sched);

  if (thread_get(thread, &th) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

  if (set_get(sched->threads, thread, (void**)&sched_th) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

  /*
   * Updating fields
   */

  sched_th->threadid = th->threadid;
  sched_th->taskid = th->taskid;
  sched_th->prior = th->prior;
  sched_th->sched = th->sched;
  sched_th->wait = th->wait;
  sched_th->stack = th->stack;
  sched_th->stacksz = th->stacksz;

  SCHED_LEAVE(sched, ERROR_NONE);
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
  if (set_reserve(ll, SET_OPT_ALLOC, sizeof(o_thread), &sched->threads)
      != ERROR_NONE)
    {
      cons_msg('!', "sched: unable to reserve the threads set\n\n");
      return ERROR_UNKNOWN;
    }

  /*
   * Reserve timer
   */
  if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch),
		    sched->quantum, TIMER_REPEAT_ENABLE,
		    &sched->timerid) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

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

t_error				sched_switch(void)
{
  t_state		state;
  o_thread*		data;
  t_setsz		size;
  t_iterator		i;
  i_thread		max_thread;
  t_prior		max_prior;
  o_thread*		th;

 SCHED_ENTER(sched);

  if (set_size(sched->threads, &size) != ERROR_NONE)
    SCHED_LEAVE(region, ERROR_UNKNOWN);

  /*
   * 1)
   */

  set_foreach(SET_OPT_FORWARD, sched->threads, &i, state)
    {
      if (set_object(sched->threads, i, (void**)&data) != ERROR_NONE)
	{
	  cons_msg('!', "sched: cannot find the sched object "
		   "corresponding to its identifier\n");

	  SCHED_LEAVE(sched, ERROR_UNKNOWN);
	}

      /*
       * Selecta
       */
      if (data->prior >= max_prior)
	{
	max_thread = data->threadid;
      max_prior = data->prior;
	}
      /*
       * Ageing
       */
      data->prior += 1;
    }

  /*
   * Pull Up !
   */
  sched->current = max_thread;

 if (thread_get(sched->current, &th) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);
 th->prior = th->init_prior;

  if (machdep_call(sched, sched_switch, sched->current) != ERROR_NONE)
    SCHED_LEAVE(sched, ERROR_UNKNOWN);

  SCHED_LEAVE(sched, ERROR_NONE);
}
