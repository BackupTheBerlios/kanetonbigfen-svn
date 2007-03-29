#include <klibc.h>
#include <kaneton.h>

extern m_region*	region;
extern i_as		kasid;
extern i_task		ktask;

void		check_tests(void)
{
  i_as		as;

/* if (as_reserve(ktask, &as) != ERROR_NONE) */
/*   cons_msg('+', "AS Reserve failed !\n"); */
  cons_msg('+', "Ending Tests\n");
}
