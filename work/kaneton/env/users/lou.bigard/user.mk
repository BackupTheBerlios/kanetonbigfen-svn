##
## licence       kaneton licence
##
## project       kaneton
##
## file          /home/buckman/kaneton/env/users/student/user.mk
##
## created       matthieu bucchianeri   [mon jan 30 23:32:09 2006]
## updated       matthieu bucchianeri   [mon jan 30 23:32:10 2006]
##

#
# ---------- information ------------------------------------------------------
#
# this file contains specific user makefile dependencies, rules, variables
# etc..
#

# disable checks
_CHECK_LO_	:= $(_CORE_CONF_DIR_)/conf.lo

# for using gdb with qemu
_CFLAGS_	+=	-ggdb
