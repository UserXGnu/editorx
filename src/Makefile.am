## Process this file with automake to produce Makefile.in

## Created by Anjuta



AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(XEDITOR_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = xeditor

xeditor_SOURCES = \
	main.c \
	menubar.h \
	scrolled.h \
	statusbar.h \
	toolbar.h \
	window.h \
	xeditor.h \
	scrolled.c \
	menubar.c \
	statusbar.c \
	toolbar.c \
	window.c \
	xeditor.c \
	search.h \
	search.c \
	definitions.h

xeditor_LDFLAGS = \
	-Wl,--export-dynamic

xeditor_LDADD = $(XEDITOR_LIBS)


