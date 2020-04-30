ifndef CPU
CPU=x200
endif # !CPU
include $(CPU).mk
MKFS=GNUmakefile $(CPU).mk

.PHONY: all help clean

all: libveckog.a rndgen.exe

help:
	@echo "gmake [CPU=x200|x64] [NDEBUG=0|1|2|3|4|5] [PROFILE=p] [all|clean|help]"

rndgen.exe: rndgen.c common.h libveckog.a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

libveckog.a: kog.o mem.o wre.o wmm.o wor.o dlasv2t.o common.o $(MKFS)
	$(AR) $(ARFLAGS) $@ kog.o mem.o wre.o wmm.o wor.o dlasv2t.o common.o

kog.o: kog.c kog.h vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

mem.o: mem.c mem.h vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

wre.o: wre.c wre.h wmm.h wor.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

wmm.o: wmm.c wmm.h wcmplx.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

wor.o: wor.c wor.h wcmplx.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

dlasv2t.o: dlasv2t.c dlasv2t.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

common.o: common.c common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

clean:
	-$(RM) common.o
	-$(RM) dlasv2t.o
	-$(RM) wor.o
	-$(RM) wmm.o
	-$(RM) wre.o
	-$(RM) mem.o
	-$(RM) libveckog.a
	-$(RM) rndgen.exe
	-$(RM) dlasv2t.exe
