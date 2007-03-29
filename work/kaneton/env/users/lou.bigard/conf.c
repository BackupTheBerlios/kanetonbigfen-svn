#include <klibc.h>
#include <kaneton.h>

extern m_region*	region;
extern i_as		kasid;
extern i_task		ktask;

void sched_switch(void)
{
 cons_msg('!', "TIC\n");
}

void		check_tests(void)
{
  i_as		as;
  i_timer		idtimer;

/* if (as_reserve(ktask, &as) != ERROR_NONE) */
/*   cons_msg('+', "AS Reserve failed !\n"); */

if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch),
120, TIMER_REPEAT_ENABLE,
&idtimer) != ERROR_NONE)
   cons_msg('+', "Timer Reserve failed !\n");

if (timer_dump() != ERROR_NONE)
   cons_msg('+', "Timer Dump failed !\n");
  cons_msg('+', "Ending Tests\n");
}
