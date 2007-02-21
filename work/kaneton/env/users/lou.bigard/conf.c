/*
** conf.c for Kaneton in /goinfre/goinfre/SVN/kaneton
**
** Made by lou bigard
** Login   <bigard_l@epita.fr>
**
** Started on  Wed Feb 21 22:56:03 2007 lou bigard
** Last update Thu Feb 22 00:45:54 2007 lou bigard
*/
#include <klibc.h>
#include <kaneton.h>

extern i_as kasid;

void			 check_tests(void)
{
  o_as*			 oas;
  o_segment*		oseg;
  o_region*		oreg;
  i_segment		segid;
  i_region		regid;

if (as_get(kasid, &oas) == ERROR_NONE)
return;

 printf("Testing Segment Reserve");
 if (segment_reserve(kasid, 10 * PAGESZ, PERM_READ | PERM_WRITE, &segid) == ERROR_NONE)
return;

}
