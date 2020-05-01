ifndef CPU
CPU=x200
endif # !CPU
include $(CPU).mk
MKFS=GNUmakefile $(CPU).mk

.PHONY: all help clean

all: libveckog.a rndgen.exe d8svd2t.exe z8svd2t.exe

help:
	@echo "gmake [CPU=x200|x64] [NDEBUG=0|1|2|3|4|5] [PROFILE=p] [all|clean|help]"

rndgen.exe: rndgen.c libveckog.a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

d8svd2t.exe: d8svd2t.c libveckog.a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

z8svd2t.exe: z8svd2t.c libveckog.a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

libveckog.a: kog.o mem.o vec.o wre.o wmm.o wor.o dlasv2t.o common.o $(MKFS)
	$(AR) $(ARFLAGS) $@ kog.o mem.o wre.o wmm.o wor.o dlasv2t.o common.o

kog.o: kog.c kog.h dkog.c dkog.h zkog.c zkog.h vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

mem.o: mem.c mem.h vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

vec.o: vec.c vec.h common.h $(MKFS)
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
	-$(RM) vec.o
	-$(RM) mem.o
	-$(RM) kog.o
	-$(RM) libveckog.a
	-$(RM) rndgen.exe
	-$(RM) d8svd2t.exe
	-$(RM) z8svd2t.exe
