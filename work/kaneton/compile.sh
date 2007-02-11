cd ~/kaneton
export KANETON_USER=fensoft
export KANETON_MACHINE=linux::ibm-pc.ia32-virtual
export KANETON_SHELL=/bin/bash
make install && qemu -fda kaneton.img
