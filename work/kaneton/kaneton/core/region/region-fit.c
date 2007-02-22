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
  printf("/--------- asid = %3i -------\\\n", as->asid);
  t_setsz s = region_size(as);
  if (s != 0)
    {
      set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
	  set_object(set, i, (void**)&oreg);
/* 	  oreg = (i_region*)i.u.array.array; */
/* 	  printf("%i\n", oreg); */
	  size = oreg->size;
	  printf("|%8x -> %8x (%4i) |\n", oreg->address, oreg->address + size, size / PAGESZ);
	}
    }
  printf("\\----------------------------/\n");
}


t_error			region_add_sorted(	o_as*	as,
					  	t_vaddr begin,
					   	t_vaddr end)
{
  t_iterator	i;
  t_state	state;
  i_set		set	=	as->regions;
  o_region*	oreg_f	=	malloc(sizeof(o_region));
  o_region*	oreg	=	NULL;
  oreg_f->address	=	begin;
  oreg_f->size		=	(end - begin) / PAGESZ;
  set_foreach(SET_OPT_FORWARD, set, &i, state)
    {
      set_object(set, i, (void**)&oreg);
      if (oreg->address > begin)
	{
	  return set_before(set, i, oreg_f);
	}
    }
  return ERROR_UNKNOWN;
}

t_error			region_first_fit(	o_as*		as,
					 	t_vsize		size,
						t_vaddr*	address)
{
  t_vaddr		start	=	region->start;
  t_vaddr		l_begin	=	start;
  i_set			set	=	as->regions;
  o_region*		oreg	=	malloc(sizeof(o_region));
  oreg->address			=	start;
  oreg->size			=	PAGESZ;
  t_iterator		i;
  t_state		state;
  set_foreach(SET_OPT_FORWARD, set, &i, state)
    {
      set_object(set, i, (void**)&oreg);
      if (l_begin - oreg->address >= size * PAGESZ)
	{
	  region_add_sorted(as, l_begin, l_begin + size * PAGESZ);
	  *address = l_begin;
	  return ERROR_NONE;
	  break;
	}
      l_begin = oreg->address + oreg->size * PAGESZ;
    }
  return ERROR_UNKNOWN;
}

