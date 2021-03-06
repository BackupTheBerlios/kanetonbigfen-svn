/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /home/buckman/kaneton/libs/libia32/include/libia32.h
 *
 * created       matthieu bucchianeri   [tue dec 20 13:58:56 2005]
 * updated       matthieu bucchianeri   [wed nov  1 18:07:26 2006]
 */

#ifndef LIBIA32_H
#define LIBIA32_H

/*
 * ---------- includes --------------------------------------------------------
 */

#include "misc/asm.h"
#include "misc/isa.h"
#include "misc/multiboot.h"
#include "misc/stdarg.h"
#include "misc/types.h"
#include "misc/spinlock.h"
#include "paging/paging.h"
#include "pmode/pmode.h"
#include "pmode/gdt.h"
#include "pmode/idt.h"
#include "interrupt/interrupt.h"
#include "interrupt/pic.h"
#include "interrupt/ipi.h"
#include "time/pit.h"
#include "task/context.h"
#include "task/tss.h"
#include "apic/apic.h"

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../pmode/pmode.c
 *      ../pmode/gdt.c
 *      ../pmode/ldt.c
 *      ../pmode/idt.c
 *      ../paging/paging.c
 *      ../paging/pd.c
 *      ../paging/pt.c
 *      ../paging/tlb.c
 *      ../interrupt/pic.c
 *      ../interrupt/interrupt.c
 *      ../interrupt/ipi.c
 *	../time/timer.c
 *	../task/context.c
 *      ../task/tss.c
 *      ../apic/apic.c
 *      ../misc/cpuid.c
 *      ../misc/extensions.c
 */

/*
 * ../pmode/pmode.c
 */

t_error			pmode_init(void);

t_error			pmode_enable(void);

t_error			pmode_set_segment_registers(t_uint16	seg_code,
						    t_uint16	seg_data);

t_error			pmode_clean(void);


/*
 * ../pmode/gdt.c
 */

t_error			gdt_dump(t_ia32_gdt*			dump_gdt);

t_error			gdt_size(t_ia32_gdt*			table,
				 t_uint16			*size);

t_error			gdt_build(t_uint16			entries,
				  t_paddr			base,
				  t_ia32_gdt*			gdt,
				  t_uint8			clear);

t_error			gdt_activate(t_ia32_gdt			new_gdt);

t_error			gdt_import(t_ia32_gdt*			gdt);

t_error			gdt_add_segment(t_ia32_gdt*		table,
					t_uint16		segment,
					t_ia32_segment		descriptor);

t_error			gdt_reserve_segment(t_ia32_gdt*		table,
					    t_ia32_segment	descriptor,
					    t_uint16*		segment);

t_error			gdt_get_segment(t_ia32_gdt*		table,
					t_uint16		index,
					t_ia32_segment*		segment);

t_error			gdt_delete_segment(t_ia32_gdt*		table,
					   t_uint16		segment);

t_error			gdt_build_selector(t_uint16		segment,
					   t_ia32_prvl		privilege,
					   t_uint16*		selector);


/*
 * ../pmode/ldt.c
 */

t_error			ldt_base(t_ia32_ldt*			table,
				 t_paddr*			addr);

t_error			ldt_size(t_ia32_ldt*			table,
				 t_uint16			*size);

t_error			ldt_dump(t_ia32_ldt*			table);

t_error			ldt_activate(t_ia32_ldt			table);

t_error			ldt_build(t_uint16			entries,
				  t_paddr			base,
				  t_ia32_ldt*			ldt,
				  t_uint8			clear);

t_error			ldt_destroy(t_ia32_ldt			*ldt);

t_error			ldt_add_segment(t_ia32_ldt*		table,
					t_uint16		segment,
					t_ia32_segment		descriptor);

t_error			ldt_reserve_segment(t_ia32_ldt*		table,
					    t_ia32_segment	descriptor,
					    t_uint16*		segment);

t_error			ldt_get_segment(t_ia32_ldt*		table,
					t_uint16		index,
					t_ia32_segment*		segment);

t_error			ldt_delete_segment(t_ia32_ldt*		table,
					   t_uint16		segment);

t_error			ldt_build_selector(t_ia32_ldt*		table,
					   t_uint16		segment,
					   t_ia32_prvl		privilege,
					   t_uint16*		selector);


/*
 * ../pmode/idt.c
 */


/*
 * ../paging/paging.c
 */

t_error			paging_init(void);

t_error			paging_enable(void);

t_error			paging_clean(void);


/*
 * ../paging/pd.c
 */

t_error			pd_dump(t_ia32_directory*		dir);

t_error			pd_build(t_paddr			base,
				 t_ia32_directory*		directory,
				 t_uint8			clear);

t_error			pd_base(t_ia32_directory*		dir,
				t_paddr*			base);

t_error			pd_activate(t_ia32_directory		dir,
				    t_uint32			cached,
				    t_uint32			writeback);

t_error			pd_get_cr3(t_uint32*			cr3,
				   t_ia32_directory		dir,
				   t_uint32			cached,
				   t_uint32			writeback);

t_error			pd_add_table(t_ia32_directory*		dir,
				     t_uint16			entry,
				     t_ia32_table		table);

t_error			pd_get_table(t_ia32_directory*		dir,
				     t_uint16			entry,
				     t_ia32_table*		table);

t_error			pd_delete_table(t_ia32_directory*	dir,
					t_uint16		entry);


/*
 * ../paging/pt.c
 */

t_error			pt_dump(t_ia32_pte*			tab);

t_error			pt_build(t_paddr			base,
				 t_ia32_table*			table,
				 t_uint8			clear);

t_error			pt_add_page(t_ia32_table*		tab,
				    t_uint16			entry,
				    t_ia32_page			page);

t_error			pt_get_page(t_ia32_table*		tab,
				    t_uint16			entry,
				    t_ia32_page*		page);

t_error			pt_delete_page(t_ia32_table*		tab,
				       t_uint16			entry);


/*
 * ../paging/tlb.c
 */

t_error			tlb_invalidate(t_paddr			page);

t_error			tlb_flush(void);


/*
 * ../interrupt/pic.c
 */

void init_pics();

void irq_enable(int i);

void irq_disable(int i);


/*
 * ../interrupt/interrupt.c
 */

void			set_gate(t_uint8	number,
				 t_uint32	offset,
				 t_uint16	segment_selector);

void event_call(int id);

void event_call_error(int id, t_uint32 error);


/*
 * ../interrupt/ipi.c
 */

void			ipi_send_init(void);

void			ipi_send_startup(void);

void			ipi_send_vector(t_uint8			vector,
					t_ia32_ipi_dest		dest);

void			ipi_acknowledge(void);


/*
 * ../time/timer.c
 */

void ia32_pit_init();


/*
 * ../task/context.c
 */

void			context_setup(void);


/*
 * ../task/tss.c
 */

t_error			tss_load(t_ia32_tss*			tss,
				 t_uint16			ss,
				 t_uint32			esp,
				 t_uint32			io);

t_error			tss_init(t_ia32_tss*			tss);


/*
 * ../apic/apic.c
 */

void			apic_write(t_uint32			reg,
				   t_uint32			value);

t_uint32		apic_read(t_uint32			reg);

t_uint32		apic_id(void);

void			apic_enable(void);


/*
 * ../misc/cpuid.c
 */

t_uint32		cpuid_is_genuine(void);

char*			cpuid_get_brand(char* brand, int n);

t_uint32		cpuid_has_mmx(void);

t_uint32		cpuid_has_sse(void);

t_uint32		cpuid_has_sse2(void);

t_uint32		cpuid_has_sse3(void);

t_uint32		cpuid_has_fxstate(void);


/*
 * ../misc/extensions.c
 */

void			extensions_enable_sse(void);


/*
 * eop
 */

#endif
