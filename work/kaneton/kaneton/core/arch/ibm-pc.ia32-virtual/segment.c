/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/arch/ibm-pc.ia32-virtual/segment.c
 *
 * created       julien quintard   [fri feb 11 03:04:40 2005]
 * updated       matthieu bucchianeri   [wed feb  7 18:09:07 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this  file implements dependent  code for  segment manager  on ia32
 * with paging architecture.
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

extern m_segment*	segment;

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the segment manager dispatch.
 */

d_segment		segment_dispatch =
  {

// FIXME: don't forget to fill this structure

  };

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

t_error			(*segment_read)(i_segment id,
					t_paddr offset,
					void* buffer,
					t_psize size)
{
o_segment*			o;

// FIXED: Lou
SEGMENT_ENTER(segment);
if (segment_get(id, (void**)&o) == ERROR_NONE)
{
memcpy(buffer, o->address + offset, size);

SEGMENT_LEAVE(segment, ERROR_NONE);
}
  return (ERROR_UNKNOWN);
}

t_error			(*segment_write)(i_segment id,
					 t_paddr offset,
					 const void* buffer,
					 t_psize size)
{
o_segment*			o;

// FIXED: Lou
SEGMENT_ENTER(segment);
if (segment_get(id, (void**)&o) == ERROR_NONE)
{
memcpy(o->address + offset, buffer, size);

SEGMENT_LEAVE(segment, ERROR_NONE);
}
  return (ERROR_UNKNOWN);
}

t_error			(*segment_copy)(i_segment dst,
						t_paddr offd,
						i_segment src,
						t_paddr offs,
						t_psize size)
{

}


/*
 * this function just initialises the machine-dependent segment manager.
 *
 * steps:
 *
 * 1) initialise protected-mode.
 * 2) insert code and data segments for kernel task.
 * 3) insert code and data segments for drivers.
 * 4) insert code and data segments for services.
 * 5) insert code and data segments for userland programs.
 * 6) update segment selector registers.
 */

t_error			ia32_segment_init(void)
{
  t_ia32_segment	seg;
  t_uint16		kcs;
  t_uint16		kds;

  SEGMENT_ENTER(segment);

  /*
   * 1)
   */

  if (pmode_init() != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  /*
   * 2)
   */

  seg.base = 0;
  seg.limit = 0xffffffff;
  seg.privilege = ia32_prvl_supervisor;
  seg.is_system = 0;
  seg.type.usr = ia32_type_code;
  if (gdt_add_segment(NULL, PMODE_GDT_CORE_CS, seg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  seg.base = 0;
  seg.limit = 0xffffffff;
  seg.privilege = ia32_prvl_supervisor;
  seg.is_system = 0;
  seg.type.usr = ia32_type_data;
  if (gdt_add_segment(NULL, PMODE_GDT_CORE_DS, seg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  /*
   * 3)
   */

  seg.base = 0;
  seg.limit = 0xffffffff;
  seg.privilege = ia32_prvl_privileged;
  seg.is_system = 0;
  seg.type.usr = ia32_type_code;
  if (gdt_add_segment(NULL, PMODE_GDT_DRIVER_CS, seg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  seg.base = 0;
  seg.limit = 0xffffffff;
  seg.privilege = ia32_prvl_privileged;
  seg.is_system = 0;
  seg.type.usr = ia32_type_data;
  if (gdt_add_segment(NULL, PMODE_GDT_DRIVER_DS, seg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  /*
   * 4)
   */

  seg.base = 0;
  seg.limit = 0xffffffff;
  seg.privilege = ia32_prvl_privileged;
  seg.is_system = 0;
  seg.type.usr = ia32_type_code;
  if (gdt_add_segment(NULL, PMODE_GDT_SERVICE_CS, seg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  seg.base = 0;
  seg.limit = 0xffffffff;
  seg.privilege = ia32_prvl_privileged;
  seg.is_system = 0;
  seg.type.usr = ia32_type_data;
  if (gdt_add_segment(NULL, PMODE_GDT_SERVICE_DS, seg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  /*
   * 5)
   */

  seg.base = 0;
  seg.limit = 0xffffffff;
  seg.privilege = ia32_prvl_user;
  seg.is_system = 0;
  seg.type.usr = ia32_type_code;
  if (gdt_add_segment(NULL, PMODE_GDT_PROGRAM_CS, seg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  seg.base = 0;
  seg.limit = 0xffffffff;
  seg.privilege = ia32_prvl_user;
  seg.is_system = 0;
  seg.type.usr = ia32_type_data;
  if (gdt_add_segment(NULL, PMODE_GDT_PROGRAM_DS, seg) != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  /*
   * 6)
   */

  gdt_build_selector(PMODE_GDT_CORE_CS, ia32_prvl_supervisor, &kcs);
  gdt_build_selector(PMODE_GDT_CORE_DS, ia32_prvl_supervisor, &kds);
  pmode_set_segment_registers(kcs, kds);

  SEGMENT_LEAVE(segment, ERROR_NONE);
}

/*
 * this function cleans the machine-dependent segment manager.
 */

t_error			ia32_segment_clean(void)
{
  SEGMENT_ENTER(segment);

  if (pmode_clean() != ERROR_NONE)
    SEGMENT_LEAVE(segment, ERROR_UNKNOWN);

  SEGMENT_LEAVE(segment, ERROR_NONE);
}
