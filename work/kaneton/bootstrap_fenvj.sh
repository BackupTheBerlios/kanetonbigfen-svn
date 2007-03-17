export KANETON_USER=fenet_v
export KANETON_MACHINE=vj-linux::ibm-pc.ia32-virtual
export KANETON_SHELL=/bin/bash
alias gcc-3.3 gcc
gmake init proto build install
# && ~bucchi_m/qemu/run.sh -fda /tmp/kaneton.img -s -S
