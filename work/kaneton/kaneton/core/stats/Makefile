##
## licence       kaneton licence
##
## project       kaneton
##
## file          /home/mycure/kaneton/kaneton/core/stats/Makefile
##
## created       julien quintard   [fri feb 11 02:57:24 2005]
## updated       julien quintard   [sat apr  1 23:39:11 2006]
##

#
# ---------- dependencies -----------------------------------------------------
#

include			../../../env/.env.mk

#
# ---------- directives -------------------------------------------------------
#

.PHONY:		clear proto dep

#
# ---------- variables --------------------------------------------------------
#

STATS_LO		:=		stats.lo

STATS_C			:=		stats.c

STATS_O			:=		$(STATS_C:.c=.o)

STATS_INCLUDE		:=		$(_CORE_INCLUDE_DIR_)/stats.h

CFLAGS			+=		-D___kernel

#
# ---------- rules ------------------------------------------------------------
#

$(STATS_LO):		$(STATS_O)
	$(call remove,$(STATS_LO),)

	$(call archive,$(STATS_LO),$(STATS_O),)

clear:
	$(call remove,$(STATS_O),)

	$(call remove,$(STATS_LO),)

	$(call purge,)

proto:
	$(call prototypes,$(STATS_INCLUDE),)

dep:
	$(call remove,$(_MAKEFILE_MK_),)

	$(call dependencies,$(STATS_C),$(_MAKEFILE_MK_),)

#
# ---------- dependencies -----------------------------------------------------
#

-include		./$(_MAKEFILE_MK_)
