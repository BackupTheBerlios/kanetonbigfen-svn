/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/include/core/sched.h
 *
 * created       matthieu bucchianeri   [sat jun  3 22:34:42 2006]
 * updated       matthieu bucchianeri   [wed feb  7 10:57:36 2007]
 */

#ifndef CORE_SCHED_H
#define CORE_SCHED_H	1

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <arch/machdep/machdep.h>
#include <core/id.h>
#include <core/types.h>
#include <core/timer.h>

/*
 * ---------- macros ----------------------------------------------------------
 */

/*
 * this is thread state.
 */

#define SCHED_STATE_RUN			0
#define SCHED_STATE_STOP		1
#define SCHED_STATE_ZOMBIE		2

/*
 * initial value for the scheduler quantum in milliseconds.
 */

#define SCHED_QUANTUM_INIT		5

/*
 * ---------- types -----------------------------------------------------------
 */

/*
 * scheduler manager
 */

typedef struct
{
  i_stats	stats;

  t_quantum	quantum;
  i_thread	current;
  i_set		cpus;
  i_set		threads;
  i_timer	timerid;

  machdep_data(m_sched);
}		m_sched;

/*
 * the scheduler architecture-dependent interface
 */

typedef struct
{
  t_error			(*sched_quantum)(t_quantum);
  t_error			(*sched_yield)(i_cpu);
  t_error			(*sched_switch)(i_thread);
  t_error			(*sched_add)(i_thread);
  t_error			(*sched_remove)(i_thread);
  t_error			(*sched_update)(i_thread);
  t_error			(*sched_init)(void);
  t_error			(*sched_clean)(void);
}				d_sched;

/*
 * ---------- macro functions -------------------------------------------------
 */

/*
 * check
 */

#define SCHED_CHECK(_sched_)						\
  {									\
    if ((_sched_) == NULL)						\
      return (ERROR_UNKNOWN);						\
  }

/*
 * enter
 */

#define SCHED_ENTER(_sched_)						\
  {									\
    SCHED_CHECK((_sched_));						\
									\
    STATS_BEGIN((_sched_)->stats);					\
  }

/*
 * leave
 */

#define SCHED_LEAVE(_sched_, _error_)					\
  {									\
    STATS_END((_sched_)->stats, (_error_));				\
    									\
    return (_error_);							\
  }

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../../core/sched/sched.c
 */

/*
 * ../../core/sched/sched.c
 */

t_error			sched_dump(void);

t_error			sched_quantum(t_quantum quantum);

t_error			sched_current(i_thread*			thread);

t_error			sched_add(i_thread			thread);

t_error			sched_remove(i_thread			thread);

t_error			sched_update(i_thread			thread);

t_error			sched_init(void);

t_error			sched_clean(void);

t_error				sched_switch(void);


/*
 * eop
 */

#endif
