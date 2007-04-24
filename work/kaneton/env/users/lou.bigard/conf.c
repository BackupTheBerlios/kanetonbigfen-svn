/*
** conf.c for kaneton in /home/francois/kaneton/kaneton/core
**
** Made by francois goudal
** Login   <goudal_f@epita.fr>
**
** Started on  Sat Feb 17 18:05:48 2007 francois goudal
** Last update Mon Apr 16 18:58:52 2007 francois goudal
*/
#include <kaneton.h>

extern t_init*		init;
extern i_as		kasid;

void	ia32_kbd_handler(t_id id)
{
  unsigned char temp;

  INB(0x60, temp);
  printf("KEYCODE %d\n", temp);
}

void	ia32_pf_handler(t_id id, t_uint32 errcode)
{
  t_uint32		temp;

  SCR2(temp);
  printf("PAGE FAULT errcode %d", errcode);
  printf(", address %x\n", temp);
  while (1)
    ;
}

void			check_tests(void)
{
  /* put your tests here */
  i_region		regid;
  i_task		taskid;
  i_as			tasid;
  t_vaddr		addr;
  char*			buf;
  char*			buf3;
  o_as*			as;
  o_as*			tas;
  int*			chiche;
  unsigned		i;
  i_timer		t;

  as_get(kasid, &as);

  buf = mmap(0, 4096 * 2, PROT_READ, 0, 0, 0);
  buf3 = mmap(0, 4096 * 2, PROT_READ | PROT_WRITE, 0, 0, 0);

  if (task_reserve(TASK_CLASS_CORE,
	       TASK_BEHAV_INTERACTIVE,
	       TASK_PRIOR_INTERACTIVE,
	       &taskid) != ERROR_NONE)
    printf("OOPS TASK RESERVE\n");
  if (as_reserve(taskid, &tasid) != ERROR_NONE)
    printf("OOPS AS RESERVE\n");
  as_get(tasid, &tas);

  map_reserve(tasid, MAP_OPT_USER, 4096, PERM_READ | PERM_WRITE, &addr);
  printf("Virt addr in task as : %x\n", addr);

  printf("Kstack addr %x\n", init->kstack);
  region_reserve(tasid,
		 init->kstack,
		 0,
		 REGION_OPT_GLOBAL | REGION_OPT_FORCE,
		 init->kstack,
		 init->kstacksz,
		 &regid);
  printf("Kstack mapped in task at address %x\n", regid);
/*   region_dump(tasid); */
  printf("Reserving more than 4megs returned : %d ",
	 map_reserve(tasid, MAP_OPT_USER, 4096 * 1024 * 4, PERM_READ | PERM_WRITE, &addr));
/*   timer_reserve(EVENT_FUNCTION, (u_timer_handler)chiche42, 1000, 1, &t); */
/*   event_reserve(33, EVENT_FUNCTION, (u_event_handler)ia32_kbd_handler); */
/*   event_reserve(14, EVENT_FUNCTION, EVENT_HANDLER(ia32_pf_handler)); */
  pd_activate(tas->machdep.pd, PD_CACHED, PD_WRITEBACK);
/*   buf3 = (void*)(t_vaddr)regid; */
/*   buf3[42] = 'C'; */
/*   buf3[43] = 'h'; */
/*   buf3[44] = 'i'; */
/*   buf3[45] = 'c'; */
/*   buf3[46] = 'h'; */
/*   buf3[47] = 'e'; */
  printf("- returned address is %x\n", addr);
  chiche = (int*)addr;
  for (i = 0; i < 4096 * 1024; ++i)
    chiche[i] = i;
  printf("Branle\n");
  while (1)
    ;
}
