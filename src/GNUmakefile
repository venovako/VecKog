ifndef COMPILER
COMPILER=x64x
endif # !COMPILER
include $(COMPILER).mk
MKFS=GNUmakefile $(COMPILER).mk

.PHONY: all help clean

all: libveckog$(TEST)$(DEBUG).a rndgen$(TEST)$(DEBUG).exe dbatch$(TEST)$(DEBUG).exe zbatch$(TEST)$(DEBUG).exe d8svd2t$(TEST)$(DEBUG).exe z8svd2t$(TEST)$(DEBUG).exe

help:
	@echo "make [COMPILER=x64x|x200] [NDEBUG=0|1|2|3|4|5] [TEST=0|1|2|3|4|5|6|7] [all|clean|help]"

rndgen$(TEST)$(DEBUG).exe: rndgen.c libveckog$(TEST)$(DEBUG).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

d8svd2t$(TEST)$(DEBUG).exe: d8svd2t.c libveckog$(TEST)$(DEBUG).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

z8svd2t$(TEST)$(DEBUG).exe: z8svd2t.c libveckog$(TEST)$(DEBUG).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

dbatch$(TEST)$(DEBUG).exe: dbatch.c libveckog$(TEST)$(DEBUG).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

zbatch$(TEST)$(DEBUG).exe: zbatch.c libveckog$(TEST)$(DEBUG).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

libveckog$(TEST)$(DEBUG).a: kog$(TEST)$(DEBUG).o mem$(TEST)$(DEBUG).o msr$(TEST)$(DEBUG).o vec$(TEST)$(DEBUG).o wre$(TEST)$(DEBUG).o wmm$(TEST)$(DEBUG).o wor$(TEST)$(DEBUG).o common$(TEST)$(DEBUG).o $(MKFS)
	$(AR) $(ARFLAGS) $@ kog$(TEST)$(DEBUG).o mem$(TEST)$(DEBUG).o msr$(TEST)$(DEBUG).o vec$(TEST)$(DEBUG).o wre$(TEST)$(DEBUG).o wmm$(TEST)$(DEBUG).o wor$(TEST)$(DEBUG).o common$(TEST)$(DEBUG).o

kog$(TEST)$(DEBUG).o: kog.c kog.h dkog1.c dkog8.c dkog1.h dkog8.h zkog1.c zkog8.c zkog1.h zkog8.h kogp.c svd2.c vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

mem$(TEST)$(DEBUG).o: mem.c mem.h vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

vec$(TEST)$(DEBUG).o: vec.c vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wre$(TEST)$(DEBUG).o: wre.c wre.h wmm.h wor.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wmm$(TEST)$(DEBUG).o: wmm.c wmm.h wcmplx.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wor$(TEST)$(DEBUG).o: wor.c wor.h wcmplx.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

msr$(TEST)$(DEBUG).o: msr.c msr.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

common$(TEST)$(DEBUG).o: common.c common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) common$(TEST)$(DEBUG).o
	-$(RM) wor$(TEST)$(DEBUG).o
	-$(RM) wmm$(TEST)$(DEBUG).o
	-$(RM) wre$(TEST)$(DEBUG).o
	-$(RM) vec$(TEST)$(DEBUG).o
	-$(RM) mem$(TEST)$(DEBUG).o
	-$(RM) kog$(TEST)$(DEBUG).o
	-$(RM) libveckog$(TEST)$(DEBUG).a
	-$(RM) rndgen$(TEST)$(DEBUG).exe
	-$(RM) dbatch$(TEST)$(DEBUG).exe
	-$(RM) zbatch$(TEST)$(DEBUG).exe
	-$(RM) d8svd2t$(TEST)$(DEBUG).exe
	-$(RM) z8svd2t$(TEST)$(DEBUG).exe
