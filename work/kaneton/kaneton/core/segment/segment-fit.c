/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/segment/segment-fit.c
 *
 * created       matthieu bucchianeri   [tue jan 10 01:03:46 2006]
 * updated       matthieu bucchianeri   [wed feb  7 10:39:57 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements simple  fitting algorithms for physical memory
 * management.
 *
 * you can define which algorithm to use with the macro SEGMENT_FIT.
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

machdep_include(segment);

/*
 * ---------- extern ----------------------------------------------------------
 */

/*
 * the segment manager structure.
 */

extern m_segment*	segment;

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXED: fensoft
t_setsz			segment_size(void)
{
	t_setsz		set_sz	=	42;
	set_size(segment->oseg_busymap_list, &set_sz);
	return set_sz;
}

void			segment_count(void)
{
  t_iterator	i;
  t_state	state;
  oseg_busymap*	oseg;
  i_set		set	=	segment->oseg_busymap_list;
  t_psize	size;
  int count = 0;
  if (segment_size() != 0)
    {
      set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
	  oseg = (oseg_busymap*)i.u.ll.node->data;
	  size = (oseg->end - oseg->start) / PAGESZ;
	  if (1 | size)
	    count++;
	}
    }
  printf("there is %i segments\n", count);
}

void			segment_dump(void)
{
  t_iterator	i;
  t_state	state;
  oseg_busymap*	oseg;
  i_set		set	=	segment->oseg_busymap_list;
  t_psize	size;

  printf("/----------------------------\\\n");
  if (segment_size() != 0)
    {
      set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
	  oseg = (oseg_busymap*)i.u.ll.node->data;
	  size = (oseg->end - oseg->start) / PAGESZ;
	  if (1 | size)
	    printf("|%8x -> %8x (%4i) |\n", oseg->start, oseg->end, size);
	}
    }
  printf("\\----------------------------/\n");
}

void			segment_dump2(i_as asid)
{
  t_iterator	i;
  t_state		state;
  o_segment*	oseg;
  i_set		set	=	segment->oseg_list;
  t_psize		size;
  printf("/--------- asid = %3i -------\\\n", asid);
  if (segment_size() != 0)
    {
      set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
	  oseg = (o_segment*)i.u.ll.node->data;
	  size = oseg->size;
	  if (oseg->asid == asid)
	    printf("|%8x -> %8x (%4i) |\n", oseg->address, oseg->address + size, size / PAGESZ);
	}
    }
  printf("\\----------------------------/\n");
}

t_error			segment_add(t_paddr begin, t_paddr end)
{
	i_set		set	=	segment->oseg_busymap_list;
	oseg_busymap*	oseg	=	malloc(sizeof(oseg_busymap));
	oseg->start		=	begin;
	oseg->end		=	end;
	return set_add(set, oseg);
}

t_error			segment_add_sorted(t_paddr begin,
					   t_paddr end)
{
	t_iterator	i;
	t_state		state;
	i_set		set	=	segment->oseg_busymap_list;
	oseg_busymap*	oseg_f	=	malloc(sizeof(oseg_busymap));
	oseg_busymap*	oseg	=	NULL;
	oseg_f->start		=	begin;
	oseg_f->end		=	end;
	set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
		oseg = (oseg_busymap*)i.u.ll.node->data;
		if (oseg->start > begin)
		  return set_before(set, i, oseg_f);
	}
	return ERROR_UNKNOWN;
}

t_error			segment_remove(t_paddr begin)
{
	t_iterator	i;
	t_state		state;
	i_set		set	=	segment->oseg_busymap_list;
	oseg_busymap*	oseg	=	NULL;
	set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
		oseg = (oseg_busymap*)i.u.ll.node->data;
		if (oseg->start == begin && begin != oseg->end)
			return set_delete_ll(set, i);
	}
	return ERROR_UNKNOWN;
}

t_error			segment_first_fit(	t_psize		size,
						t_paddr*	address)
{
  size = ((size + PAGESZ - 1 ) / PAGESZ) * PAGESZ;
  t_paddr	start	=	segment->start;
  t_paddr	l_begin	=	start;
  i_set		set	=	segment->oseg_busymap_list;
  oseg_busymap*	oseg	=	malloc(sizeof(oseg_busymap));
  oseg->start		=	start;
  oseg->end		=	start + size;
  t_iterator	i;
  t_state		state;
  set_foreach(SET_OPT_FORWARD, set, &i, state)
    {
      oseg = (oseg_busymap*)i.u.ll.node->data;
      if (l_begin - oseg->start >= size)
	{
	  segment_add_sorted(l_begin, l_begin + size);
	  *address = l_begin;
	  return ERROR_NONE;
	  break;
	}
      l_begin = oseg->end;
    }
  return ERROR_UNKNOWN;
}
