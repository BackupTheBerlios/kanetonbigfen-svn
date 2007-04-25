/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/arch/ibm-pc.ia32-virtual/timer.c
 *
 * created       renaud voltz   [tue feb 28 02:24:05 2006]
 * updated       matthieu bucchianeri   [wed feb  7 10:48:38 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements dependant code for the timer managment on ia32 with
 * paging architecture.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

/*
 * ---------- externs ---------------------------------------------------------
 */

extern m_timer*		timer;

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the ia32 timer manager dispatch.
 */
/* typedef struct */
/* { */

/* }				d_timer; */
d_timer				timer_dispatch =
  {
    NULL, /*   t_error			(*timer_show)(i_timer); */
    NULL, /*   t_error			(*timer_delay)(i_timer, */
    /* 					       t_uint32); */
    NULL, /*   t_error			(*timer_repeat)(i_timer, */
    /* 						t_uint32); */
    NULL, /*   t_error			(*timer_modify)(i_timer, */
    /* 						t_uint32, */
    /* 						t_uint32); */
    NULL, /*   t_error			(*timer_notify)(i_timer); */
    NULL, /*   t_error			(*timer_reserve)(t_type, */
    /*	 						 u_timer_handler, */
    /* 						 t_uint32, */
    /* 						 t_uint32, */
    /* 						 i_timer*); */
    NULL, /*   t_error			(*timer_release)(i_timer); */
    ia32_timer_init, /*   t_error			(*timer_init)(void); */
    NULL  /*   t_error			(*timer_clean)(void); */
  };

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

/* #define TIMER_REPEAT_DISABLE    0 */
/* #define TIMER_REPEAT_ENABLE     1 */

void ia32_timer_tick()
{
  t_state		state;
  o_timer*		timer_elt;
  t_iterator		i;
  t_setsz		size;

  if (set_size(timer->timers, &size) != ERROR_NONE)
    return;
  set_foreach(SET_OPT_FORWARD, timer->timers, &i, state)
  {
    if (set_object(timer->timers, i, (void**)&timer_elt) != ERROR_NONE)
      return;
    if (timer_elt->type == EVENT_FUNCTION)
      {
	if (timer->timeref == timer_elt->next)
	  {
	    ((t_timer_handler)timer_elt->handler.function)();
	    if (timer_elt->repeat == TIMER_REPEAT_ENABLE)
	      timer_elt->next += timer_elt->delay;
	    else
	      timer_release(timer_elt->timerid);
	  }
      }
  }
  timer->timeref++;
}

t_error ia32_timer_init()
{
  ia32_pit_init();
  //  return event_reserve(32+0, EVENT_FUNCTION, EVENT_HANDLER(ia32_timer_tick));
  return ERROR_NONE;
}
