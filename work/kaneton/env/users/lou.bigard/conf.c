#include <klibc.h>
#include <kaneton.h>

extern m_region*	region;
extern i_as		kasid;

static long		pg1024[1024] =
  {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //100

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //200

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //300

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //400

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //500

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //600

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //700

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //800

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //900

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, //1000

    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    0, 1, 2, 3
  };

void		check_tests(void)
{
  i_segment	segid;
  i_region	regid;
  i_segment	segid2;
  i_region	regid2;
  i_region	regid3;
  t_error	err;
  o_as*		oas;
  long		pg10[10] = { 100, 100, 100, 100, 100,  100, 100, 100, 100, 100 };
  long		*pgp;
  int		i;

/*   cons_msg('!', "segment_reserve 15724544 ... "); */
  err = segment_reserve(kasid, 15 * 4096, PERM_READ | PERM_WRITE, &segid);
  if (err == ERROR_NONE)
    {
      cons_msg('!', "seg_res ok... ");
      err = region_reserve(kasid, segid, 0, REGION_OPT_PRIVILEGED, 0, 15 * 4096, &regid);
      if (err == ERROR_NONE)
	cons_msg('!', "reg_res ok\n");
      else
	cons_msg('!', "reg_res failed\n");
    }
  else
    cons_msg('!', "seg_res failed\n");
/*   if (as_get(kasid, &oas) != ERROR_NONE) */
/*     SEGMENT_LEAVE(segment, ERROR_UNKNOWN); */

/* /\*   printf("regid = %X\n", regid); *\/ */

/*   if (segment_write(segid, 0, pg1024, sizeof(pg1024)) != ERROR_NONE) */
/*     printf("write ouille\n"); */

/*   cons_msg('!', "segment_reserve 4096 ... "); */
/*   err = segment_reserve(kasid, 4096, PERM_READ | PERM_WRITE, &segid2); */
/*   if (err == ERROR_NONE) */
/*     { */
/*       cons_msg('!', "seg_res ok... "); */
/*       err = region_reserve(kasid, segid2, 0, REGION_OPT_PRIVILEGED, 0, 4096, &regid2); */
/*       if (err == ERROR_NONE) */
/* 	cons_msg('!', "reg_res ok\n"); */
/*       else */
/* 	cons_msg('!', "reg_res failed\n"); */
/*     } */
/*   else */
/*     cons_msg('!', "seg_res failed\n"); */
/*   printf("segid2 = %X\n", segid2); */
/*   printf("regid2 = %X\n", regid2); */

/*   if (segment_read(segid, 0, pg10, sizeof(pg10)) != ERROR_NONE) */
/*     printf("read ouille\n"); */

/*   for (i = 0; i < 10; i++) */
/*     printf("%i ", pg10[i]); */
/*   printf("\n"); */

/*   if (segment_copy(segid2, 0, segid, 5, sizeof(pg10)) != ERROR_NONE) */
/*     printf("read ouille\n"); */

/*   if (segment_perms(segid, PERM_READ | PERM_WRITE | PERM_EXEC) != ERROR_NONE) */
/*     printf("seg perm 1 GARGL\n"); */

/*   if (segment_perms(segid, 8) != ERROR_NONE) */
/*     printf("seg perm 2 GARGL\n"); */

/*   if (segment_perms(segid, -345) != ERROR_NONE) */
/*     printf("seg perm 3 GARGL\n"); */

/*   if (segment_clone(kasid, segid, &segid2) != ERROR_NONE) */
/*     printf("OUF!!!\n"); */
/**********************************************************************/
  if (region_release(kasid, regid) != ERROR_NONE)
    printf("reg rel regid ouille\n");

  if (segment_release(segid) != ERROR_NONE)
    printf("seg rel segid ouille\n");
/**********************************************************************/
/*   if (segment_release(segid2) != ERROR_NONE) */
/*     printf("seg rel segid ouille\n"); */


/*   if (segment_read(segid2, 0, pg10, sizeof(pg10)) != ERROR_NONE) */
/*     printf("read ouille 2\n"); */

/*   for (i = 0; i < 10; i++) */
/*     printf("%i ", pg10[i]); */


/*   pgp = malloc(sizeof(pg1024)); */

/*   if (segment_read(segid2, 0, pgp, sizeof(pg1024)) != ERROR_NONE) */
/*     printf("read ouille 2\n"); */

/*   for (i = 1014; i <= 1023; i++) */
/*     printf("%i ", pgp[i]); */
/*    region_show(kasid, 0x102000); */
/*    region_show(kasid, 0x104000); */
/*    region_show(kasid, 0x10C000); */
/*    region_show(kasid, 0x10E000); */

/*   if (region_release(kasid, regid2) != ERROR_NONE) */
/*     printf("reg rel regid2 ouille\n"); */

/*   if (segment_release(segid2) != ERROR_NONE) */
/*     printf("seg rel segid2 ouille\n"); */

  cons_msg('+', "TESTS FINIS\n");
}
