/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/region/region-fit.c
 *
 * created       matthieu bucchianeri   [tue jan 10 01:28:36 2006]
 * updated       matthieu bucchianeri   [wed feb  7 15:10:59 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements simple  fitting algorithms for virtual memory
 * management.
 *
 * you can define which algorithm to use with the macro REGION_FIT.
 *
 *  - FIT_FIRST: first fit algorithm - the first large enough space is taken
 *  - FIT_BEST: best fit algorithm - the smaller space is taken
 *  - ...
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

machdep_include(region);

/*
 * ---------- extern ----------------------------------------------------------
 */

/*
 * the region manager structure.
 */

extern m_region*       region;

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: some code has been removed here

/*
 * this function calls the good algorithm.
 */

t_error			region_space(o_as*		as,
				     t_vsize		size,
				     t_vaddr*		address)
{
  REGION_ENTER(region);

  switch (region->lookup)
    {
      case FIT_FIRST:
	{
	  // FIXME: call you first-fit algorithm here

	  break;
	}
      default:
	REGION_LEAVE(region, ERROR_UNKNOWN);
    }
}
