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

// FIXED: lot of code has been removed here

t_error			timer_show(i_timer id)
{
  o_timer*		o;

  TIMER_ENTER(timer);

  /*
   * 1)
   */

  if (timer_get(id, &o) != ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  /*
   * 2)
   */

  cons_msg('#', "  timer %qd: task %qd: delay %qd: repeat %qd\n", o->timerid, o->handler.taskid, o->delay, o->repeat);

  TIMER_LEAVE(timer, ERROR_NONE);
}

t_error			timer_dump(void)
{
  t_state		state;
  o_timer*		data;
  t_setsz		size;
  t_iterator		i;

  TIMER_ENTER(timer);

  /*
   * 1)
   */

  if (set_size(timer->timers, &size) != ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  /*
   * 2)
   */

  cons_msg('#', "dumping %qu timer(s):\n", size);

  set_foreach(SET_OPT_FORWARD, timer->timers, &i, state)
    {
      if (set_object(timer->timers, i, (void**)&data) != ERROR_NONE)
	TIMER_LEAVE(timer, ERROR_UNKNOWN);

      if (timer_show(data->timerid) != ERROR_NONE)
	TIMER_LEAVE(timer, ERROR_UNKNOWN);
    }

  TIMER_LEAVE(timer, ERROR_NONE);
}

t_error			timer_repeat(i_timer id,
				     t_uint32 repeat)
{
  o_timer*		tmp;

if (timer_get(id, &tmp) == ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

 tmp->repeat = repeat;
  TIMER_LEAVE(timer, ERROR_NONE);
}

t_error			timer_modify(i_timer id,
				     t_uint32 delay,
				     t_uint32 repeat)
{
 if (timer_delay(id, delay) == ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

 if (timer_repeat(id, repeat) == ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

TIMER_LEAVE(timer, ERROR_NONE);
}

t_error			timer_delay(i_timer id, t_uint32 delay)
{
  o_timer*		tmp;

  TIMER_ENTER(timer);

  if (timer_get(id, &tmp) == ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  tmp->delay = delay;

TIMER_LEAVE(timer, ERROR_NONE);
}

t_error			timer_get(i_timer id, o_timer** o)
{
  TIMER_ENTER(timer);

  if (set_get(timer->timers, id, (void**)o) != ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  TIMER_LEAVE(timer, ERROR_NONE);
}

t_error			timer_reserve(t_type type,
					      u_timer_handler handler,
					      t_uint32 delay,
					      t_uint32 repeat,
					      i_timer* id)
{
  o_timer*		tmp;
  o_timer		o;

  TIMER_ENTER(timer);

  /*
   * 1)
   */

  if (timer_get(*id, &tmp) == ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  /*
   * 2)
   */

  memset(&o, 0x0, sizeof(o_timer));

 if (id_build(id) != ERROR_NONE)
    {
      cons_msg('!', "timer: unable to initialize the identifier object\n");

      return ERROR_UNKNOWN;
    }

  o.timerid = *id;

  o.type = type;

  o.handler = handler;

  o.delay = delay;

  o,repeat = repeat;
  /*
   * 3)
   */

  if (set_add(timer->timers, &o) != ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  TIMER_LEAVE(timer, ERROR_NONE);

}

t_error			timer_notify(i_timer id)
{
  o_timer*              o;

  TIMER_ENTER(timer);

  /*
   * 1)
   */

  if (timer_get(id, &o) != ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  /*
   * 2)
   */

  /* XXX TIMER message the task ! */

  TIMER_LEAVE(timer, ERROR_NONE);
}

t_error			timer_release(i_timer id)
{
  o_timer*		o;

  TIMER_ENTER(timer);

  /*
   * 1)
   */

  if (timer_get(id, &o) != ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  /*
   * 2)
   */

  if (set_remove(timer->timers, o->timerid) != ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  /*
   * 3)
   */

  if (machdep_call(timer, timer_release, o->timerid) != ERROR_NONE)
    TIMER_LEAVE(timer, ERROR_UNKNOWN);

  TIMER_LEAVE(timer, ERROR_NONE);

}


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

  /*
   * 3)
   */

  if (set_reserve(ll, SET_OPT_ALLOC | SET_OPT_SORT,
		  sizeof(o_timer), &timer->timers) != ERROR_NONE)
    {
      cons_msg('!', "timer: unable to reserve the timer set\n");

      return ERROR_UNKNOWN;
    }

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

