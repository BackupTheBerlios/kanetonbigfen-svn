/*
** conf.c for  in /u/a2/fenet_v/svn/kaneton
**
** Made by fenet_v
** Login <fenet_v@epita.fr>
**
** Started on  Mon Feb 19 19:15:15 2007 vincent fenet
Last update Tue Mar 27 19:20:28 2007 FENET Vincent
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

void coin(void)
{
  printf("coin\n");
  while (1)
    ;
}

void check_1(void)
{
  int i, j;
  i = 42;
  j = 0;
  i = i / j;
  /* printf(" ready... "); */
/*   mysleep(100); */
//  idt_init();
/*   printf(" initialized... "); */
/*   mysleep(100); */
//  event_dump();
//  u_event_handler c;
//  c.function = coin;
/*   for (i=0; i<256; i++) */
/*     event_reserve(i, EVENT_FUNCTION, c); */
//  for (i=0; i<256; i++)
//    set_gate( i, (unsigned long)dbz, 257);
  //event_dump();
//  mysleep(200);
  /* asm volatile ("int $1\n"); */
  //i = 42 / j;
/*   printf(" div 0... "); */
/*   mysleep(100); */
/*   printf("\n"); */
}

void ia32_pf_handler(t_id id,
		     t_uint32 error_code)
{
  t_uint32 addr;
  SCR2(addr);
  printf("#PF @ %p\n", addr);
  while (1)
    ;
}

void check_2()
{
  event_reserve(0, EVENT_FUNCTION, EVENT_HANDLER(ia32_pf_handler));
}

void check_tests(void)
{
  check_2();
  printf("end.\n");
}
