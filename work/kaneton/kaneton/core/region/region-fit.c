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

// FIXED: fensoft

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
	  // FIXED: fensoft
	  region_first_fit(as, size, address);
	  break;
	}
      default:
	REGION_LEAVE(region, ERROR_UNKNOWN);
    }
  return (ERROR_NONE);
}

t_setsz			region_size(o_as *as)
{
  t_setsz		set_sz	=	42;
  set_size(as->regions, &set_sz);
  return set_sz;
}

void			region_dump2(o_as* as)
{
  t_iterator	i;
  t_state	state;
  o_region*	oreg;
  i_set		set	=	as->regions;
  t_psize	size;
  t_setsz s = region_size(as);
  printf("/----------- asid = %3i (", as->asid);
  printf("%3i) -----------\\\n", s);
  if (s != 0)
    {
      set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
	  set_object(set, i, (void**)&oreg);
	  size = oreg->size;
	  printf("|%12x -> %12x (%8li) |\n", oreg->address, oreg->address + size - 1, size / PAGESZ);
	}
    }
  printf("\\----------------------------------------/\n");
}

/*
t_error			region_add_sorted(	o_as*	as,
					  	t_vaddr begin,
					   	t_vsize size)
{
  i_set		set	=	as->regions;
  o_region*	oreg_f	=	malloc(sizeof(o_region));
  oreg_f->address	=	begin;
  oreg_f->regid		=	(i_region)begin;
  oreg_f->size		=	size;
  set_add(set, oreg_f);
  return ERROR_UNKNOWN;
}
*/
t_error			region_first_fit(	o_as*		as,
					 	t_vsize		size,
						t_vaddr*	address)
{
  size = ((size + PAGESZ - 1 ) / PAGESZ) * PAGESZ;
  t_vaddr		start	=	region->start;
  t_vaddr		l_begin	=	start;
  i_set			set	=	as->regions;
  o_region*		oreg;

  t_iterator		i;
  t_state		state;

  set_foreach(SET_OPT_FORWARD, set, &i, state)
    {
      set_object(set, i, (void**)&oreg);
      if (oreg->address - l_begin >= size)
	{
/* 	  region_add_sorted(as, l_begin, size); */
	  *address = l_begin;
	  return ERROR_NONE;
	}
      l_begin = oreg->address + oreg->size;
    }
  return ERROR_UNKNOWN;
}

