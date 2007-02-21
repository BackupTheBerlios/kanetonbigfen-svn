/*
** conf.c for  in /u/a2/fenet_v/svn/kaneton
**
** Made by fenet_v
** Login <fenet_v@epita.fr>
**
** Started on  Mon Feb 19 19:15:15 2007 vincent fenet
** Last update Wed Feb 21 15:03:45 2007 vincent fenet
*/

#include <klibc.h>
#include <kaneton.h>

extern int kasid;

void check_tests(void)
{
  check_1();
  /* printf("%i\n", kasid); */
  /* as_show(kasid); */
  i_segment segid;
  segment_reserve(kasid, 10, 0, &segid);
  o_segment *oseg;// = malloc(sizeof(o_segment));
  segment_get(segid, &oseg);
/*   segment_get(16777216, &oseg); */
}

extern m_segment* segment;

void check_1(void)
{
  /* printf("low=%i up=%i pages=%i\n", segment->start, segment->size + segment->start, segment->size/PAGESZ); */
/*   t_paddr res1; */
/*   segment_first_fit(2, &res1); */
/*   segment_space(0, 4, &res1); */
/*   segment_dump(); */
/*   t_paddr res2; */
/*   segment_first_fit(4, &res2); */
/*   segment_dump(); */
/*   segment_remove(res1); */
/*   segment_dump(); */
/*   segment_first_fit(1, &res1); */
/*   segment_dump(); */
/*   segment_first_fit(1, &res1); */
  segment_dump();
}
