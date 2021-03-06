/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/include/core/region.h
 *
 * created       julien quintard   [fri feb 11 02:19:44 2005]
 * updated       matthieu bucchianeri   [wed feb  7 10:56:24 2007]
 */

#ifndef CORE_REGION_H
#define CORE_REGION_H		1

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <arch/machdep/machdep.h>
#include <core/id.h>
#include <core/types.h>

/*
 * ---------- macros ----------------------------------------------------------
 */

/*
 * flags
 */

#define REGION_OPT_NONE		0
#define REGION_OPT_FORCE	(1 << 0)
#define REGION_OPT_USER		(0 << 1)
#define REGION_OPT_PRIVILEGED	(1 << 1)
#define REGION_OPT_LOCAL	(0 << 2)
#define REGION_OPT_GLOBAL	(1 << 2)

/*
 * ---------- types -----------------------------------------------------------
 */

/*
 * region object
 *
 * a region object is identified by a regid.
 *
 * the identifier is in fact identical to the virtual address of the region.
 */

typedef struct
{
  i_region			regid;

  i_segment			segid;

  t_vaddr			address;
  t_paddr			offset;
  t_vsize			size;
  t_opts			opts;

  machdep_data(o_region);
}				o_region;

/*
 * region manager
 */

typedef struct
{
  o_id				id;

  t_lookup			lookup;

  t_vaddr			start;
  t_vsize			size;

  i_stats			stats;

  machdep_data(m_region);
}				m_region;

/*
 * the region architecture-dependent interface
 */

typedef struct
{
  t_error			(*region_show)(i_as,
					       i_region);
  t_error			(*region_inject)(i_as,
						 o_region*);
  t_error			(*region_reserve)(i_as,
						  i_segment,
						  t_paddr,
						  t_opts,
						  t_vaddr,
						  t_vsize,
						  i_region*);
  t_error			(*region_release)(i_as,
						  i_region);
  t_error			(*region_flush)(i_as);
  t_error			(*region_init)(t_vaddr,
					       t_vsize);
  t_error			(*region_clean)(void);
}				d_region;

/*
 * ---------- macro functions -------------------------------------------------
 */

/*
 * check
 */

#define REGION_CHECK(_region_)						\
  {									\
    if ((_region_) == NULL)						\
      return (ERROR_UNKNOWN);						\
  }

/*
 * enter
 */

#define REGION_ENTER(_region_)						\
  {									\
    REGION_CHECK((_region_));						\
									\
    STATS_BEGIN((_region_)->stats);					\
  }

/*
 * leave
 */

#define REGION_LEAVE(_region_, _error_)					\
  {									\
    STATS_END((_region_)->stats, (_error_));				\
									\
    return (_error_);							\
  }

/*
 * ---------- common prototypes -----------------------------------------------
 */

t_error			region_space(o_as*		as,
				     t_vsize		size,
				     t_vaddr*		address);
t_error			map_page(t_paddr paddr, t_vaddr *vaddr);
t_error			unmap_page (t_vaddr *vaddr);
/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../../core/region/region.c
 *      ../../core/region/region-fit.c
 */

/*
 * ../../core/region/region.c
 */

t_error			region_show(i_as			asid,
				    i_region			regid);

t_error			region_dump(i_as		asid);

t_error			region_inject(i_as		asid,
				      o_region*		o);

t_error			region_reserve(i_as			asid,
				       i_segment		segid,
				       t_paddr			offset,
				       t_opts			opts,
				       t_vaddr			address,
				       t_vsize			size,
				       i_region*		regid);

t_error			region_release(i_as			asid,
				       i_region			regid);

t_error			region_flush(i_as			asid);

t_error			region_get(i_as				asid,
				   i_region			regid,
				   o_region**			o);

t_error			region_init(t_vaddr			start,
				    t_vsize			size);

t_error			region_clean(void);


/*
 * ../../core/region/region-fit.c
 */

t_error			region_space(o_as*		as,
				     t_vsize		size,
				     t_vaddr*		address);

t_setsz			region_size(o_as *as);

void			region_dump2(o_as* as);

t_error			region_first_fit(	o_as*		as,
					 	t_vsize		size,
						t_vaddr*	address);


/*
 * eop
 */

#endif
