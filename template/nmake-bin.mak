# -*- coding: cp932-dos -*-
# vim:fileencoding=cp932:ff=dos

# ----------------------------------------------------------

root_dir        = .                     # FIXME

include_dir     = $(root_dir)\include   # FIXME
src_dir         = $(root_dir)\src       # FIXME

# ----------------------------------------------------------

vpath           = $(src_dir)    # FIXME

include_dirs    = $(include_dir) $(vpath)   # FIXME

object_files    = main.obj      # FIXME

target_name     = app.exe       # FIXME

lib_files       = winmm.lib     # FIXME

win_ver         = 0x0A00        # XXX Windows 10

# ----------------------------------------------------------

!ifdef DEBUG
ccdefs      = /MTd /Zi /D WIN32;_DEBUG;_CONSOLE;WINVER=$(win_ver);_WIN32_WINNT=$(win_ver);_CRT_SECURE_NO_WARNINGS;_WINDOWS;DEBUG
linkflags   = /DEBUG
!else
ccdefs      = /MT /D WIN32;NDEBUG;_CONSOLE;WINVER=$(win_ver);_WIN32_WINNT=$(win_ver);_CRT_SECURE_NO_WARNINGS;_WINDOWS
linkflags   =
!endif

CFLAGS      = /nologo /GL /GS /RTCs /RTCu /W4 $(ccdefs:;= /D ) /I $(include_dirs: = /I )
CXXFLAGS    = /nologo /EHsc /GL /GS /RTCs /RTCu /W4 $(ccdefs:;= /D ) /I $(include_dirs: = /I )

# ----------------------------------------------------------

phony_targets   = all clean usage

usage: FORCE
	:: usage: $(MAKE) [DEBUG=1] [$(phony_targets: =] [)]

all: $(target_name)

$(target_name): $(object_files)
	link.exe /NOLOGO /LTCG /OUT:$@ /SUBSYSTEM:CONSOLE $(linkflags) $** $(lib_files)

clean: FORCE
	del /F $(target_name) $(object_files) *.pdb

FORCE:

# ----------------------------------------------------------

{$(src_dir)}.c.obj::
	$(CC) $(CFLAGS) /c $<
{$(src_dir)}.cpp.obj::
	$(CXX) $(CXXFLAGS) /c $<
