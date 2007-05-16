/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/arch/ibm-pc.ia32-virtual/thread.c
 *
 * created       renaud voltz   [tue apr  4 03:08:03 2006]
 * updated       matthieu bucchianeri   [wed feb  7 14:32:23 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * XXX THREAD information need to be written.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

/*
 * ---------- extern ----------------------------------------------------------
 */

/*
 * the thread manager.
 */

extern m_thread*	thread;

/*
 * kernel asid
 */

extern i_as		kasid;

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the thread manager dispatch.
 */

// FIXME: don't forget to fill this structure
d_thread			thread_dispatch =
  {
    NULL,//t_error			(*thread_show)(i_thread);
    NULL,/*t_error			(*thread_clone)(i_task,
							i_thread,
							i_thread*);*/
    NULL,//t_error			(*thread_flush)(i_task);
    ia32_thread_load,/*t_error			(*thread_load)(i_thread,
						       t_thread_context);*/
    ia32_thread_store,/*t_error			(*thread_store)(i_thread,
							t_thread_context*);*/
    NULL,/*t_error	(*thread_reserve)(i_task,
							  i_thread*);*/
    NULL,//t_error			(*thread_release)(i_thread);
    NULL,/*t_error			(*thread_priority)(i_thread,
							   t_prior);*/
    NULL,/*t_error			(*thread_state)(i_thread,
							t_state);*/
    NULL,/*t_error			(*thread_stack)(i_thread,
							t_stack);*/
    ia32_thread_init,//t_error	       	(*thread_init)(void);
    NULL //t_error			(*thread_clean)(void);
  };

t_uint32 gl_stack_int;

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

/*
 * initialize the IA-32 related structures for the thread manager.
 *
 * steps:
 *
 * 1) get the kernel address space.
 * 2) reserve some memory for the TSS.
 * 3) reserve 2 pages for the interrupt stack. this stack is
 *    automatically setup by the processor on privilege level switch.
 * 4) load the interrupt stack and the I/O bitmap base into the TSS.
 * 5) activate the TSS.
 */

t_error			ia32_thread_init(void)
{
  THREAD_ENTER(thread);

  o_as*			as;
  t_vaddr		int_stack;

  /*
   * 1)
   */

  if (as_get(kasid, &as) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 2)
   */

  if (map_reserve(kasid,
		  MAP_OPT_PRIVILEGED,
		  3 * PAGESZ,
		  PERM_READ | PERM_WRITE,
		  (t_vaddr*)&thread->machdep.tss) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

      memset(thread->machdep.tss, 0x0, sizeof(t_ia32_tss));

  /*
   * 3)
   */

  if (map_reserve(kasid,
		  MAP_OPT_PRIVILEGED,
		  2 * PAGESZ,
		  PERM_READ | PERM_WRITE,
		  &int_stack) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  /*
   * 4)
   */

  if (tss_load(thread->machdep.tss,
	       SEGSEL(PMODE_GDT_CORE_DS, PRIV_RING0),
	       int_stack + 2 * PAGESZ - 16,
	       0x68) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  gl_stack_int = int_stack + 2 * PAGESZ - 16;

  /*
   * 5)
   */

  if (tss_init(thread->machdep.tss) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

/* thread stack */
/* thread load */
/* thread store */

t_error ia32_thread_load(i_thread thr,t_thread_context ctx)
{
  o_thread* o;
  thread_get(thr, &o);
  o->machdep.named.esp = ctx.sp;
  //printf("[%i", o->machdep.named.esp = ctx.sp);
  //printf("@%i]\n", &(o->machdep.named));
  o->machdep.named.eip = ctx.pc;
  gdt_build_selector(PMODE_GDT_CORE_CS, ia32_prvl_supervisor, &o->machdep.named.cs);
  return ERROR_NONE;
}

t_error ia32_thread_store(i_thread thr, t_thread_context* ctx)
{
  o_thread* o;
  thread_get(thr, &o);
  ctx->sp = o->machdep.named.esp;
  ctx->pc = o->machdep.named.eip;
  return ERROR_NONE;
}
