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
extern i_as	kasid;
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
  t_perms			perms;
  t_vaddr*		addr = NULL;

  if (prot & PROT_READ)
    perms &= PERM_READ;

  if (prot & PROT_WRITE)
    perms &= PERM_WRITE;

  if (prot & PROT_EXEC)
    perms &= PERM_EXEC;

  // FIXED: Lou - some easy code has been removed here
  map_reserve(kasid, MAP_OPT_PRIVILEGED, length, perms, addr);
  return addr;
}

/*
 * this function is a wrapper to munmap.
 */

int			munmap(void*			start,
			       size_t			length)
{
  // FIXME: Lou - some easy code has been removed here
  length = length;
  map_release(kasid, *(t_vaddr*) start);

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
  MAP_ENTER(map);
  // FIXED: Lou - some easy code has been removed here
  i_segment		segid;
  i_region		regid;
  o_region*		oreg;

  if (segment_reserve(asid, size, perms, &segid) != ERROR_NONE)
    MAP_LEAVE(map, ERROR_UNKNOWN);

  if (region_reserve(asid, &segid, 0, opts, *addr, size, &regid) != ERROR_NONE)
    MAP_LEAVE(map, ERROR_UNKNOWN);

  if (region_get(asid, &regid, &oreg) != ERROR_NONE)
    MAP_LEAVE(map, ERROR_UNKNOWN)
      *addr = oreg->address;

  return (ERROR_NONE);
}

/*
 * release a virtual memory space.
 */

t_error			map_release(i_as		asid,
				    t_vaddr		addr)
{
  o_as*			oas;
  t_state		state;
  o_region*		data;
  t_iterator		i;
  i_region		regid;
  i_segment		segid;
MAP_ENTER(map);

  // FIXED: Lou - some easy code has been removed here

if (as_get(asid, &oas) != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);
set_foreach(SET_OPT_FORWARD, oas->regions, &i, state)
    {
      if (set_object(oas->regions, i, (void**)&data) != ERROR_NONE)
	{
	  cons_msg('!', "region: cannot find the region object "
		   "corresponding to its identifier\n");

	  MAP_LEAVE(map, ERROR_UNKNOWN);
	}
if (data->address == addr)
{
regid = data->regid;
segid = data->segid;
break;
}
}
if (region_release(asid, regid) != ERROR_NONE)
	MAP_LEAVE(map, ERROR_UNKNOWN);

if (segment_release(segid) != ERROR_NONE)
	MAP_LEAVE(map, ERROR_UNKNOWN);

  return (ERROR_NONE);
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
