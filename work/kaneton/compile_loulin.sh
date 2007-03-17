export KANETON_USER=lou.bigard
export KANETON_MACHINE=linux::ibm-pc.ia32-virtual
export KANETON_SHELL=/bin/bash
gmake install && ~bucchi_m/qemu/run.sh -fda /tmp/kaneton.img
