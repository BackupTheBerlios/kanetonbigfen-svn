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


t_error			region_add_sorted(	o_as*	as,
					  	t_vaddr begin,
					   	t_vaddr end)
{
	t_iterator	i;
	t_state		state;
	i_set		set	=	as->regions;		//oregion busymap list
	o_region*	oreg_f	=	malloc(sizeof(o_region));	//oregion busymap object
	o_region*	oreg	=	NULL;				//oregion busymap object
	oreg_f->address		=	begin;				//
	oreg_f->size		=	(end - begin) / PAGESZ;
	set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
		oreg = (o_region*)i.u.ll.node->data;
		//printf("actual is [%i,%i]\n", oseg->start, oseg->end);
		if (oreg->address > begin)
		{
			//printf("yes !\n");
			return set_before_ll(set, i, oreg_f);
		}
	}
	return ERROR_UNKNOWN;
}

t_error			region_first_fit(	o_as*		as,
					 	t_vsize		size,
						t_vaddr*	address)
{
	t_vaddr		start	=	region->start;			//mem start
	t_vaddr		l_begin	=	start;				//tmp start zone
	i_set		set	=	as->regions;			//oregion busymap list
 	o_region*	oreg	=	malloc(sizeof(o_region));	//oregion busymap object
 	oreg->address		=	start;				//
 	oreg->size		=	PAGESZ;
 	//printf("not null\n");
 	t_iterator	i;
 	t_state		state;
 	set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
// 		oreg = (o_region*)i.u.ll.node->data;
// 		if (l_begin - oreg->address >= size * PAGESZ)
// 		{
// 			region_add_sorted(as, l_begin, l_begin + size * PAGESZ);
// 			*address = l_begin;
// 			return ERROR_NONE;
// 			break;
// 		}
// 		l_begin = oreg->address + oreg->size * PAGESZ;
	}
	return ERROR_UNKNOWN;
}

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
