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
t_setsz			segment_size()
{
	t_setsz		set_sz	=	42;				//set size
	set_size(segment->oseg_list, &set_sz); //get size of busymap
	return set_sz;
}

t_error			segment_first_fit(	t_psize		size,
						t_paddr*	address)
{
	t_paddr		start	=	segment->start;			//mem start
	t_paddr		end	=	segment->start + segment->size;	//mem end
	t_paddr		l_begin	=	start;				//tmp start zone
	t_paddr		l_end	=	end;				//tmp end zone
	i_set		set	=	segment->oseg_list;		//osegment busymap list
	oseg_busymap*	oseg	=	malloc(sizeof(oseg_busymap));	//osegment busymap object
	oseg->start		=	start;				//
	oseg->end		=	start + size * PAGESZ;
// 	if (segment_size() == 0)
// 	{
// 		printf("null\n");
// 		if (segment->size < size)
// 			return	(ERROR_UNKNOWN);
// 		else
// 		{
// 			*address = oseg->start;
// 			return set_add_ll(set, oseg);
// 		}
// 	}
// 	else
	{
		//printf("not null\n");
		t_iterator	i;
		t_state		state;
		set_foreach(SET_OPT_FORWARD, set, &i, state)
		{
			oseg = (oseg_busymap*)i.u.ll.node->data;
// 			printf("actual busy seg is %i -> %i\n", oseg->start, oseg->end);
			if (l_begin - oseg->start >= size * PAGESZ)
			{
// 				printf("enough place between %i > %i\n", l_begin, oseg->start);
				segment_add_sorted(l_begin, l_begin + size * PAGESZ);
				*address = l_begin;
				return ERROR_NONE;
				break;
			}
			else
// 				printf("not enough place between %i > %i, trying next...\n", l_begin, oseg->start);
			l_begin = oseg->end;
		}
		return ERROR_UNKNOWN;
	}
}

void			segment_dump()
{
	t_iterator	i;
	t_state		state;
	oseg_busymap*	oseg;
	i_set		set	=	segment->oseg_list;
	if (segment_size() != 0)
	{
		printf("+--- begin dump ----\n");
		set_foreach(SET_OPT_FORWARD, set, &i, state)
		{
			oseg = (oseg_busymap*)i.u.ll.node->data;
			printf("|%8x -> %x\n", oseg->start, oseg->end);
		}
		printf("+---  end  dump ----\n");
	}
	else
		printf("%s\n", "Empty dump");
}
