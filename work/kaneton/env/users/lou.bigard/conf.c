/*
** conf.c for Kaneton in /goinfre/goinfre/SVN/kaneton
**
** Made by lou bigard
** Login   <bigard_l@epita.fr>
**
** Started on  Wed Feb 21 22:56:03 2007 lou bigard
** Last update Thu Feb 22 23:07:36 2007 lou bigard
*/
#include <klibc.h>
#include <kaneton.h>

extern i_as kasid;

int sleep_num = 1;
int mysleep(int k)
{
  printf("sleep time=%3ims seq=%3i\n", k, sleep_num++);
  int i, j, ret;
  for (j = 0; j != k; j++)
    for (i = 0; i != 100000; i++)
      ret = i + j;
  return ret;
}


void			 check_tests(void)
{
  o_as*			 oas;
  o_segment*		oseg;
  o_region*		oreg;
  i_segment		segid;
  i_region		regid;
  t_vaddr		addr;
  
if (as_get(kasid, &oas) != ERROR_NONE)
return;

 cons_msg('#', "Testing Segment Reserve\n");
  
/*   if (segment_reserve(kasid, 1 * PAGESZ, PERM_READ | PERM_WRITE, &segid) != ERROR_NONE) */
/*    cons_msg('!', "Error Segment Reserve\n"); */
/*   region_reserve(kasid, segid, 0, REGION_OPT_NONE, 0, 1 * PAGESZ, &regid); */
/*  cons_msg('#', "After Segment Reserve %x\n", (t_vaddr) regid); */


/*   if (segment_reserve(kasid, 1 * PAGESZ, PERM_READ | PERM_WRITE, &segid) != ERROR_NONE) */
/*    cons_msg('!', "Error Segment Reserve\n"); */
/*   region_reserve(kasid, segid, 0, REGION_OPT_NONE, 0, 1 * PAGESZ, &regid); */
/*  cons_msg('#', "After Segment Reserve %x\n", (t_vaddr) regid); */


/*   if (segment_reserve(kasid, 1 * PAGESZ, PERM_READ | PERM_WRITE, &segid) != ERROR_NONE) */
/*    cons_msg('!', "Error Segment Reserve\n"); */
/*   region_reserve(kasid, segid, 0, REGION_OPT_NONE, 0, 1 * PAGESZ, &regid); */
/*  cons_msg('#', "After Segment Reserve %x\n", (t_vaddr) regid); */


/*   if (segment_reserve(kasid, 1 * PAGESZ, PERM_READ | PERM_WRITE, &segid) != ERROR_NONE) */
/*    cons_msg('!', "Error Segment Reserve\n"); */
/*   region_reserve(kasid, segid, 0, REGION_OPT_NONE, 0, 1 * PAGESZ, &regid); */
/*  cons_msg('#', "After Segment Reserve %x\n", (t_vaddr) regid); */


/*  if (segment_reserve(kasid, 3 * PAGESZ, PERM_READ | PERM_WRITE, &segid) != ERROR_NONE)
   cons_msg('!', "Error Segment Reserve\n");
    region_reserve(kasid, segid, 0, REGION_OPT_NONE, 0, 3 * PAGESZ, &regid);
 cons_msg('#', "After Segment Reserve %x\n", (t_vaddr) regid);
*/
  if (map_reserve(kasid,
		  MAP_OPT_PRIVILEGED,
		  3 * PAGESZ,
		  PERM_READ | PERM_WRITE,
		  &addr) != ERROR_NONE)
cons_msg('#', "Error Map Reserve %x\n", (t_vaddr) addr);
cons_msg('#', "After Map Reserve %x\n", (t_vaddr) addr);

 // region_dump(kasid);
 // region_dump(kasid);
}

