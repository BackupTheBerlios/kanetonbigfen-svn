/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/segment/segment.c
 *
 * created       julien quintard   [fri feb 11 03:04:40 2005]
 * updated       matthieu bucchianeri   [wed feb  7 18:08:17 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * the segment manager manages physical memory.
 *
 * it  is  able   to  reserve  and  release  memory   areas  (see  the
 * segment-fit.c for  allocation algorithm)  and to operated  on these
 * area: resize, split, copy, etc.
 *
 * a segment  is identified by  a 64 bits identifier  corresponding to
 * its physical  address. so  it is easy  to retrieve  this identifier
 * given the base address of a segment.
 *
 * remember  that  segments are  global:  there  is  only one  set  of
 * segments objects for  the entire kernel. the set  of segments in an
 * address space is just a set of identifiers.
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
 * init structure
 */

extern t_init*		init;

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the segment manager structure.
 */

m_segment*		segment;

/*
 * ---------- functions -------------------------------------------------------
 */

t_error			segment_clone(i_as			asid,
				      i_segment			old,
				      i_segment*		new)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			segment_inject(i_as		asid,
				       o_segment*	o,
				       i_segment*	segid)
{
  // FIXME: Lou
o_as*			oas;

SEGMENT_ENTER(segment);
// Getting the o_as*
if (as_get(asid, &oas) == ERROR_NONE)
{
// Segment injection
o->asid = asid;
*segid = o->segid = (i_segment)o->address;
set_add_array(oas->segments, (void*) o);
set_add_array(segment->oseg_list, (void*) o);
return (ERROR_NONE);
}
	return (ERROR_UNKNOWN);
}

t_error			segment_perms(i_segment			segid,
				      t_perms			perms)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			segment_flush(i_as			asid)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			segment_get(i_segment			segid,
				    o_segment**			o)
{
  // FIXME: Lou
SEGMENT_ENTER(segment);

if (set_get(segment->oseg_list, segid, (void**)o) == ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_NONE);

  return (ERROR_UNKNOWN);
}

t_error			segment_reserve(i_as			asid,
					t_psize			size,
					t_perms			perms,
					i_segment*		segid)
{
  // FIXED: Lou
o_as*			oas;
o_segment*		oseg;
t_iterator		i;
t_state			state;

cons_msg('!', "BEFORE     \n");
as_show(asid);
// Getting the o_as*
if (as_get(asid, &oas) != ERROR_NONE)
	SEGMENT_LEAVE(as, ERROR_UNKNOWN);

  set_foreach(SET_OPT_FORWARD, oas->segments, &i, state)
    {
      if (set_object(oas->segments, i, (void**)&oseg) != ERROR_NONE)
		SEGMENT_LEAVE(region, ERROR_UNKNOWN);
	if (oseg->address == 0x0)
		break;
}
// Segment Allocation
segment_space(oas, size, &oseg->address);
oseg->size = size;
oseg->asid = asid;
oseg->perms = perms;

*segid = oseg->segid = (i_segment)oseg->address;
set_add_array(oas->segments, (void*) oseg);
set_add_array(segment->oseg_list, (void*) oseg);
cons_msg('!', "AFTER     \n");
as_show(asid);
  return (ERROR_UNKNOWN);
}

t_error			segment_release(i_segment		segid)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			segment_space(	o_as*		as,
				      	t_psize		size,
					t_paddr*	address)
{
	return segment_first_fit(size, address);
}

/*
 * this function initialises the segment manager from the init
 * variable containing segments to keep safe.
 *
 * steps:
 *
 * 1) allocates and initialises the segment manager structure.
 * 2) initialises the segment manager structure fields from the init
 *    structure.
 * 3) tries to reserve a statistics object.
 * 4) calls the machine-dependent code.
 */

/**
 * 
 * @param  
 * @return 
 */
t_error			segment_init(void)
{
i_segment	        seg;
i_task			ktask = ID_UNUSED;
i_as			asid;
  /*
   * 1)
   */

  if ((segment = malloc(sizeof(m_segment))) == NULL)
    {
      cons_msg('!', "segment: cannot allocate memory for the segment "
	       "manager structure\n");

      return (ERROR_UNKNOWN);
    }

  memset(segment, 0x0, sizeof(m_segment));

  /*
   * 2)
   */

  segment->start = init->mem;
  segment->size = init->memsz;
  segment->lookup = SEGMENT_LOOKUP_ALGORITHM;

  /*
   * 3)
   */

  STATS_RESERVE("segment", &segment->stats);

  // FIXME: perhaps some code is needed here
  set_reserve_ll(SET_OPT_NONE, 2 + segment->size/PAGESZ, &segment->oseg_busymap_list); // pire cas
if (set_reserve(array, SET_OPT_SORT | SET_OPT_ALLOC, AS_SEGMENTS_INITSZ,
		  sizeof(i_segment), &segment->oseg_list) != ERROR_NONE)
      AS_LEAVE(as, ERROR_UNKNOWN);

  segment_add(segment->start + segment->size, segment->start + segment->size);
  segment_add(segment->start, segment->start);
//   
//     //printf("low=%i up=%i pages=%i\n", segment->start, segment->size + segment->start, segment->size/PAGESZ);
   //t_paddr res1;
//   segment_first_fit(2, &res1);
   //segment_space(0, 4, &res1);
//   segment_dump();
//   t_paddr res2;
//   segment_first_fit(4, &res2);
//   segment_dump();
//   segment_remove(res1);
//   segment_dump();
//   segment_first_fit(1, &res1);
//   segment_dump();
//   segment_first_fit(1, &res1);
//   segment_dump();

  i_segment test;
  segment_reserve(0, 4, PERM_READ | PERM_WRITE, &test);
  segment_dump();
 /*if (as_reserve(ktask, &asid) != ERROR_NONE)
    {
      cons_msg('!', "task: unable to reserve the kernel address space\n");

      return (ERROR_UNKNOWN);
    }*/
/*if (segment_reserve(&asid, PAGESZ,
			  PERM_READ | PERM_WRITE, &seg) != ERROR_NONE)
	AS_LEAVE(as, ERROR_UNKNOWN);*/
  /*
   * 4)
   */

  if (machdep_call(segment, segment_init) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  return (ERROR_NONE);
}

/*
 * this function just reinitialises the segment manager.
 *
 * steps:
 *
 * 1) calls the machine-dependent code.
 * 2) releases the stats object.
 * 3) frees the segment manager structure's memory.
 */

t_error			segment_clean(void)
{
  /*
   * 1)
   */

  if (machdep_call(segment, segment_clean) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  /*
   * 2)
   */

  STATS_RELEASE(segment->stats);

  // FIXME: perhaps some code is needed here

  /*
   * 3)
   */

  free(segment);

  return (ERROR_NONE);
}
