export KANETON_USER=lou.bigard
export KANETON_MACHINE=vj-linux::ibm-pc.ia32-virtual
export KANETON_SHELL=/bin/bash
LANG=us gmake init proto build install
# && ~bucchi_m/qemu/run.sh -fda /tmp/kaneton.img -s -S
