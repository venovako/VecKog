ifndef CPU
CPU=x200
endif # !CPU
include $(CPU).mk
MKFS=GNUmakefile $(CPU).mk

.PHONY: all help clean

all: common.o

help:
	@echo "gmake [CPU=x200|x64] [NDEBUG=0|1|2|3|4|5] [PROFILE=p] [all|clean|help]"

common.o: common.c common.h $(MKFS)
	$(CC) $(CFLAGS) -c $<

rndgen.exe: rndgen.c common.h $(MKFS)
	clang -DNDEBUG -I. -std=gnu17 -O3 -march=native -integrated-as $< -o $@

clean:
	-$(RM) common.o
	-$(RM) rndgen.exe
