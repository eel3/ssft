# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix

# ----------------------------------------------------------

root-dir       := .                     # FIXME

include-dir    := $(root-dir)/include   # FIXME
src-dir        := $(root-dir)/src       # FIXME

# ----------------------------------------------------------

VPATH          := $(src-dir)    # FIXME

include-dirs   := $(addprefix -I ,$(include-dir) $(VPATH) .)    # FIXME

object-files   := main.o        # FIXME

depend-files   := $(subst .o,.d,$(object-files))

# ----------------------------------------------------------

TARGET_BASE_NAME       := libXXXX   # FIXME
TARGET_MAJOR_VERSION   := 1         # FIXME
TARGET_MINOR_VERSION   := 0         # FIXME
TARGET_RELEASE_VERSION := 0         # FIXME
TARGET_VERSION         := $(TARGET_MAJOR_VERSION).$(TARGET_MINOR_VERSION).$(TARGET_RELEASE_VERSION)
TARGET_COMPAT_VERSION  := $(TARGET_VERSION)     # FIXME

# ----------------------------------------------------------

ifeq "$(strip $(DEBUG))" ""
  CPPFLAGS     += -DNDEBUG
  LDFLAGS      += -O2   # FIXME
  OPTIM        += -O2   # FIXME
else
  CPPFLAGS     += -DDEBUG
  LDFLAGS      += -g
  OPTIM        += -g
endif

ifneq "$(strip $(PROFILE))" ""
  LDFLAGS      += --coverage
  OPTIM        += --coverage
  cov-files     = $(subst .o,.gcno,$(object-files)) $(subst .o,.gcda,$(object-files)) $(wildcard *.gcov)
endif

OPTIM          += -fno-common -fPIC

WARN_COMMON    ?= -pedantic -Wall -Wextra
WARN_C         ?=
WARN_CXX       ?=

CWARN          ?= -std=c89 $(WARN_COMMON) $(WARN_C)         # FIXME
CXXWARN        ?= -std=c++11 $(WARN_COMMON) $(WARN_CXX)     # FIXME
OBJCWARN       ?= -std=gnu99 $(WARN_COMMON) $(WARN_C)       # FIXME
OBJCXXWARN     ?= -std=gnu++11 $(WARN_COMMON) $(WARN_CXX)   # FIXME

CFLAGS         += $(OPTIM) $(CWARN) $(WARNADD)
CXXFLAGS       += $(OPTIM) $(CXXWARN) $(WARNADD)
OBJCFLAGS      += $(OPTIM) $(OBJCWARN) $(WARNADD)
OBJCXXFLAGS    += $(OPTIM) $(OBJCXXWARN) $(WARNADD)
CPPFLAGS       += -DPIC $(include-dirs)
LDFLAGS        +=

# ----------------------------------------------------------

phony-targets  := all clean usage

.PHONY: $(phony-targets)

usage:
	# usage: $(MAKE) [DEBUG=1] [PROFILE=1] $(patsubst %,[%],$(phony-targets))

clean:
	$(RM) $(SHARED_LIBRARY_NAME) $(object-files) $(depend-files) $(cov-files)

# ----------------------------------------------------------

ifneq "$(MAKECMDGOALS)" ""
ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "usage"
  -include $(depend-files)
endif
endif
endif

# $(call make-depend,source-file,object-file,depend-file,cc,flags)
make-depend = $4 -MM -MF $3 -MP -MT $2 $5 $(CPPFLAGS) $1

%.o: %.c
	$(call make-depend,$<,$@,$(subst .o,.d,$@),$(CC),$(CFLAGS))
	$(COMPILE.c) $(OUTPUT_OPTION) $<

%.o: %.cpp
	$(call make-depend,$<,$@,$(subst .o,.d,$@),$(CXX),$(CXXFLAGS))
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

%.o: %.m
	$(call make-depend,$<,$@,$(subst .o,.d,$@),$(OBJC),$(OBJCFLAGS))
	$(COMPILE.m) $(OUTPUT_OPTION) $<

%.o: %.mm
	$(call make-depend,$<,$@,$(subst .o,.d,$@),$(OBJCXX),$(OBJCXXFLAGS))
	$(OBJCXX) $(OBJCXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $(OUTPUT_OPTION) $<
