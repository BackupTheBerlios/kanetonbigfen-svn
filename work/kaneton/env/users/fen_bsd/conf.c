/*
** conf.c for  in /u/a2/fenet_v/svn/kaneton
**
** Made by fenet_v
** Login <fenet_v@epita.fr>
**
** Started on  Mon Feb 19 19:15:15 2007 vincent fenet
** Last update Thu Feb 22 00:19:49 2007 vincent fenet
*/

#include <klibc.h>
#include <kaneton.h>
int mysleep(void);
void check_1(void);
void check_2(void);

extern int kasid;

int num = 0;
int mysleep(void)
{
  printf("sleep\n");
  int i, j, ret;
  for (j = 0; j != 200; j++)
    for (i = 0; i != 100000; i++)
      ret = i + j;
  return ret;
}


void check_tests(void)
{
  check_2();
}

void check_2(void)
{
  printf("%i\n", kasid);
  mysleep();
  as_show(kasid);
  i_segment segid;
  mysleep();
  segment_reserve(kasid, 110 * PAGESZ, 0, &segid);
  mysleep();
  o_segment *oseg;
  mysleep();
  segment_get(segid, &oseg);
  mysleep();
  segment_dump();
  printf("look at 110 at the beginning\n");
  mysleep();
  printf("end of check_2\n");
}

extern m_segment* segment;
void check_1(void)
{
  t_paddr res1;
  segment_first_fit(102, &res1);
  segment_space(0, 104, &res1);
  segment_dump();
  t_paddr res2;
  segment_first_fit(104, &res2);
  mysleep();
  segment_dump();
  segment_remove(res1);
  mysleep();
  segment_dump();
  segment_first_fit(101, &res1);
  mysleep();
  segment_dump();
  segment_first_fit(101, &res1);
  mysleep();
  segment_dump();
}
