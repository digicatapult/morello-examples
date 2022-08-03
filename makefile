MORELLO_SDK?=${HOME}/cheri/output/morello-sdk

TARGET_FLAGS=-target aarch64-unknown-freebsd
DEBUG_FLAGS=-g
OPT_FLAGS=-O2
SYSROOT_FLAGS=--sysroot='$(MORELLO_SDK)/sysroot-morello-purecap'
LINKER_FLAGS=-fuse-ld=lld
DIAG_FLAGS=-Wall -Wcheri

CC=$(MORELLO_SDK)/bin/clang
CFLAGS=$(TARGET_FLAGS) $(DEBUG_FLAGS) $(OPT_FLAGS) $(SYSROOT_FLAGS) $(LINKER_FLAGS) $(DIAG_FLAGS)

EXAMPLES_LIST=out-of-bounds-write out-of-bounds-read out-of-bounds-access
TARGET_LIST=$(patsubst %,$(CHERI_PATTERN), $(EXAMPLES_LIST)) $(patsubst %,$(AARCH64_PATTERN), $(EXAMPLES_LIST))

.DEFAULT_GOAL := default
default: all

OUT_PATTERN=./build/%
clean:
	rm -f $(patsubst %,$(OUT_PATTERN), $(TARGET_LIST))

CHERI_PATTERN=%-cheri
$(CHERI_PATTERN): ./src/%.c
	$(CC) $(CFLAGS) $< -o ./build/$@

AARCH64_PATTERN=%-aarch64
$(AARCH64_PATTERN): ./src/%.c
	$(CC) $(CFLAGS) $< -o ./build/$@

%-cheri: CFLAGS := $(CFLAGS) -march=morello+c64 -mabi=purecap -Xclang -morello-vararg=new
%-aarch64: CFLAGS := $(CFLAGS) -march=morello+noa64c

all: $(TARGET_LIST)

