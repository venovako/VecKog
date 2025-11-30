ifndef COMPILER
COMPILER=x64
endif # !COMPILER
include $(COMPILER).mk
MKFS=GNUmakefile $(COMPILER).mk

.PHONY: all help clean

all: libveckog$(TEST).a rndgen$(TEST).exe dbatch$(TEST).exe zbatch$(TEST).exe d8svd2t$(TEST).exe z8svd2t$(TEST).exe

help:
	@echo "make [TEST=0|1|2|3|4|5|6|7] [all|clean|help]"

rndgen$(TEST).exe: rndgen.c libveckog$(TEST).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

d8svd2t$(TEST).exe: d8svd2t.c libveckog$(TEST).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

z8svd2t$(TEST).exe: z8svd2t.c libveckog$(TEST).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

dbatch$(TEST).exe: dbatch.c libveckog$(TEST).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

zbatch$(TEST).exe: zbatch.c libveckog$(TEST).a $(MKFS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

libveckog$(TEST).a: kog$(TEST).o mem$(TEST).o msr$(TEST).o vec$(TEST).o wre$(TEST).o wmm$(TEST).o wor$(TEST).o common$(TEST).o $(MKFS)
	$(AR) $(ARFLAGS) $@ kog$(TEST).o mem$(TEST).o msr$(TEST).o vec$(TEST).o wre$(TEST).o wmm$(TEST).o wor$(TEST).o common$(TEST).o

kog$(TEST).o: kog.c kog.h dkog1.c dkog8.c dkog1.h dkog8.h zkog1.c zkog8.c zkog1.h zkog8.h kogp.c svd2.c vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

mem$(TEST).o: mem.c mem.h vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

vec$(TEST).o: vec.c vec.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wre$(TEST).o: wre.c wre.h wmm.h wor.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wmm$(TEST).o: wmm.c wmm.h wcmplx.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

wor$(TEST).o: wor.c wor.h wcmplx.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

msr$(TEST).o: msr.c msr.h common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

common$(TEST).o: common.c common.h $(MKFS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) common$(TEST).o
	-$(RM) wor$(TEST).o
	-$(RM) wmm$(TEST).o
	-$(RM) wre$(TEST).o
	-$(RM) vec$(TEST).o
	-$(RM) mem$(TEST).o
	-$(RM) kog$(TEST).o
	-$(RM) libveckog$(TEST).a
	-$(RM) rndgen$(TEST).exe
	-$(RM) dbatch$(TEST).exe
	-$(RM) zbatch$(TEST).exe
	-$(RM) d8svd2t$(TEST).exe
	-$(RM) z8svd2t$(TEST).exe
