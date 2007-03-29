/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/include/arch/machdep/core/core.h
 *
 * created       julien quintard   [sat dec 17 17:13:18 2005]
 * updated       matthieu bucchianeri   [wed feb  7 11:18:29 2007]
 */

#ifndef IA32_CORE_CORE_H
#define IA32_CORE_CORE_H	1

/*
 * ---------- macros ----------------------------------------------------------
 */

#define ___endian		ENDIAN_LITTLE
#define ___wordsz		WORDSZ_32

#define PAGESZ			4096

/*
 * ---------- includes --------------------------------------------------------
 */

#include <arch/machdep/core/as.h>
#include <arch/machdep/core/debug.h>
#include <arch/machdep/core/init.h>
#include <arch/machdep/core/region.h>
#include <arch/machdep/core/segment.h>
#include <arch/machdep/core/stats.h>
#include <arch/machdep/core/event.h>
#include <arch/machdep/core/timer.h>
#include <arch/machdep/core/thread.h>
#include <arch/machdep/core/task.h>
#include <arch/machdep/core/sched.h>
#include <arch/machdep/core/message.h>
#include <arch/machdep/core/cpu.h>

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../../../../core/arch/machdep/as.c
 *      ../../../../core/arch/machdep/region.c
 *      ../../../../core/arch/machdep/segment.c
 *      ../../../../core/arch/machdep/event.c
 *	../../../../core/arch/machdep/timer.c
 *      ../../../../core/arch/machdep/task.c
 *      ../../../../core/arch/machdep/thread.c
 *      ../../../../core/arch/machdep/sched.c
 *      ../../../../core/arch/machdep/message.c
 *      ../../../../core/arch/machdep/cpu.c
 */

/*
 * ../../../../core/arch/machdep/as.c
 */

t_error			ia32_as_show(i_as			asid);

t_error			ia32_as_reserve(i_task			tskid,
					i_as*			asid);


/*
 * ../../../../core/arch/machdep/region.c
 */

t_error			map_page(t_paddr paddr, t_vaddr *vaddr);

t_error			ia32_region_reserve(i_as			asid,
					i_segment		segid,
				     	t_paddr			offset,
				     	t_opts			opts,
				     	t_vaddr			address,
				     	t_vsize			size,
				     	i_region*		regid);

t_error			ia32_region_release(i_as			asid,
					    i_region			regid);

t_error			ia32_region_init(t_vaddr		start,
					 t_vsize		size);

t_error			ia32_region_clean(void);


/*
 * ../../../../core/arch/machdep/segment.c
 */

t_error                 ia32_segment_read(i_segment id,
					  t_paddr offset,
					  void* buffer,
					  t_psize size);

t_error			ia32_segment_write(i_segment id,
					   t_paddr offset,
					   const void* buffer,
					   t_psize size);

t_error			ia32_segment_copy(i_segment dst,
					  t_paddr offd,
					  i_segment src,
					  t_paddr offs,
					  t_psize size);

t_error			ia32_segment_init(void);

t_error			ia32_segment_clean(void);


/*
 * ../../../../core/arch/machdep/event.c
 */

t_error ia32_event_init(void);

t_error			ia32_event_reserve(i_event		id,
					   t_uint32		type,
					   t_uint32		handler);

t_error			ia32_event_release(i_event id);


/*
 * ../../../../core/arch/machdep/timer.c
 */


/*
 * ../../../../core/arch/machdep/task.c
 */

t_error			ia32_task_clone(i_task			old,
					i_task*			new);

t_error			ia32_task_reserve(t_class			class,
					  t_behav			behav,
					  t_prior			prior,
					  i_task*			id);

t_error			ia32_task_init(void);


/*
 * ../../../../core/arch/machdep/thread.c
 */

t_error			ia32_thread_init(void);


/*
 * ../../../../core/arch/machdep/sched.c
 */


/*
 * ../../../../core/arch/machdep/message.c
 */


/*
 * ../../../../core/arch/machdep/cpu.c
 */

t_error			ia32_cpu_current(i_cpu*			cpuid);


/*
 * eop
 */

#endif
