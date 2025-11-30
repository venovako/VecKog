# MARCH=common-avx512 for KNLs
SHELL=/bin/bash
ARCH=$(shell uname)
RM=rm -rfv
AR=ar
ARFLAGS=rsv
include ../../libpvn/src/pvn.mk
CC=$(PVN_CC)
CFLAGS=$(PVN_CFLAGS) -fimf-use-svml=true $(PVN_CPPFLAGS) -DUSE_INTEL -DUSE_X64 -DUSE_MKL -I. -I${MKLROOT}/include/intel64/lp64 -I${MKLROOT}/include
ifdef TEST
CFLAGS += -DTEST=$(TEST)
endif # TEST
LDFLAGS=$(PVN_LDFLAGS) -L. -lveckog$(TEST) -L${MKLROOT}/lib -Wl,-rpath=${MKLROOT}/lib -lmkl_intel_lp64 -lmkl_sequential -lmkl_core $(shell if [ -L /usr/lib64/libmemkind.so ]; then echo '-lmemkind'; fi) $(PVN_LIBS)
