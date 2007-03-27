export KANETON_USER=lou.bigard
export KANETON_MACHINE=lab-gistr::ibm-pc.ia32-virtual
export KANETON_SHELL=/bin/bash
make install && qemu -fda /tmp/kaneton.img
