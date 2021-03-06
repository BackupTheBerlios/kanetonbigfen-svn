/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/include/core/message.h
 *
 * created       matthieu bucchianeri   [sat jun 17 19:39:50 2006]
 * updated       matthieu bucchianeri   [wed feb  7 10:56:05 2007]
 */

#ifndef CORE_MESSAGE_H
#define CORE_MESSAGE_H	1

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <arch/machdep/machdep.h>
#include <core/id.h>
#include <core/types.h>

/*
 * ---------- macros ----------------------------------------------------------
 */

/*
 * ---------- types -----------------------------------------------------------
 */

/*
 * message object
 */

typedef struct
{
  // FIXME: think about what is needed here...
}		o_message;

/*
 * message box
 */

typedef struct
{
  // FIXME: think about what is needed here...
}		t_message_box;

/*
 * message manager
 */

typedef struct
{
  i_stats	stats;

  // FIXME: think about what is needed here...

  machdep_data(m_message);
}		m_message;

/*
 * the message architecture-dependent interface
 */

typedef struct
{
  t_error			(*message_init)(void);
  t_error			(*message_clean)(void);

  // XXX this should be patched in the future
}				d_message;

/*
 * ---------- macro functions -------------------------------------------------
 */

/*
 * check
 */

#define MESSAGE_CHECK(_message_)					\
  {									\
    if ((_message_) == NULL)						\
      return (ERROR_UNKNOWN);						\
  }

/*
 * enter
 */

#define MESSAGE_ENTER(_message_)					\
  {									\
    MESSAGE_CHECK((_message_));						\
									\
    STATS_BEGIN((_message_)->stats);					\
  }

/*
 * leave
 */

#define MESSAGE_LEAVE(_message_, _error_)				\
  {									\
    STATS_END((_message_)->stats, (_error_));				\
									\
    return (_error_);							\
  }

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../../core/message/message.c
 */

/*
 * ../../core/message/message.c
 */

t_error			message_init(void);

t_error			message_clean(void);


/*
 * eop
 */

#endif
