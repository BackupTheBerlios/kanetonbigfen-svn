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
    NULL,
    NULL,
    region_reserve,
    region_release,
    NULL,
    NULL,
    NULL
  };

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here
t_error			map_page(t_paddr paddr, t_vaddr *vaddr)
{
  o_as*			kas;
  t_ia32_pde		pde;
  t_ia32_pde		pte;
  t_ia32_directory	dir;
  t_ia32_table		table;
  t_ia32_page		page;
  o_region*		oreg;
  i_segment		segid;
  o_segment*		segment;

  REGION_ENTER(region);

  if (as_get(kasid, &kas) != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  if (region_space(kas, PAGESZ, vaddr) != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  if ((oreg = malloc(sizeof(o_segment*))) == NULL)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  if (region_inject(kasid, oreg) != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  oreg->address = *vaddr;
  oreg->regid = (i_region)oreg->address;
  oreg->opts = REGION_OPT_PRIVILEGED;
  oreg->size = PAGESZ;
  oreg->offset = paddr;
  oreg->segid = (i_segment)oreg->offset;

  region_inject(kasid, oreg);

  // Page Dir
  dir = kas->machdep.pd;
  pde = PDE_ENTRY(*vaddr);

  if (pd_get_table(&dir, pde, &table) == ERROR_UNKNOWN)
    {
      segment_reserve(kasid, 1, PERM_READ | PERM_WRITE, &segid);
      if (segment_get(segid, &segment) != ERROR_NONE)
	REGION_LEAVE(region, ERROR_UNKNOWN);
      pt_build(segment->address, &table, 0);
      table.present = 0;
      table.rw = 0;
      table.user = 0;
      table.cached = 0;
      table.writeback = 0;
      pd_add_table(&dir, pde, table);
    }
  else
    table.entries = ENTRY_ADDR(PD_MIRROR, pde);
  // Page Table
  pte = PTE_ENTRY(*vaddr);

  page.addr = paddr;
  pt_add_page(&table, pte, page);

  REGION_LEAVE(region, ERROR_NONE);
}

t_error			ia32_region_reserve(i_as			asid,
					i_segment		segid,
				     	t_paddr			offset,
				     	t_opts			opts,
				     	t_vaddr			address,
				     	t_vsize			size,
				     	i_region*		regid)
{
  t_ia32_pde			pde_start;
  t_ia32_pde			pde_end;
  t_ia32_pte			pte_start;
  t_ia32_pte			pte_end;
  t_ia32_table			table;
  i_segment	        	table_id;
  t_ia32_directory		pd;
  o_as*				oas;
  t_ia32_page			page;
  t_paddr			base;
  t_vaddr			pd_addr;
  o_segment*			segment;
  int				i = 0;
  int				j = 0;
  int				x = 0;

  REGION_ENTER(region);
  if (as_get(asid, &oas) != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  pd = oas->machdep.pd;
  base = MK_BASE(pd);
  // Mapping PD into Kernel
  map_page(base, &pd_addr);

  pde_start = PDE_ENTRY(pd_addr);
  pde_end = PDE_ENTRY(pd_addr + size);
  pte_start = PTE_ENTRY(pd_addr);
  pte_end = PTE_ENTRY(pd_addr + size);

  for (i = pde_start; i != pde_end; i++)
    {
      if (pd_get_table(&pd, i, &table) == ERROR_UNKNOWN)
	{
	  segment_reserve(asid, 1, PERM_READ | PERM_WRITE, &segid);
	  if (segment_get(segid, &segment) != ERROR_NONE)
	    REGION_LEAVE(region, ERROR_UNKNOWN);
	  pt_build(segment->address, &table, 0);
	  table.present = 0;
	  table.rw = 0;
	  table.user = 0;
	  table.cached = 0;
	  table.writeback = 0;
	  pd_add_table(&pd, i, table);
	}
      for (j = (i == pde_start ? pte_start : 0); j != (i == pde_end ? pte_end : 1023); j++)
	{
	  page.addr = x + offset;
	  pt_add_page(&table, j, page);
	  x += PAGESZ;
	}
    }
  REGION_LEAVE(region, ERROR_NONE);
}

t_error			ia32_region_release(i_as			asid,
					    i_region			regid)
{

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
