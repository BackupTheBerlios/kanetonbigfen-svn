/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/map/map.c
 *
 * created       matthieu bucchianeri   [sun feb 26 12:56:54 2006]
 * updated       matthieu bucchianeri   [wed feb  7 15:00:10 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * the map manager is used to manage memory in a simpler way.
 *
 * this manager only does two things: reserving a new map and releasing it.
 * a map is a couple of segment and region.
 *
 * in future implementation, resizing of maps will be possible.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the map manager structure.
 */

m_map*		map;

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

/*
 * this function is a wrapper of mmap to map_reserve.
 */

void*			mmap(void*			start,
			     size_t			length,
			     int			prot,
			     int			flags,
			     int			fd,
			     off_t			offset)
{
  // FIXME: some easy code has been removed here

  return NULL;
}

/*
 * this function is a wrapper to munmap.
 */

int			munmap(void*			start,
			       size_t			length)
{
  // FIXME: some easy code has been removed here

  return 0;
}

/*
 * reserve virtual memory and map it.
 */

t_error			map_reserve(i_as		asid,
				    t_opts		opts,
				    t_vsize		size,
				    t_perms		perms,
				    t_vaddr*		addr)
{
  // FIXME: some easy code has been removed here

  return (ERROR_UNKNOWN);
}

/*
 * release a virtual memory space.
 */

t_error			map_release(i_as		asid,
				    t_vaddr		addr)
{
  // FIXME: some easy code has been removed here

  return (ERROR_UNKNOWN);
}

/*
 * initialize the map manager.
 *
 * steps:
 *
 * 1) allocate the manager structure.
 * 2) reserve a statistic object.
 */

t_error			map_init(void)
{
  /*
   * 1)
   */

  if ((map = malloc(sizeof(m_map))) == NULL)
    {
      cons_msg('!', "map: cannot allocate memory for the map "
	       "manager structure\n");

      return (ERROR_UNKNOWN);
    }

  memset(map, 0x0, sizeof(m_map));

  /*
   * 2)
   */

  STATS_RESERVE("map", &map->stats);

  return (ERROR_NONE);
}

/*
 * release the map manager.
 *
 * steps:
 *
 * 1) release the stats object.
 * 2) free the manager structure.
 */

t_error			map_clean(void)
{
  /*
   * 1)
   */

  STATS_RELEASE(map->stats);

  /*
   * 2)
   */

  free(map);

  return (ERROR_NONE);
}
