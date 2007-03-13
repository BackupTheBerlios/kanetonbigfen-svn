/*
** conf.c for  in /u/a2/fenet_v/svn/kaneton
**
** Made by fenet_v
** Login <fenet_v@epita.fr>
**
** Started on  Mon Feb 19 19:15:15 2007 vincent fenet
** Last update Tue Mar 13 13:15:19 2007 fensoft
*/

#include <klibc.h>
#include <kaneton.h>
#define MYCHECK(_str_, _fct_)                                    \
{	  			                                 \
  int _res_ = (int)_fct_;                                        \
  printf("%s...%s\n", _str_, _res_ ? "ok" : "ko");               \
  if (!_res_)                                                    \
    while (1)                                                    \
      ;                                                          \
}

extern int kasid;

int sleep_num = 1;
int mysleep(int k)
{
  //  printf("sleep time=%3ims seq=%3i\n", k, sleep_num++);
  printf("%i,", sleep_num++);
  int i, j, ret;
  for (j = 0; j != k; j++)
    for (i = 0; i != 100000; i++)
      ret = i + j;
  return ret;
}


void check_tests(void)
{
  check_5();
}

void check_a(void)
{
/*   i_task taskid; */
/*   task_reserve(TASK_CLASS_PROGRAM, TASK_BEHAV_TIMESHARING, TASK_PRIOR_TIMESHARING, */
/* 	       &taskid); */
/*   i_as asid; */
/*   as_reserve(taskid, &asid); */
/*   o_as* as; */
/*   as_get(asid, &as); */
/*   region_dump2(as); */
/*   segment_dump2(asid); */
/*   i_segment segid; */
/*   segment_count(); */
/*   segment_reserve(as->asid, 1234, 0, &segid); */
/*   printf("t1(valid)  :%i\n", ERROR_NONE == (int)segment_perms(segid, PERM_READ)); */
/*   printf("t2(unvalid):%i\n", ERROR_UNKNOWN == (int)segment_perms(segid, 0)); */
/*   printf("t3(too big):%i\n", ERROR_UNKNOWN == (int)segment_perms(segid, 42)); */
/*   cons_msg('+', "end of check_9\n"); */
}

// CHECK SEGMENT_PERMS (valid perms ?)
void check_9(void)
{
  i_task taskid;
  task_reserve(TASK_CLASS_PROGRAM, TASK_BEHAV_TIMESHARING, TASK_PRIOR_TIMESHARING,
	       &taskid);
  i_as asid;
  as_reserve(taskid, &asid);
  o_as* as;
  as_get(asid, &as);
  region_dump2(as);
  segment_dump2(asid);
  i_segment segid;
  segment_count();
  segment_reserve(as->asid, 1234, 0, &segid);
  printf("t1(valid)  :%i\n", ERROR_NONE == (int)segment_perms(segid, PERM_READ));
  printf("t2(unvalid):%i\n", ERROR_UNKNOWN == (int)segment_perms(segid, 0));
  printf("t3(too big):%i\n", ERROR_UNKNOWN == (int)segment_perms(segid, 42));
  cons_msg('+', "end of check_9\n");
}

// CHECK SEGMENT_FLUSH
void check_8(void)
{
  printf("kernel asid=%i\n", kasid);
  i_task taskid;
  task_reserve(TASK_CLASS_PROGRAM, TASK_BEHAV_TIMESHARING, TASK_PRIOR_TIMESHARING,
	       &taskid);
  i_as asid;
  as_reserve(taskid, &asid);
  o_as* as;
  as_get(asid, &as);
  region_dump2(as);
  segment_dump2(asid);
  i_segment res;
  segment_count();
  segment_reserve(as->asid, 1234, 0, &res);
  segment_count();
  region_dump2(as);
  segment_dump2(asid);
  segment_flush(asid);
  segment_count();
  cons_msg('+', "end of check_8\n");
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
  cons_msg('+', "end of check_7\n");
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
  cons_msg('+', "end of check_6\n");
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
  char* test = "t";
  MYCHECK("writting", segment_write(segid, 0, test, 10) == ERROR_NONE);
  char* res =  "f";
  MYCHECK("reading", segment_read(segid, 0, res, 10) == ERROR_NONE);
  //  MYCHECK("checking r&w", test[0] == res[0]);
  MYCHECK("checking r&w", strcmp(test, res) == 0);
  //  printf("? %s%s\n", test, res);
  cons_msg('+', "end of check_5\n");
}

void check_4(void)
{
  o_as* as;
  as_get(kasid, &as);
  t_vaddr res;
  region_space(as, 169 * PAGESZ, &res);
  printf("%x\n", res);
  region_space(as, 169 * PAGESZ, &res);
  printf("%x\n", res);
  region_dump2(as);
  cons_msg('+', "end of check_3\n");
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
  cons_msg('+', "end of check_3\n");
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
  cons_msg('+', "end of check_2\n");
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
  cons_msg('+', "end of check_2\n");
  mysleep(2000);
}
