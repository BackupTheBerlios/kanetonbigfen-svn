export KANETON_USER=fen_bsd
export KANETON_MACHINE=netbsd-epita::ibm-pc.ia32-virtual
export KANETON_SHELL=/usr/pkg/bin/bash
export PATH=/u/prof/acu/pub/NetBSD/bin:$PATH
gmake install
# && ~bucchi_m/qemu/run.sh -fda /tmp/kaneton.img -s -S
