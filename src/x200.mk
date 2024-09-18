SHELL=/bin/bash
ARCH=$(shell uname)
ifdef NDEBUG
DEBUG=
else # DEBUG
DEBUG=g
endif # ?NDEBUG
RM=rm -rfv
AR=xiar
ARFLAGS=-qnoipo -lib rsv
CC=icx -std=gnu18
CPUFLAGS=-DUSE_INTEL -DUSE_X64 -fPIC -fexceptions -fasynchronous-unwind-tables -fno-omit-frame-pointer -mprefer-vector-width=512 -qopenmp -traceback -vec-threshold0
ifdef TEST
CPUFLAGS += -DTEST=$(TEST)
endif # TEST
C18FLAGS=$(CPUFLAGS)
FPUFLAGS=-fp-model=precise -fp-speculation=safe -fprotect-parens -fma -no-ftz -fimf-precision=high -fimf-use-svml=true
ifndef MARCH
MARCH=common-avx512
endif # !MARCH
ifdef NDEBUG
OPTFLAGS=-O$(NDEBUG) -x$(MARCH) -fno-math-errno -inline-level=2
DBGFLAGS=-DNDEBUG -qopt-report=3
else # DEBUG
OPTFLAGS=-O0 -x$(MARCH)
DBGFLAGS=-$(DEBUG) -debug emit_column -debug extended -debug inline-debug-info -debug pubnames -debug parallel
endif # ?NDEBUG
LIBFLAGS=-D_GNU_SOURCE -I. -DUSE_MKL -I${MKLROOT}/include/intel64/lp64 -I${MKLROOT}/include
LDFLAGS=-rdynamic -static-libgcc -L. -lveckog$(TEST)$(DEBUG) -L${MKLROOT}/lib/intel64 -Wl,-rpath=${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm -ldl -lmemkind
CFLAGS=$(OPTFLAGS) $(DBGFLAGS) $(LIBFLAGS) $(C18FLAGS) $(FPUFLAGS)
