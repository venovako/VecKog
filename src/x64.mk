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
CC=icc -std=c18
CPUFLAGS=-DUSE_INTEL -DUSE_X64 -fPIC -fexceptions -fno-omit-frame-pointer -qopenmp -rdynamic
ifdef TEST
CPUFLAGS += -DTEST=$(TEST)
endif # TEST
C18FLAGS=$(CPUFLAGS)
FPUFLAGS=-fma -fp-model source -no-ftz -no-complex-limited-range -no-fast-transcendentals -prec-div -prec-sqrt -fimf-precision=high -fimf-use-svml=true
ifdef NDEBUG
OPTFLAGS=-O$(NDEBUG) -xHost
DBGFLAGS=-DNDEBUG -qopt-report=5 -traceback -w3 -diag-disable=1572,2547,10397
else # DEBUG
OPTFLAGS=-O0 -xHost
DBGFLAGS=-$(DEBUG) -debug emit_column -debug extended -debug inline-debug-info -debug pubnames -traceback -check=stack,uninit -w3 -diag-disable=1572,2547,10397
ifneq ($(ARCH),Darwin) # Linux
DBGFLAGS += -debug parallel
endif # ?Linux
FPUFLAGS += -fp-stack-check
endif # ?NDEBUG
LIBFLAGS=-I. -DUSE_MKL -I${MKLROOT}/include/intel64/lp64 -I${MKLROOT}/include
LDFLAGS=-L. -lveckog$(DEBUG)
ifeq ($(ARCH),Darwin)
LDFLAGS += -L${MKLROOT}/lib -Wl,-rpath,${MKLROOT}/lib -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
else # Linux
LIBFLAGS += -D_GNU_SOURCE
LDFLAGS += -L${MKLROOT}/lib/intel64 -Wl,-rpath=${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
endif # ?Darwin
LDFLAGS += -lpthread -lm -ldl
CFLAGS=$(OPTFLAGS) $(DBGFLAGS) $(LIBFLAGS) $(C18FLAGS) $(FPUFLAGS)
