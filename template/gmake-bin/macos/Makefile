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
TARGET_ARCH    := -mmacosx-version-min=10.12 -arch x86_64   # FIXME

# ----------------------------------------------------------

include ../unix-common/common.mk
