/*
** conf.c for  in /u/a2/fenet_v/svn/kaneton
**
** Made by fenet_v
** Login <fenet_v@epita.fr>
**
** Started on  Mon Feb 19 19:15:15 2007 vincent fenet
** Last update Thu Feb 22 18:33:07 2007 vincent fenet
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
/*   check_1(); */
/*   check_2(); */
/*   check_3(); */
/*   check_5(); */
  check_4();
/*   mysleep(2000); */
/*   check_7(); */
}

void check_7(void)
{
  mysleep(100);
  o_as* as;
  as_get(kasid, &as);
  region_dump2(as);
  mysleep(1000);
  t_vaddr ret;
  region_space(as, 142 * PAGESZ + 1, &ret);
  region_dump2(as);
  printf("end of check_7\n");
}

void check_6(void)
{
  i_task taskid;
  mysleep(100);
  task_reserve(TASK_CLASS_PROGRAM, TASK_BEHAV_TIMESHARING, TASK_PRIOR_TIMESHARING,
	       &taskid);
  printf("taskid=%i\n", taskid);
  mysleep(100);
  i_as asid;
  as_reserve(taskid, &asid);
  mysleep(100);
  o_as* as;
  as_get(asid, &as);
  mysleep(100);
  region_dump2(as);
  mysleep(100);
/*   region_add_sorted(as, 1000, 2000); */
  printf("end of check_6\n");
}

void check_5(void)
{
  i_task taskid;
  task_reserve(TASK_CLASS_PROGRAM, TASK_BEHAV_TIMESHARING, TASK_PRIOR_TIMESHARING,
	       &taskid);
  i_as asid;
  as_reserve(taskid, &asid);
  /////
  i_segment segid;
  segment_reserve(asid, 20000, 0, &segid);
  /////
  char* test = "135792468";
  segment_write(segid, 0, test, 10);
  char* res =  "abcdefghi";
  segment_read(segid, 0, test, 10);
  printf("must be %s = %s\n", test, res);
  printf("end of check_5\n");
}

void check_4(void)
{
  o_as* as;
  as_get(kasid, &as);
  t_vaddr res;
  region_first_fit(as, 169 * PAGESZ, &res);
  printf("%i\n", res);
  region_first_fit(as, 169 * PAGESZ, &res);
  printf("%i\n", res);
  printf("end of check_3\n");
  mysleep(2000);
}

void check_3(void)
{
  i_task taskid;
  task_reserve(TASK_CLASS_PROGRAM, TASK_BEHAV_TIMESHARING, TASK_PRIOR_TIMESHARING,
	       &taskid);
  i_as asid;
  as_reserve(taskid, &asid);
  i_segment segid;
  segment_reserve(asid, 169 * PAGESZ, 0, &segid);
  segment_dump2(asid);
  printf("look at 169 at the beginning\n");
  mysleep(2000);
  segment_flush(asid);
  segment_dump2(asid);
  printf("look at * removal\n");
  printf("end of check_3\n");
  mysleep(2000);
}

void check_2(void)
{
  as_show(kasid);
  i_segment segid;
  segment_reserve(kasid, 110 * PAGESZ, 0, &segid);
  o_segment *oseg;
  segment_get(segid, &oseg);
  segment_dump();
  printf("look at 110 at the beginning\n");
  mysleep(2000);
  segment_release(segid);
  segment_dump();
  printf("look at 110 deletion at the beginning\n");
  mysleep(2000);
  if (segment_get(segid, &oseg) == ERROR_NONE)
    printf("found, bugged !\n");
  else
    printf("not found, seems ok!\n");
  printf("end of check_2\n");
  mysleep(2000);
}

extern m_segment* segment;
void check_1(void)
{
  t_paddr res1;
  segment_first_fit(102 * PAGESZ, &res1);
  segment_space(0, 104 * PAGESZ, &res1);
  segment_dump();
  printf("look at 102 104\n");
  mysleep(2000);
  t_paddr res2;
  segment_first_fit(104 * PAGESZ, &res2);
  segment_dump();
  printf("look at 102 104 104\n");
  mysleep(2000);
  segment_remove(res1);
  segment_dump();
  printf("look at 102 --- 104\n");
  mysleep(2000);
  segment_first_fit(101 * PAGESZ, &res1);
  segment_dump();
  printf("look at 102 101 --- 104\n");
  mysleep(2000);
  segment_first_fit(3 * PAGESZ, &res1);
  segment_dump();
  printf("look at 102 101 3 104\n");
  printf("end of check_2\n");
  mysleep(2000);
}
