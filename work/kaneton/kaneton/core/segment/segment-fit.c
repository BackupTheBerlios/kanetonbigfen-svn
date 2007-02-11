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

// FIXME: lot of code has been removed here
t_setsz			segment_size(void)
{
	t_setsz		set_sz	=	42;				//set size
	set_size(segment->oseg_list, &set_sz); //get size of busymap
	return set_sz;
}

void			segment_dump(void)
{
	t_iterator	i;
	t_state		state;
	oseg_busymap*	oseg;
	i_set		set	=	segment->oseg_list;
	printf("+--- begin dump ----\n");
	if (segment_size() != 0)
	{
		set_foreach(SET_OPT_FORWARD, set, &i, state)
		{
			oseg = (oseg_busymap*)i.u.ll.node->data;
			printf("|%8x -> %x\n", oseg->start, oseg->end);
		}
	}
	printf("+---  end  dump ----\n");
}

t_error			segment_add(t_paddr begin, t_paddr end)
{
	i_set		set	=	segment->oseg_list;		//osegment busymap list
	oseg_busymap*	oseg	=	malloc(sizeof(oseg_busymap));	//osegment busymap object
	oseg->start		=	begin;				//
	oseg->end		=	end;
	return set_add_ll(set, oseg);
}

t_error			segment_add_sorted(t_paddr begin,
					   t_paddr end)
{
	t_iterator	i;
	t_state		state;
	i_set		set	=	segment->oseg_list;		//osegment busymap list
	oseg_busymap*	oseg_f	=	malloc(sizeof(oseg_busymap));	//osegment busymap object
	oseg_busymap*	oseg	=	NULL;				//osegment busymap object
	oseg_f->start		=	begin;				//
	oseg_f->end		=	end;
	set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
		oseg = (oseg_busymap*)i.u.ll.node->data;
		//printf("actual is [%i,%i]\n", oseg->start, oseg->end);
		if (oseg->start > begin)
		{
			//printf("yes !\n");
			return set_before_ll(set, i, oseg_f);
		}
	}
	return ERROR_UNKNOWN;
}

t_error			segment_remove(t_paddr begin)
{
	t_iterator	i;
	t_state		state;
	i_set		set	=	segment->oseg_list;		//osegment busymap list
	oseg_busymap*	oseg	=	NULL;				//osegment busymap object
// 	printf("%x\n", begin);
	set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
		oseg = (oseg_busymap*)i.u.ll.node->data;
// 		printf("actual is [%i,%i]\n", oseg->start, oseg->end);
		if (oseg->start == begin && begin != oseg->end)
			return set_delete_ll(set, i);
	}
	return ERROR_UNKNOWN;
}

t_error			segment_first_fit(	t_psize		size,
						t_paddr*	address)
{
	t_paddr		start	=	segment->start;			//mem start
	t_paddr		l_begin	=	start;				//tmp start zone
	i_set		set	=	segment->oseg_list;		//osegment busymap list
	oseg_busymap*	oseg	=	malloc(sizeof(oseg_busymap));	//osegment busymap object
	oseg->start		=	start;				//
	oseg->end		=	start + size * PAGESZ;
	//printf("not null\n");
	t_iterator	i;
	t_state		state;
	set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
		oseg = (oseg_busymap*)i.u.ll.node->data;
		if (l_begin - oseg->start >= size * PAGESZ)
		{
			segment_add_sorted(l_begin, l_begin + size * PAGESZ);
			*address = l_begin;
			return ERROR_NONE;
			break;
		}
		l_begin = oseg->end;
	}
	return ERROR_UNKNOWN;
}
