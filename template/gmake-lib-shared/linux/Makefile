# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix

# ----------------------------------------------------------

PREFIX         :=
CC             := $(PREFIX)$(CC)
CXX            := $(PREFIX)$(CXX)
OBJC           := $(PREFIX)$(OBJC)
OBJCXX         := $(CXX)

CFLAGS          = -pthread      # FIXME
CXXFLAGS        =               # FIXME
OBJCFLAGS       =               # FIXME
OBJCXXFLAGS     =               # FIXME
CPPFLAGS        = -D_BSD_SOURCE -D_DEFAULT_SOURCE   # FIXME
LDFLAGS         = -pthread      # FIXME
LDLIBS         := -lm -lrt      # FIXME

WARNADD        := -finput-charset=cp932     # FIXME

# ----------------------------------------------------------

include ../unix-common/common.mk

# ----------------------------------------------------------

SHARED_LIBRARY_NAME    := $(TARGET_BASE_NAME).so.$(TARGET_VERSION)
SHARED_LIBRARY_FLAGS   := -shared -Wl,-soname,$(TARGET_BASE_NAME).so.$(TARGET_MAJOR_VERSION)

# ----------------------------------------------------------

include ../unix-common/shared-lib.mk
