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
  int			clear = 0;

  REGION_ENTER(region);

  if (as_get(kasid, &kas) != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  if (region_space(kas, PAGESZ, vaddr) != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  if ((oreg = malloc(sizeof(o_segment*))) == NULL)
    REGION_LEAVE(region, ERROR_UNKNOWN);

  if ((segment = malloc(sizeof(o_segment))) == NULL)
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
      segment_reserve(kasid, PAGESZ, PERM_READ | PERM_WRITE, &segid);
      if (segment_get(segid, &segment) != ERROR_NONE)
	REGION_LEAVE(region, ERROR_UNKNOWN);
      pt_build(segment->address, &table, 0);
      pd_add_table(&dir, pde, table);
      clear = 1;
    }
 table.entries = ENTRY_ADDR(PD_MIRROR, pde);
 if (clear)
   memset(ENTRY_ADDR(PD_MIRROR, pde), '\0', PAGESZ);
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
  t_ia32_directory		pd;
  o_as*				oas;
  t_ia32_page			page;
  t_paddr			base;
  t_paddr			ram_paddr;
  t_vaddr			pd_addr;
  t_paddr			pt_addr;
  o_segment*			segment;
  int				i = 0;
  int				j = 0;
  int				x = 0;
  int				clear = 0;

  REGION_ENTER(region);
  if (as_get(asid, &oas) != ERROR_NONE)
    REGION_LEAVE(region, ERROR_UNKNOWN);

if (segment_get(segid, &segment) != ERROR_NONE)
	    REGION_LEAVE(region, ERROR_UNKNOWN);

  ram_paddr = segment->address;
  pd = oas->machdep.pd;
  base = MK_BASE(pd);
  // Mapping PD into Kernel
  map_page(base, &pd_addr);

  pde_start = PDE_ENTRY(address);
  pde_end = PDE_ENTRY(address + size);
  pte_start = PTE_ENTRY(address);
  pte_end = PTE_ENTRY(address + size);

  for (i = pde_start; i <= pde_end; i++)
    {
      if (pd_get_table((t_ia32_directory *) &pd_addr, i, &table) == ERROR_UNKNOWN)
	{
	  segment_reserve(asid, PAGESZ, PERM_READ | PERM_WRITE, &segid);
	  if (segment_get(segid, &segment) != ERROR_NONE)
	    REGION_LEAVE(region, ERROR_UNKNOWN);
	  pt_build(segment->address, &table, 0);
	  pd_add_table((t_ia32_directory *) &pd_addr, i, table);
	  clear = 1;
	}
       map_page(segment->address, &pt_addr);
       table.entries = pt_addr;
       if (clear)
	 memset((void*)pt_addr, '\0', PAGESZ);
      for (j = (i == pde_start ? pte_start : 0); j <= (i == pde_end ? pte_end : 1023); j++)
	{
	  page.addr = x + (offset + ram_paddr);
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
