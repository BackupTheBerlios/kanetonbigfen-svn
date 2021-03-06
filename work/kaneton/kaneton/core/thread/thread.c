/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/thread/thread.c
 *
 * created       renaud voltz   [tue apr  4 03:02:57 2006]
 * updated       matthieu bucchianeri   [wed feb  7 18:21:42 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements the thread manager.
 * a thread objecct contains:
 *  - an execution context (architecture-depedent)
 *  - information relevant to its own stack
 *  - scheduling information (state, priority within the task)
 *
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

machdep_include(thread);

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the thread manager variable.
 */

m_thread*		thread = NULL;

/*
 * ---------- functions -------------------------------------------------------
 */

/*
 * this function shows a given thread.
 *
 * steps:
 *
 * 1) get the thread object from its identifier.
 * 2) display the thread information.
 * 3) call the machine-dependent code.
 */

t_error			thread_show(i_thread			threadid)
{
  o_thread*		o;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  if (thread_get(threadid, &o) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  cons_msg('#', " thread %qd in task %qd:\n",
	   o->threadid,
	   o->taskid);

  cons_msg('#', " priority : %i initial[%i]\n",
	   o->prior,
	   o->init_prior);

  cons_msg('#', " sched : %qd | wait : %qd\n",
	   o->sched,
	   o->wait);

  cons_msg('#', " stack : 0x%08x | stack size : %qd\n\t---------------------\n",
	   o->stack,
	   o->stacksz);

  /*
   * 3)
   */

  if (machdep_call(thread, thread_show, threadid) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * this function dumps the thread manager.
 *
 * steps:
 *
 * 1) get the set size.
 * 2) show each thread.
 */

t_error			thread_dump(void)
{
  t_state		state;
  o_thread*		data;
  t_setsz		size;
  t_iterator		i;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  if (set_size(thread->threads, &size) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  cons_msg('#', "dumping %qu thread(s):\n");

  set_foreach(SET_OPT_FORWARD, thread->threads, &i, state)
    {
      if (set_object(thread->threads, i, (void**)&data) != ERROR_NONE)
	THREAD_LEAVE(thread, ERROR_UNKNOWN);

      if (thread_show(data->threadid) != ERROR_NONE)
	THREAD_LEAVE(thread, ERROR_UNKNOWN);
    }

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * clone a thread.
 * the clone is added to the specified task.
 *
 * 1) get the thread to clone.
 * 2) reserve the clone objet.
 * 3) copy data from the original thead to the new one.
 * 4) copy the waits set from the original thread to the new one.
 * 5) call the machine-dependent code.
 */

t_error			thread_clone(i_task			taskid,
				     i_thread			old,
				     i_thread*			new)
{
  o_thread*		from;
  o_thread*		to;
  t_state		state;
  t_iterator		i;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  if (thread_get(old, &from) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  if (thread_reserve(taskid, from->prior, new) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 3)
   */

  // XXX do reserve !

  to->sched = from->sched;

  to->wait = from->wait;

  to->stack = from->stack;
  to->stacksz = from->stacksz;

  /*
   * 4)
   */

  set_foreach(SET_OPT_FORWARD, from->waits, &i, state)
    {
      i_thread*		data;

      if (set_object(from->waits, i, (void**)&data) != ERROR_NONE)
	{
	  cons_msg('!', "thread: cannot find the object "
		   "corresponding to its identifier\n");

	  THREAD_LEAVE(thread, ERROR_UNKNOWN);
	}

      if (set_add(to->waits, data) != ERROR_NONE)
	THREAD_LEAVE(thread, ERROR_UNKNOWN);
    }

  /*
   * 5)
   */

  if (machdep_call(thread, thread_clone, taskid, old, new) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * this function reserves a thread for a given task.
 *
 * steps:
 *
 * 1) sanity checks.
 * 2) get the task object.
 * 3) reserve an id for the new thread and fill its information.
 * 4) fill thread information.
 * 5) add the new thread in the thread container and in the task threads list.
 * 6) call the machine-dependent code.
 */

t_error			thread_reserve(i_task			taskid,
				       t_prior			prior,
				       i_thread*		threadid)
{
  o_task*		task;
  o_thread		o;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  if (prior < THREAD_LPRIOR || prior > THREAD_HPRIOR)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  if (task_get(taskid, &task) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 3)
   */

  if (id_reserve(&thread->id, threadid) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 4)
   */

  memset(&o, 0x0, sizeof(o_thread));

  o.threadid = *threadid;
  o.taskid = taskid;
  o.prior = prior;
  o.init_prior = prior;
  o.sched = SCHED_STATE_STOP;
  o.waits = ID_UNUSED; // XXX

  /*
   * 5)
   */

  if (set_add(thread->threads, &o) != ERROR_NONE)
    {
      id_release(&thread->id, o.threadid);

      THREAD_LEAVE(thread, ERROR_UNKNOWN);
    }

  if (set_add(task->threads, &o.threadid) != ERROR_NONE)
    {
      set_remove(thread->threads, o.threadid);

      id_release(&thread->id, o.threadid);

      THREAD_LEAVE(thread, ERROR_UNKNOWN);
    }

  /*
   * 6)
   */

  if (machdep_call(thread, thread_reserve, taskid, threadid) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * this function releases a thread from a given task.
 *
 * steps:
 *
 * 1) call the machine-dependent code.
 * 2) get the thread object.
 * 3) get the task object.
 * 4) release the thread stack if needed.
 * 5) release the thread-s object identifer.
 * 6) remove the thread from the task threads list.
 * 7) remove the thread from the threads set.
 */

t_error			thread_release(i_thread			threadid)
{
  o_task*		task;
  o_thread*		o;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  if (machdep_call(thread, thread_release, threadid) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  if (thread_get(threadid, &o) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 3)
   */

  if (task_get(o->taskid, &task) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 4)
   */

  if (o->stack)
    {
      if (map_release(task->asid, o->stack) != ERROR_NONE)
	THREAD_LEAVE(thread, ERROR_UNKNOWN);
    }

  /*
   * 5)
   */

  if (id_release(&thread->id, o->threadid) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 6)
   */

  if (set_remove(task->threads, threadid) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 7)
   */

  if (set_remove(thread->threads, threadid) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * update the thread priority
 *
 * steps:
 *
 * 1) sanity checs.
 * 2) get the thread object from the thread container.
 * 3) update the priority if needed.
 * 4) call the machine-dependent code.
 * 5) call the scheduler to update its internal data.
 */

t_error			thread_priority(i_thread		threadid,
					t_prior			prior)
{
  o_thread*		o;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  if (prior < THREAD_LPRIOR || prior > THREAD_HPRIOR)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  if (thread_get(threadid, &o) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 3)
   */

  if (o->prior == prior)
    THREAD_LEAVE(thread, ERROR_NONE);

  o->prior = prior;

  /*
   * 4)
   */

  if (machdep_call(thread, thread_priority, threadid, prior) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 5)
   */

  if (o->sched == SCHED_STATE_RUN)
    if (sched_update(threadid) != ERROR_NONE)
      THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * update the thread state.
 *
 * steps:
 *
 * 1) check wether the requested state is valid.
 * 2) get the thread object from the thread container.
 * 3) update the thread state if needed.
 * 4) XXX
 * 5) call the machine-dependent code.
 * 6) call the scheduler to schedule or cancel the thread.
 */

t_error			thread_state(i_thread			threadid,
				     t_state			sched)
{
  o_thread*		o;
  t_state		wakeup;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  switch(sched)
    {
      case SCHED_STATE_RUN:
	wakeup = WAIT_START;
	break;
      case SCHED_STATE_STOP:
	wakeup = WAIT_STOP;
	break;
      case SCHED_STATE_ZOMBIE:
	wakeup = WAIT_DEATH;
	break;
      default:
	THREAD_LEAVE(thread, ERROR_UNKNOWN);
    }

  /*
   * 2)
   */

  if (thread_get(threadid, &o) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 3)
   */

  if (o->sched == sched)
    THREAD_LEAVE(thread, ERROR_NONE);

  o->sched = sched;

  /*
   * 4)
   */
/*
  set_foreach(SET_OPT_FORWARD, o->waits, &i, state)
    {
      o_waitfor*	w;

      if (set_object(o->waits, i, (void**)&w) != ERROR_NONE)
	{
	  cons_msg('!', "thread: cannot find the object "
		   "corresponding to its identifier\n");

	  THREAD_LEAVE(thread, ERROR_UNKNOWN);
	}

      if (w->opts & wakeup)
	thread_state(w->u.thread, SCHED_STATE_RUN);
    }
*/
  /*
   * 5)
   */

  if (machdep_call(thread, thread_state, threadid, sched) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 6)
   */

  switch(sched)
    {
      case SCHED_STATE_RUN:
	if (sched_add(threadid) != ERROR_NONE)
	  THREAD_LEAVE(thread, ERROR_UNKNOWN);
	break;
      case SCHED_STATE_STOP:
	if (sched_remove(threadid) != ERROR_NONE)
	  THREAD_LEAVE(thread, ERROR_UNKNOWN);
	break;
      case SCHED_STATE_ZOMBIE:
	/* XXX */
	break;
    }

//  printf("thread %qd is %s\n", threadid, sched == SCHED_STATE_STOP ? "stopping" : "starting");

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * allocate the thread stack.
 *
 * steps:
 *
 * 1) check wether the stack is large enough.
 * 2) get the thread object from the threads container.
 * 3) get the task owning the thread.
 * 3) allocate the thread stack in the task address space.
 * 4) call the machine-dependent code.
 */

t_error			thread_stack(i_thread			threadid,
				     t_stack			stack)
{
  o_thread*		o;
  o_task*		task;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  if (stack.size < THREAD_MIN_STACKSZ)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  if (thread_get(threadid, &o) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 3)
   */

  if (task_get(o->taskid, &task) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 4)
   */

  if (!stack.base)
    {
      if (map_reserve(task->asid,
		      MAP_OPT_NONE | (task->class == TASK_CLASS_CORE ? MAP_OPT_PRIVILEGED : MAP_OPT_USER),
		      stack.size,
		      PERM_READ | PERM_WRITE,
		      &(o->stack)) != ERROR_NONE)
	THREAD_LEAVE(thread, ERROR_UNKNOWN);
      printf("[%i ]", o->stack);
    }
  else
    o->stack = stack.base;

  o->stacksz = stack.size;

  /*
   * 5)
   */

  if (machdep_call(thread, thread_stack, threadid, stack) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}


/*
 * this function removes every thread that belongs to the specified task.
 *
 * steps:
 *
 * 1) call the machine-dependent code.
 * 2) gets the task object from its identifier.
 * 3) for every thread belonging to the task, release it.
 */

t_error			thread_flush(i_task			taskid)
{
  i_thread*		data;
  o_task*		task;
  t_iterator		i;

  THREAD_ENTER(thread);

  /*
   * 1)
   */

  if (machdep_call(thread, thread_flush, taskid) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  if (task_get(taskid, &task) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 3)
   */

  while (set_head(task->threads, &i) == ERROR_NONE)
    {
      if (set_object(task->threads, i, (void**)&data) != ERROR_NONE)
	{
	  cons_msg('!', "thread: cannot find the object "
		   "corresponding to ist identifier\n");

	  THREAD_LEAVE(thread, ERROR_UNKNOWN);
	}
      if (thread_release(*data) != ERROR_NONE)
	THREAD_LEAVE(thread, ERROR_UNKNOWN);
    }

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * this function loads a new execution context in the thread object.
 */

t_error			thread_load(i_thread			threadid,
				    t_thread_context		context)
{
  THREAD_ENTER(thread);

  if (machdep_call(thread, thread_load, threadid, context) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * this fonction stores the thread execution context.
 */

t_error			thread_store(i_thread			threadid,
				     t_thread_context*		context)
{
  THREAD_ENTER(thread);

  if (machdep_call(thread, thread_store, threadid, context) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * this function gets an thread object from the thread container.
 */

t_error			thread_get(i_thread			threadid,
				   o_thread**			o)
{
  THREAD_ENTER(thread);

  if (set_get(thread->threads, threadid, (void**)o) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/*
 * initialise the thread manager.
 *
 * steps:
 *
 * 1) allocate and initialise the thread manager.
 * 2) initialise the object identifier.
 * 3) reserve the thread set.
 * 4) try to reserve a statistic object.
 * 5) call the machine-dependent code.
 * 6) dump the thread manager if debug is enabled.
 */

t_error			thread_init(void)
{
  /*
   * 1)
   */

  if ((thread = malloc(sizeof(m_thread))) == NULL)
    {
      cons_msg('!', "thread: cannot allocate memory "
	       "for the thread manager structure\n");

      return ERROR_UNKNOWN;
    }

  memset(thread, 0x0, sizeof(m_thread));

  /*
   * 2)
   */

  if (id_build(&thread->id) != ERROR_NONE)
    {
      cons_msg('!', "thread: unable to initialise the identifier object\n");

      return ERROR_UNKNOWN;
    }


  /*
   * 3)
   */

  if (set_reserve(ll, SET_OPT_ALLOC, sizeof(o_thread), &thread->threads)
      != ERROR_NONE)
    {
      cons_msg('!', "thread: unable to reserve the thread set\n\n");

      return ERROR_UNKNOWN;
    }

  /*
   * 4)
   */

  STATS_RESERVE("thread", &thread->stats);

  /*
   * 5)
   */

  if (machdep_call(thread, thread_init) != ERROR_NONE)
    return ERROR_UNKNOWN;

  /*
   * 6)
   */

#if (DEBUG & DEBUG_THREAD)
  if (thread_dump() != ERROR_NONE)
    return ERROR_UNKNOWN;
#endif

  return ERROR_NONE;
}

/*
 * destroy the thread manager.
 *
 * steps:
 *
 * 1) call the machine-dependent code.
 * 2) release the statistics object.
 * 3) release every thread object.
 * 4) destroy the identifier object.
 * 5) free the thread manager's structure memory.
 */

t_error			thread_clean(void)
{
  /*
   * 1)
   */

  if (machdep_call(thread, thread_clean) != ERROR_NONE)
    return ERROR_UNKNOWN;

  /*
   * 2)
   */

  STATS_RELEASE(thread->stats);

  /*
   * 3)
   */

  if (set_release(thread->threads) != ERROR_NONE)
    {
      cons_msg('!', "thread: unable to release the thread set\n");

      return ERROR_UNKNOWN;
    }

  /*
   * 4)
   */

  if (id_destroy(&thread->id) != ERROR_NONE)
    {
      cons_msg('!', "thread: unable to destroy the identifier object\n");

      return ERROR_UNKNOWN;
    }

  /*
   * 5)
   */

  free(thread);

  return ERROR_NONE;
}
