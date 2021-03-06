/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /home/buckman/kaneton/libs/klibc/libstring/strncmp.c
 *
 * created       julien quintard   [fri feb 11 02:56:44 2005]
 * updated       matthieu bucchianeri   [tue jan 24 11:56:34 2006]
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <klibc.h>

/*
 * ---------- functions -------------------------------------------------------
 */

int			strncmp(const char*			s1,
				const char*			s2,
				size_t				n)
{
  u_int			i;
  u_int			j;

  for (i = 0, j = 0; s1[i] && s2[j] && i < n; i++, j++)
    if (s1[i] != s2[j])
      return (s1[i] - s2[j]);

  if (s1[i] != s2[j])
    return (s1[i] - s2[j]);

  return (0);
}
