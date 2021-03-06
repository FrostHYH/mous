#
# libavcodec Makefile
# (c) 2000-2003 Fabrice Bellard
# (c) 2004 McMCC <mcmcc@mail.ru>
#
include config.mak

# NOTE: -I.. is needed to include config.h
CFLAGS+=$(OPTFLAGS) -DHAVE_AV_CONFIG_H -fno-strict-aliasing -I/usr/local/include  -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_GNU_SOURCE

OBJS= common.o utils.o mem.o allcodecs.o futils.o cutils.o os_support.o allformats.o parser.o \
      avio.o aviobuf.o file.o simple_idct.o dsputil.o fft.o mdct.o asf.o

# codecs which are patented in some non free countries like the us
ifeq ($(CONFIG_RISKY),yes)
OBJS+= wmadec.o
endif

ifeq ($(TARGET_GPROF),yes)
CFLAGS+=-p
LDFLAGS+=-p
endif

SRCS := $(OBJS:.o=.c) $(ASM_OBJS:.o=.S)
OBJS := $(OBJS) $(ASM_OBJS)

LIB= $(LIBPREF)ffwma$(LIBSUF)
ifeq ($(BUILD_SHARED),yes)
SLIB= $(SLIBPREF)ffwma$(SLIBSUF)
endif

all: $(LIB) $(SLIB)

$(LIB): $(OBJS)
	rm -f $@
	$(AR) rc $@ $(OBJS)
	$(RANLIB) $@

$(SLIB): $(OBJS)
	$(CC) $(SHFLAGS) -o $@ $(OBJS) $(EXTRALIBS)

dsputil.o: dsputil.c dsputil.h

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

depend: $(SRCS)
	$(CC) -MM $(CFLAGS) $^ 1>.depend

dep:	depend

clean: 
	rm -f *.o *.d *~ .depend $(LIB) $(SLIB) *.so

distclean: clean
	rm -f Makefile.bak .depend

ifeq ($(BUILD_SHARED),yes)
install: all install-headers
	install -d $(prefix)/lib
	install -s -m 755 $(SLIB) $(prefix)/lib/libffwma-$(VERSION).so
	ln -sf libffwma-$(VERSION).so $(prefix)/lib/libffwma.so
	ldconfig || true
else
install:
endif

installlib: all install-headers
	install -m 644 $(LIB) $(prefix)/lib

install-headers:
	mkdir -p "$(prefix)/include/ffwma"
	install -m 644 *.h "$(prefix)/include/ffwma"

