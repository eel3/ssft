# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix

# ----------------------------------------------------------

all: $(SHARED_LIBRARY_NAME)

$(SHARED_LIBRARY_NAME): $(object-files)
	$(CC) $(SHARED_LIBRARY_FLAGS) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@
