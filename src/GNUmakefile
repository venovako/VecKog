ifndef CPU
CPU=x200
endif # !CPU
include $(CPU).mk
MKFS=GNUmakefile $(CPU).mk

.PHONY: all help clean

all: libveckog$(DEBUG).a rndgen$(DEBUG).exe d8svd2t$(DEBUG).exe z8svd2t$(DEBUG).exe

help:
	@echo "gmake [CPU=x200|x64] [NDEBUG=0|1|2|3|4|5] [TEST=0|1|2] [all|clean|help]"

rndgen$(DEBUG).exe: rndgen.c libveckog$(DEBUG).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

d8svd2t$(DEBUG).exe: d8svd2t.c libveckog$(DEBUG).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

z8svd2t$(DEBUG).exe: z8svd2t.c libveckog$(DEBUG).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

libveckog$(DEBUG).a: kog$(DEBUG).o mem$(DEBUG).o vec$(DEBUG).o wre$(DEBUG).o wmm$(DEBUG).o wor$(DEBUG).o dlasv2t$(DEBUG).o common$(DEBUG).o $(MKFS)
	$(AR) $(ARFLAGS) $@ kog$(DEBUG).o mem$(DEBUG).o vec$(DEBUG).o wre$(DEBUG).o wmm$(DEBUG).o wor$(DEBUG).o dlasv2t$(DEBUG).o common$(DEBUG).o

kog$(DEBUG).o: kog.c kog.h dkog.c dkog.h zkog.c zkog.h vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

mem$(DEBUG).o: mem.c mem.h vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

vec$(DEBUG).o: vec.c vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wre$(DEBUG).o: wre.c wre.h wmm.h wor.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wmm$(DEBUG).o: wmm.c wmm.h wcmplx.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wor$(DEBUG).o: wor.c wor.h wcmplx.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

dlasv2t$(DEBUG).o: dlasv2t.c dlasv2t.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

common$(DEBUG).o: common.c common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) common$(DEBUG).o
	-$(RM) dlasv2t$(DEBUG).o
	-$(RM) wor$(DEBUG).o
	-$(RM) wmm$(DEBUG).o
	-$(RM) wre$(DEBUG).o
	-$(RM) vec$(DEBUG).o
	-$(RM) mem$(DEBUG).o
	-$(RM) kog$(DEBUG).o
	-$(RM) libveckog$(DEBUG).a
	-$(RM) rndgen$(DEBUG).exe
	-$(RM) d8svd2t$(DEBUG).exe
	-$(RM) z8svd2t$(DEBUG).exe
