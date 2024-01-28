# sbase version
VERSION = 0.0

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

CC = /opt/lfi/toolchain/bin/lfi-clang
AR = ar
RANLIB = ranlib

# for NetBSD add -D_NETBSD_SOURCE
# -lrt might be needed on some systems
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -D_FILE_OFFSET_BITS=64
CFLAGS   = -std=c99 -Wall -pedantic
LDFLAGS  = -s
