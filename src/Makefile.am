
AM_CFLAGS = -W -Wall -Os
AM_LDLIBS = -lm

bin_PROGRAMS = imgmin
imgmin_SOURCES = imgmin.c dssim.c interpolate.c

imgmin$(EXEEXT): $(imgmin_SOURCES)
	$(CC) $(AM_CFLAGS) $(AM_LDFLAGS) `$(MAGICK_CONFIG) --cflags --cppflags` -o $@ $^ `$(MAGICK_CONFIG) --ldflags --libs`

