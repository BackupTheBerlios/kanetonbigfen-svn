/*
 * licence
 *
 * project       kaneton
 *
 * file          /tmp/tutu/kaneton/env/users/student/conf.h
 *
 * created       matthieu bucchianeri   [fri dec  2 18:50:46 2005]
 * updated       matthieu bucchianeri   [wed feb  7 11:19:40 2007]
 */

#ifndef KANETON_CONF_H
#define KANETON_CONF_H		1

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <core/debug.h>

/*
 * ---------- macros ----------------------------------------------------------
 */

/*
 * the title of your kernel which will be displayed by the grub
 * bootloader and by your kernel during its bootstrap.
 */

#define CONF_TITLE		"kaneton"

/*
 * the current release version.
 */

#define CONF_VERSION		"0.0.1"

/*
 * the current kernel mode, release, development.
 *
 * the development mode means that the current kernel was not
 * entirely tested while the release mode indicates that the kernel can
 * be used.
 */

#define CONF_MODE_DEVELOPMENT	(1 << 0)
#define CONF_MODE_RELEASE	(1 << 1)

#define CONF_MODE		MODE_DEVELOPMENT

/*
 * which algorithm to use in segment
 */

#define SEGMENT_LOOKUP_ALGORITHM	FIT_FIRST

/*
 * which algorithm to use in region
 */

#define REGION_LOOKUP_ALGORITHM		FIT_FIRST

/*
 * which fit method to use in alloc
 */

#define ALLOC_FIT	FIT_FIRST

/*
 * this define activates the statistics
 */

#undef CONF_STATS

/*
 * this define starts the tests by hand.
 */

#undef CONF_ENABLE_CHECK

/*
 * the configuration debug
 */

#define CONF_DEBUG							\
  (0)

/*
 * the machine-dependent configuration debug
 */

#define CONF_MACHDEP_DEBUG						\
  (0)

/*
 * serial port debug
 */

#undef SERIAL

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../../core/conf/conf.c
 */

/*
 * ../../core/conf/conf.c
 */


/*
 * eop
 */

#endif
