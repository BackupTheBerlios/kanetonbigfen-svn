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

// FIXME: lot of code has been removed here

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
  // FIXME: some code was removed here

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
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			segment_reserve(i_as			asid,
					t_psize			size,
					t_perms			perms,
					i_segment*		segid)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
}

t_error			segment_release(i_segment		segid)
{
  // FIXME: some code was removed here

  return (ERROR_UNKNOWN);
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

  // FIXME: perhaps some code is needed here
  cons_msg(' ', "\n");
  cons_msg(' ', "\n");
  set_init();
  i_set test;
  set_reserve_ll(SET_OPT_NONE, 100, &test);
  set_add_ll(test, "coin");
  set_add_ll(test, "42");
  set_add_ll(test, "69");
  set_show_ll(test);
  t_iterator i;
  t_state state;
  set_foreach(SET_OPT_FORWARD, test, &i, state)
  {
    printf("%s\n", i.u.ll.node->data);
  }
  cons_msg(' ', "\n");
  cons_msg(' ', "\n");
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
