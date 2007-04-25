#include <klibc.h>
#include <kaneton.h>

extern m_region*	region;
extern i_as		kasid;
extern i_task		ktask;

/*
 * Mapping
 */

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

/* void sched_switch(void) */
/* { */
/*  cons_msg('!', "TIC\n"); */
/* } */
void entry_point()
{
printf("This is a thread.\n");
/* */
/* I MUST NOT RETURN ! */
/* */
while (1)
;
}

void getkey(void)
{
  char i,j;
  INB(0x60, i);
  INB(0x64, j);
 if (i < 128 && i > 0 && kbdus[i][0])
/*     printf("%s", kbdus[i]); */
  if (kbdus[i][0] == 's')
     printf("Comment dit on Alice au Pays des Merveilles en Arabe ? \nFatima chez Tatie ! \nYuuuurk Yuuuuurk !\n(Ceci etait une blague debile et xenophobe, veuillez envoyer les missiles chez Carlos, Les Grosses Tetes, et tous les editeurs de blagues)\n");

}


void		check_tests(void)
{
i_task tsk;
i_as as;
i_thread thr;
o_thread* o;
t_thread_context ctx;
t_stack stack;

event_reserve(32+1, EVENT_FUNCTION, EVENT_HANDLER(getkey));
/* if (task_reserve(TASK_CLASS_PROGRAM, */
/* TASK_BEHAV_INTERACTIVE, */
/* TASK_PRIOR_INTERACTIVE, */
/* &tsk) != ERROR_NONE) */
/* cons_msg('+', "task_reserve failed !\n"); */
/* if (as_reserve(tsk, &as) != ERROR_NONE) */
/* cons_msg('+', "as_reserve failed !\n"); */
/* if (thread_reserve(tsk, THREAD_PRIOR, &thr) != ERROR_NONE) */
/* cons_msg('+', "thread_reserve failed !\n"); */
/* stack.base = 0; */
/* stack.size = THREAD_MIN_STACKSZ; */
/* if (thread_stack(thr, stack) != ERROR_NONE) */
/* cons_msg('+', "thread_stack failed !\n"); */
/* if (thread_get(thr, &o) != ERROR_NONE) */
/* cons_msg('+', "thread_get failed !\n"); */
/* ctx.sp = o->stack + o->stacksz - 16; */
/* ctx.pc = (t_vaddr)entry_point; */
/* if (thread_load(thr, ctx) != ERROR_NONE) */
/* cons_msg('+', "thread_load failed !\n"); */
/* if (task_state(tsk, SCHED_STATE_RUN) != ERROR_NONE) */
/* cons_msg('+', "task_state failed !\n"); */

/*
/*   i_timer		idtimer; */
/*   i_timer		idtimer2; */
/*   o_timer*		tmp; */
/*   i_thread		thre1; */

/*   i_task		taskid; */
/*   i_as			tasid; */
/*   char*			buf; */
/*   char*			buf3; */
/*   o_as*			as; */
/*   o_as*			tas; */

/*   as_get(kasid, &as); */

/*   buf = mmap(0, 4096 * 2, PROT_READ, 0, 0, 0); */
/*   buf3 = mmap(0, 4096 * 2, PROT_READ | PROT_WRITE, 0, 0, 0); */

/*   if (task_reserve(TASK_CLASS_CORE, */
/* 	       TASK_BEHAV_INTERACTIVE, */
/* 	       TASK_PRIOR_INTERACTIVE, */
/* 	       &taskid) != ERROR_NONE) */
/*     printf("[ERROR] TASK RESERVE\n"); */
/*   if (as_reserve(taskid, &tasid) != ERROR_NONE) */
/*     printf("[ERROR] AS RESERVE\n"); */
/*   as_get(tasid, &tas); */


/*   if (task_reserve(TASK_CLASS_PROGRAM, TASK_BEHAV_TIMESHARING, TASK_PRIOR_TIMESHARING, &taskid) != ERROR_NONE) */
/*     cons_msg('+', "TASK Reserve failed !\n"); */

/*   if (as_reserve(taskid, &as) != ERROR_NONE) */
/*     cons_msg('+', "AS Reserve failed !\n"); */

/*   thread_reserve(taskid, 150, &thre1); */

/*   if (sched_add(thre1) != ERROR_NONE); */
/*     cons_msg('+', "SCHED Add failed !\n"); */

/*   if (task_state(taskid, SCHED_STATE_RUN) != ERROR_NONE) */
/*     cons_msg('+', "TASK Run failed !\n"); */

/*   task_dump(); */
/*   thread_dump(); */



/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 120, TIMER_REPEAT_ENABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 125, TIMER_REPEAT_ENABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 156, TIMER_REPEAT_DISABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 20, TIMER_REPEAT_ENABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_reserve(EVENT_FUNCTION, TIMER_HANDLER(sched_switch), */
/* 20, TIMER_REPEAT_ENABLE, */
/* &idtimer) != ERROR_NONE) */
/*    cons_msg('+', "Timer Reserve failed !\n"); */

/* if (timer_dump() != ERROR_NONE) */
/*    cons_msg('+', "Timer Dump failed !\n"); */

/* if (timer_show(idtimer)  != ERROR_NONE) */
/*    cons_msg('+', "Timer Show failed !\n"); */

/* if (timer_get(idtimer, &tmp)  != ERROR_NONE) */
/*    cons_msg('+', "Timer Get failed !\n"); */



  cons_msg('+', "Ending Tests\n");
}
