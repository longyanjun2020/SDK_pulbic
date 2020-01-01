CC=gcc

LEXCOMPILE = $(LEX) $(LFLAGS) $(AM_LFLAGS)
LEX = flex
LEXLIB = -lfl
LEX_OUTPUT_ROOT = lex.yy

CONFIG_UPNP_DEBUG=0
CONFIG_AMNSS_DEBUG=1

# CFLAGS=-g -Wall -pedantic -Wc++-compat \
	-Wparentheses -Wsequence-point -Wswitch-default \
	-Wextra -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast \
	-Wwrite-strings -Wold-style-definition \
	-Wmissing-prototypes -Wredundant-decls -Wnested-externs
# not used for now but interesting:
# -Wpacked
# -Wunreachable-code
# -ansi
# -std=c89

CFLAGS=-g -Wall -D__AMN_OS_LINUX__
LDFLAGS=-lpthread -lutil -lrt

ifeq ($(CONFIG_AMNSS_DEBUG),1)
CFLAGS+= -D__AMNSS_DEBUG__
endif

# Suppress warnings from casts from a pointer to an integer type of a different size.
CFLAGS+= -Wno-pointer-to-int-cast

# Suppress warnings from casts to pointer type of an integer of a different size.
CFLAGS+= -Wno-int-to-pointer-cast

#Set this to where you have the lwip core module checked out from CVS
#default assumes it's a dir named lwip at the same level as the contrib module

CFLAGS:=$(CFLAGS) -I.

SRCS_COMMON := \
	../common/amn_system.c ../common/__md5.c ../common/config_man.c \
	../common/amn_event.c ../common/net_daemon.c  ../common/web_vhandler.c

#	streaming/amnss_event.c      -> ../common/amnss_event.c
#	streaming/protocol/net_tcp.c -> ../common/net_daemon.c

SRCS_ASS := \
    amnss_linux.c amnss_mmobjs.c amnss_conf.c \
	snkLivecastRTSP.c snkLivecastHTTP.c \
	fltDebug.c fltFrameDrop.c srcSimFile.c srcSimV4L2.c \
    protocol/http-auth.c protocol/rtsp.c \
    protocol/rtp.c protocol/rtp-h264.c protocol/rtp-jpeg.c \
	protocol/rtp-mpa.c protocol/rtp-mpv.c protocol/rtp-h263.c protocol/rtp-mpeg4.c protocol/rtp-rawaudio.c

SRCS_HTTP := \
	../http/cgi_main.c \
	../http/cgi/config_cgi.c ../http/cgi/user_cgi.c ../http/cgi/cvd_cgi.c \
	../http/chp_engine.c ../http/chp_custom.c ../http/chp_C/includes-all.c \

SRCS_LIBUPNP := \
	../libupnp/upnp/src/genlib/net/http/webserver.c \
	../libupnp/upnp/src/genlib/net/http/httpreadwrite.c \
	../libupnp/upnp/src/genlib/net/http/httpparser.c \
	../libupnp/upnp/src/genlib/net/http/statcodes.c \
	../libupnp/upnp/src/genlib/net/uri/uri.c \
	../libupnp/upnp/src/genlib/net/sock.c \
	../libupnp/upnp/src/genlib/util/membuffer.c \
	../libupnp/upnp/src/genlib/util/strintmap.c \
	../libupnp/upnp/src/api/upnpapi.c \
	../libupnp/upnp/src/inet_pton.c \
	../libupnp/threadutil/src/LinkedList.c \
	../libupnp/threadutil/src/FreeList.c \

# \
	../libupnp/upnp/src/genlib/miniserver/miniserver.c \
	../libupnp/upnp/src/genlib/net/http/parsetools.c \
	../libupnp/upnp/src/genlib/service_table/service_table.c \
	../libupnp/upnp/src/genlib/client_table/client_table.c \
	../libupnp/upnp/src/genlib/util/util.c \
	../libupnp/upnp/src/genlib/util/upnp_timeout.c \

CFLAGS:=$(CFLAGS) -I../common -I../http -I../http/chp_C -I../libupnp/upnp/src/inc -I../libupnp/build/inc -I../libupnp/upnp/inc -I../libupnp/threadutil/inc

ifeq ($(CONFIG_UPNP_DEBUG),1)
SRCS_LIBUPNP := $(SRCS_LIBUPNP) ../libupnp/upnp/src/api/upnpdebug.c
CFLAGS:=$(CFLAGS) -D__UPNP_DEBUG__ -DDEBUG
endif

#SRCS_LIBXML := \
	../libupnp/ixml/src/node.c \
	../libupnp/ixml/src/ixmlparser.c \
	../libupnp/ixml/src/ixmlmembuf.c \
	../libupnp/ixml/src/element.c \
	../libupnp/ixml/src/ixmldebug.c \
	../libupnp/ixml/src/attr.c \
	../libupnp/ixml/src/ixml.c \
	../libupnp/ixml/src/nodeList.c \
	../libupnp/ixml/src/document.c \
	../libupnp/ixml/src/namedNodeMap.c \

CFLAGS:=$(CFLAGS) -I../libupnp/ixml/inc/ -I../libupnp/ixml/src/inc/

OBJS_ASS := $(patsubst %.c, obj/%.o, $(SRCS_ASS))
OBJS_HTTP := $(patsubst %.c, obj/%.o, $(SRCS_HTTP))
OBJS_COMMON := $(patsubst %.c, obj/%.o, $(SRCS_COMMON))
OBJS_LIBUPNP := $(patsubst %.c, obj/%.o, $(SRCS_LIBUPNP))
OBJS_LIBXML := $(patsubst %.c, obj/%.o, $(SRCS_LIBXML))

#OBJS := $(OBJS_ASS) $(OBJS_HTTP) $(OBJS_COMMON) $(OBJS_LIBUPNP) $(OBJS_LIBXML)
OBJS := $(OBJS_ASS) $(OBJS_HTTP) $(OBJS_COMMON) $(OBJS_LIBUPNP)

all : aitstream

aitstream: ../common/inc/auto_syscfg.h cchp $(OBJS)
	@echo -e "\n======================================================="
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: all conf clean clean_all cchp ccfg

$(OBJS): obj/%.o : %.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c -o $@ $<

../common/inc/auto_syscfg.h: ../common/conf/amn_system.linux.conf
	../bin/cfg-compile.pl -o $@ $<

ccfg:
	../bin/cfg-compile.pl -o ../common/inc/auto_syscfg.h ../common/conf/amn_system.ucos.conf


cchp:
	../bin/chp-compile.pl -o ../http/chp_C/ ../http/chp/

# Note the FLEX file: conf_scan.l, renamed to conf_scan.ll, otherwise ARM ADS will complain
# .l.c:
conf_scan.c: conf_scan.ll
	$(LEXCOMPILE) $<
	sed '/^#/ s|$(LEX_OUTPUT_ROOT)\.c|$@|' $(LEX_OUTPUT_ROOT).c >$@
	rm -f $(LEX_OUTPUT_ROOT).c
	#---- for uC/OS -------
	cat $@ | awk '{ if ($$0 ~ "^#include <errno.h>") { printf "#ifdef __AMN_OS_LINUX__\n#include <errno.h>\n#else\n#define YY_NO_UNISTD_H\n#endif\n"; } else print $$0; }' | \
		sed -e 's/file ? (isatty( fileno(file) ) > 0) ://' \
			-e 's/\bfree\b/osal_free/' \
			-e 's/\brealloc\b/osal_realloc/' \
			-e 's/\bmalloc\b/osal_zmalloc/' \
			-e 's/\bexit\b/osal_exit/' \
			-e 's/\bstdin\b/(FILE*)0/' \
			-e 's/\bstdout\b/(FILE*)0/' \
			-e 's,^#line ,// #line ,' \
			-e 's/(void) fprintf( stderr,/osal_dprint(ERR,/' \
		   	> ait_$@

conf/amnss_conf.h: conf/amnss_ucos.conf
	sed -e 's/"/\\"/g' -e 's/^\(.*\)$$/  "\1\   \\n",/' $< > conf/amnss_conf.h

conf: conf/amnss_conf.h

clean_all: clean
	@if [ -f ait_conf_scan.c ]; then mv -vf ait_conf_scan.c /tmp/ait_conf_scan.c.$$$$; fi
	rm -f conf_scan.c conf/amnss_conf.h
	rm -f ../common/inc/auto_syscfg.h
	rm -f ../http/chp_C/*

clean:
	rm -rf obj/ aitstream aitstreamer.log
	rm -rf common/ libupnp/ http/ *.txt

