#include <klibc.h>
#include <kaneton.h>

extern m_region*	region;
extern i_as		kasid;
extern i_task		ktask;

/* void sched_switch(void) */
/* { */
/*  cons_msg('!', "TIC\n"); */
/* } */

void		check_tests(void)
{
  i_as			as;
  i_timer		idtimer;
  i_timer		idtimer2;
  o_timer*		tmp;
  i_task		*taskid;
  i_thread		thre1;

  if (task_reserve(TASK_CLASS_PROGRAM, TASK_BEHAV_TIMESHARING, TASK_PRIOR_TIMESHARING, taskid) != ERROR_NONE)
    cons_msg('+', "TASK Reserve failed !\n");

/*   if (as_reserve(*taskid, &as) != ERROR_NONE) */
/*     cons_msg('+', "AS Reserve failed !\n"); */
  thread_reserve(*taskid, 150, &thre1);

  if (sched_add(thre1) != ERROR_NONE);
    cons_msg('+', "SCHED Add failed !\n");

  if (task_state(*taskid, SCHED_STATE_RUN) != ERROR_NONE)
    cons_msg('+', "TASK Run failed !\n");

  task_dump();
  thread_dump();
/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 120, TIMER_REPEAT_ENABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 125, TIMER_REPEAT_ENABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 156, TIMER_REPEAT_DISABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 20, TIMER_REPEAT_ENABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 20, TIMER_REPEAT_ENABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_dump() != ERROR_NONE) */
/*    cons_msg('+', "Timer Dump failed !\n"); */

/* if (timer_show(idtimer)  != ERROR_NONE) */
/*    cons_msg('+', "Timer Show failed !\n"); */

/* if (timer_get(idtimer, &tmp)  != ERROR_NONE) */
/*    cons_msg('+', "Timer Get failed !\n"); */



  cons_msg('+', "Ending Tests\n");
}
