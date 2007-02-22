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
  // FIXED: Lou
  o_as*			oas;

  SEGMENT_ENTER(segment);
  // Getting the o_as*
  if (as_get(asid, &oas) == ERROR_NONE)
    {
      // Segment injection
      o->asid = asid;
      *segid = o->segid = (i_segment)o->address;
      set_add(oas->segments, (void*) o);
      set_add(segment->oseg_list, (void*) o);
      segment_add_sorted(o->address, o->address + o->size);
      return (ERROR_NONE);
    }
  return (ERROR_UNKNOWN);
}

t_error			segment_perms(i_segment			segid,
				      t_perms			perms)
{
  o_segment*			o;

  // FIXED: Lou
  SEGMENT_ENTER(segment);
  if (segment_get(segid,&o) == ERROR_NONE)
    {
      o->perms = perms;
      SEGMENT_LEAVE(segment, ERROR_NONE);
    }
  return (ERROR_UNKNOWN);
}

t_error			segment_flush(i_as			asid)
{
  // FIXED: fensoft

  t_iterator	i;
  t_state	state;
  o_segment*	oseg;
  i_set		set	=	segment->oseg_list;
  t_psize	size;
  if (segment_size() != 0)
    {
      set_foreach(SET_OPT_FORWARD, set, &i, state)
	{
	  oseg = (o_segment*)i.u.ll.node->data;
	  size = oseg->size;
	  if (oseg->asid == asid)
	    segment_release(oseg->segid);
	}
    }
  return (ERROR_UNKNOWN);
}

t_error			segment_get(i_segment			segid,
				    o_segment**			o)
{
  // FIXED: Lou
  SEGMENT_ENTER(segment);

  if (set_get(segment->oseg_list, segid, (void**)o) == ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_NONE);
  SEGMENT_LEAVE(segment, ERROR_UNKNOWN);
}

t_error			segment_reserve(i_as			asid,
					t_psize			size,
					t_perms			perms,
					i_segment*		segid)
{
  SEGMENT_ENTER(segment);
  // FIXED: Lou
  o_as*			oas;
  o_segment*		oseg = malloc(sizeof(o_segment));

  // Getting the o_as*
  if (as_get(asid, &oas) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  // Segment Allocation
  if (segment_space(oas, size, &oseg->address) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);
  oseg->size = size;
  oseg->asid = asid;
  oseg->perms = perms;
  oseg->type = SEGMENT_TYPE_MEMORY;
  *segid = oseg->segid = (i_segment)oseg->address;

  if (set_add(oas->segments, (void*) oseg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);
  if (set_add(segment->oseg_list, (void*) oseg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);
 SEGMENT_LEAVE(segment, ERROR_NONE);
  return (ERROR_UNKNOWN);
}

t_error			segment_release(i_segment		segid)
{
  // FIXED: fensoft
  SEGMENT_ENTER(segment);
  // get the o_segment
  o_segment*	oseg;
  if (segment_get(segid, &oseg) != ERROR_NONE)
    return (ERROR_UNKNOWN);
  // get the o_as
  o_as*			oas;
  if (as_get(oseg->asid, &oas) != ERROR_NONE)
    return (ERROR_UNKNOWN);
  segment_remove(oseg->address);
  set_remove(oas->segments, oseg->segid);
  set_remove(segment->oseg_list, oseg->segid);
  return (ERROR_NONE);
}

t_error			segment_space(	o_as*		as,
				      	t_psize		size,
					t_paddr*	address)
{
  // FIXED: Fensoft
  size = ((size + PAGESZ - 1 ) / PAGESZ) * PAGESZ;
  return segment_first_fit(size, address);
}

t_error			segment_read(i_segment	id,
				     t_paddr	offset,
				     void*	buffer,
				     t_psize	size)
{
  if (machdep_call(segment, segment_read, id, offset, buffer, size) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);
}

t_error			segment_write(i_segment		id,
				      t_paddr		offset,
				      const void*	buffer,
				      t_psize		size)
{
  if (machdep_call(segment, segment_write, id, offset, buffer, size) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);
}

t_error			segment_copy(i_segment	dst,
				     t_paddr	offd,
				     i_segment	src,
				     t_paddr	offs,
				     t_psize	size)
{
  if (machdep_call(segment, segment_copy, dst, offd, src, offs, size) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);
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

  // FIXED: fensoft
  if (set_reserve(ll, SET_OPT_ALLOC, 2 + segment->size/PAGESZ, &segment->oseg_busymap_list) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);
  if (set_reserve(ll, SET_OPT_SORT | SET_OPT_FREE,
		  sizeof(o_segment), &segment->oseg_list) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  segment_add(segment->start + segment->size, segment->start + segment->size);
  segment_add(segment->start, segment->start);

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
