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

d_thread			thread_dispatch =
  {

// FIXME: don't forget to fill this structure
/*     NULL, */
/*     NULL, */
/*     NULL, */
/*     NULL, */
/*     NULL, */
/*     NULL, */
/*     NULL, */
/*     NULL, */
/*     NULL, */
/*     NULL, */
/*     ia32_thread_init, */
/*     NULL, */
  };

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

  /*
   * 5)
   */

  if (tss_init(thread->machdep.tss) != ERROR_NONE)
    THREAD_LEAVE(thread, ERROR_UNKNOWN);

  THREAD_LEAVE(thread, ERROR_NONE);
}

