/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/kaneton/include/arch/ibm-pc.ia32-virtual/core/thread.h
 *
 * created       renaud voltz   [tue apr  4 03:10:52 2006]
 * updated       matthieu bucchianeri   [wed feb  7 11:09:47 2007]
 */

#ifndef IA32_CORE_THREAD_H
#define IA32_CORE_THREAD_H       1

/*
 * ---------- dependencies ----------------------------------------------------
 */

//#include <core/thread.h>

/*
 *
 */

typedef struct
{
  t_ia32_tss*		tss;
}			am_thread;

/*
 * ---------- types -----------------------------------------------------------
 */

typedef struct
{
  t_uint32 eflags;
  t_uint32 cs;
  t_uint32 eip;
  //  t_uint32 error;

  t_uint32 ds;
  t_uint32 es;
  t_uint32 fs;
  t_uint32 gs;
  t_uint32 eax;
  t_uint32 ebx;
  t_uint32 ecx;
  t_uint32 edx;
  t_uint32 esi;
  t_uint32 edi;

  t_uint32 cr3;

  t_uint32 ss;
  t_uint32 esp;
  t_uint32 ebp;
} ao_thread_named;

typedef union
{
  ao_thread_named named;
  t_uint32 unamed[17];
} ao_thread;

/* typedef struct */
/* { */

/* }			ao_thread; */

/*
 * ---------- macro functions -------------------------------------------------
 */

#define         machdep_include_thread()				\
  extern d_thread                thread_dispatch

#define         machdep_call_thread(_function_, _args_...)		\
  (									\
    {									\
      t_error   _r_ = ERROR_NONE;					\
									\
      if (thread_dispatch._function_ != NULL)				\
        _r_ = thread_dispatch._function_(_args_);			\
									\
      _r_;								\
    }									\
  )

#define         machdep_data_m_thread()					\
  am_thread		machdep

#define         machdep_data_o_thread()					\
  ao_thread		machdep

#endif
