/*
** conf.c for  in /u/a2/fenet_v/svn/kaneton
**
** Made by fenet_v
** Login <fenet_v@epita.fr>
**
** Started on  Mon Feb 19 19:15:15 2007 vincent fenet
Last update Fri Mar 30 19:31:07 2007 FENET Vincent
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
  int a = 1;
  int b = 0;
  int c;
  c = a / b;
}

void check_4();
static int go = 0;
static int tic = 0;
static int toc = 0;

char *kbdus[128] =
{
    "",  "\0x17", "1", "2", "3", "4", "5", "6", "7", "8",	/* 9 */
  "9", "0", "-", "=", "\b",	/* Backspace */
  "\t",			/* Tab */
  "q", "w", "e", "r",	/* 19 */
  "t", "y", "u", "i", "o", "p", "[", "]", "\r\n",	/* Enter key */
    "",			/* 29   - Control */
  "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",	/* 39 */
 "\"", "`",   "",		/* Left shift */
 "\\", "z", "x", "c", "v", "b", "n",			/* 49 */
  "m", ",", ".", "/",   "",				/* Right shift */
  "*",
    "",	/* Alt */
  " ",	/* Space bar */
    "",	/* Caps lock */
    "",	/* 59 - F1 key ... > */
    "",   "",   "",   "",   "",   "",   "",   "",
    "",	/* < ... F10 */
    "",	/* 69 - Num lock*/
    "",	/* Scroll Lock */
    "",	/* Home key */
    "",	/* Up Arrow */
    "",	/* Page Up */
  "-",
    "",	/* Left Arrow */
    "",
    "",	/* Right Arrow */
  "+",
    "",	/* 79 - End key*/
    "",	/* Down Arrow */
    "",	/* Page Down */
    "",	/* Insert Key */
    "",	/* Delete Key */
    "",   "",   "",
    "",	/* F11 Key */
    "",	/* F12 Key */
    "",	/* All other keys are undefined */
};

void getkey(void)
{
  char i,j;
  INB(0x60, i);
  INB(0x64, j);
  if (i < 128 && i > 0 && kbdus[i][0])
    printf("%s", kbdus[i]);
}

void check_3()
{
  event_reserve(32+1, EVENT_FUNCTION, EVENT_HANDLER(getkey));
}

void tick()
{
  if (go)
    if (!(toc = (toc + 1) % 100))
      printf("\n %d ", tic++);
}

void check_4()
{
  timer_init();
  event_reserve(32+0, EVENT_FUNCTION, EVENT_HANDLER(tick));
}

void check_5()
{
  event_reserve(32+1, EVENT_FUNCTION, EVENT_HANDLER(getkey));
  event_reserve(32+0, EVENT_FUNCTION, EVENT_HANDLER(tick));
}

void check_tests(void)
{
  i_timer res = 42;
  timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(tick), 200, TIMER_REPEAT_ENABLE, &res);
  timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(tick), 200, TIMER_REPEAT_ENABLE, &res);
  timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(tick), 200, TIMER_REPEAT_ENABLE, &res);
  timer_dump();

  o_timer *o;
  timer_get(res, &o);
  printf("[%x/handlerfunc]", o->handler.function);

  event_reserve(32+1, EVENT_FUNCTION, EVENT_HANDLER(getkey));
  printf("end.\n");
}
