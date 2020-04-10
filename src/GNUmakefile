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

libveckog.a: wre.o wmm.o wor.o dlas2t.o common.o $(MKFS)
	$(AR) $(ARFLAGS) $@ wre.o wmm.o wor.o dlas2t.o common.o

wre.o: wre.c wre.h wmm.h wor.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

wmm.o: wmm.c wmm.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

wor.o: wor.c wor.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

dlas2t.o: dlas2t.c dlas2t.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

common.o: common.c common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

clean:
	-$(RM) common.o
	-$(RM) dlas2t.o
	-$(RM) wor.o
	-$(RM) wmm.o
	-$(RM) wre.o
	-$(RM) libveckog.a
	-$(RM) rndgen.exe
	-$(RM) dlas2t.exe
