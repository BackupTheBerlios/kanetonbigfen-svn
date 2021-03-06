/*
 * licence       kaneton licence
 *
 * project       kaneton
 *
 * file          /home/buckman/kaneton/kaneton/include/core/serial.h
 *
 * created       julien quintard   [fri feb 11 02:19:44 2005]
 * updated       matthieu bucchianeri   [sun jun 18 16:58:44 2006]
 */

#ifndef	CORE_SERIAL_H
#define	CORE_SERIAL_H		1

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <arch/machdep/machdep.h>

/*
 * ---------- macros ----------------------------------------------------------
 */

#define SERIAL_COM1		0x3f8
#define	SERIAL_COM2		0x2f8
#define SERIAL_COM3		0x3e8
#define SERIAL_COM4		0x2e8

#define	SERIAL_BR9600		0x0C
#define	SERIAL_BR19200		0x06
#define	SERIAL_BR38400		0x03
#define	SERIAL_BR57600		0x02
#define	SERIAL_BR115200		0x01

#define	SERIAL_8N1		0x03
#define	SERIAL_7N1		0x02
#define	SERIAL_8N2		0x07
#define	SERIAL_7N2		0x06

#define SERIAL_FIFO_14		0xC7
#define SERIAL_FIFO_8		0x87
#define	SERIAL_FIFO_4		0x47
#define SERIAL_FIFO_1		0x07

/*
 * ---------- types -----------------------------------------------------------
 */


/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../../core/debug/serial.c
 */

/*
 * ../../core/debug/serial.c
 */


/*
 * eop
 */

#endif
