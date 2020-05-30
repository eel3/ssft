# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix

# ----------------------------------------------------------

PREFIX         := xcrun 
CC             := $(PREFIX)$(CC)
CXX            := $(PREFIX)$(CXX)
OBJC           := $(PREFIX)$(OBJC)
OBJCXX         := $(CXX)

CFLAGS          = -pthread      # FIXME
CXXFLAGS        =               # FIXME
OBJCFLAGS       =               # FIXME
OBJCXXFLAGS     =               # FIXME
CPPFLAGS        =               # FIXME
LDFLAGS         =
LDLIBS         := -lm -lobjc -framework Foundation      # FIXME

WARNADD        :=

# ----------------------------------------------------------

SDKROOT        := $(shell xcodebuild -version -sdk macosx | sed -n '/^Path: /s///p')

CPPFLAGS       += -isysroot "$(SDKROOT)"
TARGET_ARCH    := -mmacosx-version-min=10.13 -arch x86_64   # FIXME

# ----------------------------------------------------------

include ../unix-common/common.mk

# ----------------------------------------------------------

SHARED_LIBRARY_NAME    := $(TARGET_BASE_NAME).dylib
SHARED_LIBRARY_FLAGS   := -dynamiclib \
                          -compatibility_version $(TARGET_COMPAT_VERSION) \
                          -current_version $(TARGET_VERSION) \
                          -install_name @rpath/$(SHARED_LIBRARY_NAME)

# ----------------------------------------------------------

include ../unix-common/shared-lib.mk
