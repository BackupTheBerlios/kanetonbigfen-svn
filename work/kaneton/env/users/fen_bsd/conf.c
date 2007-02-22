/*
** conf.c for  in /u/a2/fenet_v/svn/kaneton
**
** Made by fenet_v
** Login <fenet_v@epita.fr>
**
** Started on  Mon Feb 19 19:15:15 2007 vincent fenet
** Last update Thu Feb 22 11:43:42 2007 vincent fenet
*/

#include <klibc.h>
#include <kaneton.h>

extern int kasid;

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


void check_tests(void)
{
  check_2();
}

void check_2(void)
{
  printf("%i\n", kasid);
  mysleep(100);
  as_show(kasid);
  i_segment segid;
  mysleep(100);
  segment_reserve(kasid, 110 * PAGESZ, 0, &segid);
  mysleep(100);
  o_segment *oseg;
  mysleep(100);
  segment_get(segid, &oseg);
  mysleep(100);
  segment_dump();
  printf("look at 110 at the beginning\n");
  mysleep(100);
  segment_release(segid);
  segment_dump();
  printf("look at 110 deletion at the beginning\n");
  mysleep(100);
  if (segment_get(segid, &oseg) == ERROR_NONE)
    printf("found, bugged !\n");
  else
    printf("not found, seems ok!\n");
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
  mysleep(200);
  segment_dump();
  segment_remove(res1);
  mysleep(200);
  segment_dump();
  segment_first_fit(101, &res1);
  mysleep(200);
  segment_dump();
  segment_first_fit(101, &res1);
  mysleep(200);
  segment_dump();
}
