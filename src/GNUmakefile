ifndef CPU
CPU=x200
endif # !CPU
include $(CPU).mk
MKFS=GNUmakefile $(CPU).mk

.PHONY: all help clean

all: libveckog.a rndgen.exe

help:
	@echo "gmake [CPU=x200|x64] [NDEBUG=0|1|2|3|4|5] [PROFILE=p] [all|clean|help]"

libveckog.a: common.o $(MKFS)
	$(AR) $(ARFLAGS) $@ common.o

common.o: common.c common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

rndgen.exe: rndgen.c common.h libveckog.a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	-$(RM) rndgen.exe
	-$(RM) libveckog.a
