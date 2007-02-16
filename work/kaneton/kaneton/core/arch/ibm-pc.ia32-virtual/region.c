/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/arch/ibm-pc.ia32-virtual/region.c
 *
 * created       julien quintard   [wed dec 14 07:06:44 2005]
 * updated       matthieu bucchianeri   [wed feb  7 10:47:05 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file  implements dependent  code for region  manager on  ia32 with
 * paging architecture.
 *
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>
#include <kaneton.h>

/*
 * ---------- extern ----------------------------------------------------------
 */

extern m_region*	region;
extern i_as		kasid;

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the region manager dispatch.
 */

d_region		region_dispatch =
  {

// FIXME: don't forget to fill this structure

  };

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here
t_error			ia32_region_reserve(i_as			asid,
					i_segment		segid,
				     	t_paddr			offset,
				     	t_opts			opts,
				     	t_vaddr			address,
				     	t_vsize			size,
				     	i_region*		regid)
{
/*t_uint16			pde_start;
t_uint16			pde_end;
t_uint16			pte_start;
t_uint16			pte_end;
t_ia32_table*			table = NULL;
i_segment	        	table_id;
int				i = 0;

REGION_ENTER(region);
pde_start = PDE_ENTRY(address);
pde_end = PDE_ENTRY(address + size);
pte_start = PTE_ENTRY(address);
pte_end = PTE_ENTRY(address + size);

for (i = pde_start; i != pde_end; i++)
{
pd_get_table(NULL, i, table);
if (table == NULL)
{
segment_reserve(asid, PAGESZ, PERM_READ | PERM_WRITE, &table_id);

pd_add_table(NULL, i,t_ia32_table		table)
}
}*/
REGION_LEAVE(region, ERROR_NONE);
}

/*
 * this function just initialises the machine-dependent region manager.
 *
 * for the intel 32-bit architecture we just initialise the paging mode.
 */

t_error			ia32_region_init(t_vaddr		start,
					 t_vsize		size)
{
  REGION_ENTER(region);

  if (paging_init() != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  REGION_LEAVE(region, ERROR_NONE);
}

/*
 * this function cleans the machine-dependent region manager.
 */

t_error			ia32_region_clean(void)
{
  REGION_ENTER(region);

  if (paging_clean() != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  REGION_LEAVE(region, ERROR_NONE);
}
