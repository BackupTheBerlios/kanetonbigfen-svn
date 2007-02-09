##
## licence       kaneton licence
##
## project       kaneton
##
## file          /tmp/tutu/kaneton/libs/Makefile
##
## created       julien quintard   [fri feb 11 02:28:05 2005]
## updated       matthieu bucchianeri   [wed feb  7 18:12:32 2007]
##

#
# ---------- dependencies -----------------------------------------------------
#

include			../env/.env.mk

#
# ---------- directives -------------------------------------------------------
#

.PHONY:		all clear proto dep

#
# ---------- variables --------------------------------------------------------
#

SUBDIRS			:=		klibc

ARCHSUBDIRS		:=		libia32

#
# ---------- rules ------------------------------------------------------------
#

all:
	$(call launch,Makefile,$(SUBDIRS),,)

clear:
	$(call launch,Makefile,$(SUBDIRS),clear,)

	$(call launch,Makefile,$(ARCHSUBDIRS),clear,)

	$(call purge,)

proto:
	$(call launch,Makefile,$(SUBDIRS),proto,)

	$(call launch,Makefile,$(ARCHSUBDIRS),proto,)

dep:
	$(call launch,Makefile,$(SUBDIRS),dep,)

	$(call launch,Makefile,$(ARCHSUBDIRS),dep,)
