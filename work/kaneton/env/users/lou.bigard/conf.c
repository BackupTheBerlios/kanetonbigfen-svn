/*
** conf.c for Kaneton in /goinfre/goinfre/SVN/kaneton
**
** Made by lou bigard
** Login   <bigard_l@epita.fr>
**
** Started on  Wed Feb 21 22:56:03 2007 lou bigard
** Last update Thu Feb 22 12:01:39 2007 lou bigard
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


if (as_get(kasid, &oas) != ERROR_NONE)
return;

 cons_msg('#', "Testing Segment Reserve\n");

 // as_show(kasid);
  if (segment_reserve(kasid, 10 * PAGESZ, PERM_READ | PERM_WRITE, &segid) != ERROR_NONE)
   cons_msg('!', "Error Segment Reserve\n");

cons_msg('#', "After Segmentt Reserve\n");
/* as_show(kasid);*/

/* region_reserve(i_as			asid, */
/* 				       i_segment		segid, */
/* 				       t_paddr			offset, */
/* 				       t_opts			opts, */
/* 				       t_vaddr			address, */
/* 				       t_vsize			size, */
/* 	       i_region*		regid); */
}
