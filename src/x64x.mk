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
CC=icx -std=c18
CPUFLAGS=-DUSE_INTEL -DUSE_X64 -fPIC -fexceptions -fno-omit-frame-pointer -qopenmp -rdynamic
ifdef TEST
CPUFLAGS += -DTEST=$(TEST)
endif # TEST
C18FLAGS=$(CPUFLAGS)
FPUFLAGS=-fp-model precise -fprotect-parens -fma -no-ftz -fimf-use-svml=true
ifdef NDEBUG
OPTFLAGS=-O$(NDEBUG) -xHost -vec-threshold0
DBGFLAGS=-DNDEBUG -qopt-report=3 -traceback
else # DEBUG
OPTFLAGS=-O0 -xHost
DBGFLAGS=-$(DEBUG) -debug emit_column -debug extended -debug inline-debug-info -debug pubnames -traceback
ifneq ($(ARCH),Darwin) # Linux
DBGFLAGS += -debug parallel
endif # ?Linux
endif # ?NDEBUG
LIBFLAGS=-I. -DUSE_MKL -I${MKLROOT}/include/intel64/lp64 -I${MKLROOT}/include
LDFLAGS=-L. -lveckog$(TEST)$(DEBUG)
ifeq ($(ARCH),Darwin)
LDFLAGS += -L${MKLROOT}/lib -Wl,-rpath,${MKLROOT}/lib -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
else # Linux
LIBFLAGS += -static-libgcc -D_GNU_SOURCE
LDFLAGS += -L${MKLROOT}/lib/intel64 -Wl,-rpath=${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
endif # ?Darwin
LDFLAGS += -lpthread -lm -ldl
CFLAGS=$(OPTFLAGS) $(DBGFLAGS) $(LIBFLAGS) $(C18FLAGS) $(FPUFLAGS)
