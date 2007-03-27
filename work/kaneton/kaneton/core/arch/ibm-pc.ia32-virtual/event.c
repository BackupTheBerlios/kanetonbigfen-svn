/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/core/arch/ibm-pc.ia32-virtual/event.c
 *
 * created       renaud voltz   [mon feb 13 01:05:52 2006]
 * updated       matthieu bucchianeri   [wed feb  7 10:46:43 2007]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements dependent code for the events on ia32 with paging
 * architecture.
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
 * the event manager dispatch.
 */
/*   t_error			(*event_show)(i_event); */
/*   t_error			(*event_notify)(i_event); */
/*   t_error			(*event_reserve)(i_event, */
/* 						 t_uint32, */
/* 						 u_event_handler); */
/*   t_error			(*event_release)(i_event); */
/*   t_error			(*event_init)(void); */
/*   t_error			(*event_clean)(void); */
d_event				event_dispatch =
  {
    NULL,
    NULL,
    NULL,
    NULL,
    ia32_event_init,
    NULL
  };

//static unsigned char idt[256][8];
static struct s_idt_entry gl_idt[256];

/*
 * ---------- functions -------------------------------------------------------
 */

// FIXME: lot of code has been removed here

/* void idt_set(int interupt, */
/* 	     unsigned long pointer) */
/* { */
/*   idt[interupt][7] = (pointer & 0xFF000000) >> 24; */
/*   idt[interupt][6] = (pointer & 0x00FF0000) >> 16; */
/*   idt[interupt][5] = 0xEE; */
/*   idt[interupt][4] = 0x00; */
/*   idt[interupt][3] = 0x0010 >> 8;  //? */
/*   idt[interupt][2] = 0x0010; //? */
/*   idt[interupt][1] = (pointer & 0x0000FF00) >> 8; */
/*   idt[interupt][0] = (pointer & 0xFF0000FF) >> 0; */
/* } */

struct s_idt_entry
{
  unsigned char field[8];
}__attribute__((packed));

struct s_idt_ptr
{
  unsigned short        limit;
  unsigned int          base;
}__attribute__((packed));

void			set_gate(unsigned char	number,
				 unsigned long	offset,
				 unsigned short	segment_selector)
{
  unsigned short        offsetH;
  unsigned short        offsetL;

  offsetH = offset >> 16;
  offsetL = offset & 0x0000FFFF;
  gl_idt[number].field[0] = offsetL;
  gl_idt[number].field[1] = offsetL >> 8;
  gl_idt[number].field[2] = segment_selector;
  gl_idt[number].field[3] = segment_selector >> 8;
  gl_idt[number].field[4] = 0;
  gl_idt[number].field[5] = 0xEE; //1 11 0 1 110
  gl_idt[number].field[6] = offsetH;
  gl_idt[number].field[7] = offsetH >> 8;
}

void dbz()
{
  printf("Division by zero : Looser...\n");
  while (1)
    ;
}

/* void idt_init() */
/* { */
/*   int i, j; */
/*   for (i = 0; i < 256; i++) */
/*     for (j = 0; j < 8; j++) */
/*       idt[i][j] = 0; */
/*   for (i = 0; i < 13; i++) */
/*     idt_set(i, (unsigned long)test); */
/*   struct s_idt_ptr */
/*   { */
/*     unsigned short        limit; */
/*     unsigned int          base; */
/*   }__attribute__((packed)); */
/*   struct s_idt_ptr	idtr; */
/*   idtr.limit = 256 * 8;; */
/*   idtr.base = (unsigned int) idt; */
/*   asm volatile("lidt %0":: "m" (idtr)); */
/* } */

void			lidt(void *base, unsigned short limit)
{
  struct s_idt_ptr	idtr;

  idtr.limit = limit;
  idtr.base = (unsigned int) base;
  //asm volatile("lgdt %0":: "m" (idtr));
  asm volatile("lidt %0\n":: "m" (idtr):"memory");
}

int			idt_init()
{
  int			i;
  int			j;

  for (j = 0; j < 256; ++j)
    for (i = 0; i < 8; ++i)
      gl_idt[j].field[i] = 0x00;

  t_uint16		kcs;
/*   gdt_build_selector(PMODE_GDT_CORE_CS, ia32_prvl_supervisor, &kcs); */
/*   printf(" kcs=%i ", kcs); */
/*   gdt_build_selector(PMODE_GDT_CORE_CS, ia32_prvl_supervisor, &kcs); */
/*   printf(" kcs=%i ", kcs); */
  gdt_build_selector(PMODE_GDT_CORE_CS, ia32_prvl_supervisor, &kcs);
  printf(" kcs=%i ", kcs);
  for (i=0; i<16; i++)
    set_gate( i, (unsigned long)dbz, 0x8E);

  lidt(gl_idt, 256 * 8);
  asm volatile ("int $1\n");
  return 0;
}

t_error ia32_event_init(void)
{
  //idt_init();
 /*  asm volatile ("int $1"); */
  return ERROR_NONE;
}
