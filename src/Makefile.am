## Process this file with automake to produce Makefile.in

## Created by Anjuta



AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(EDITORX_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = editorx

editorx_SOURCES = \
	main.c \
	xeditor.h \
	xeditor.c \
	window.h \
	window.c \
	toolbar.h \
	toolbar.c \
	statusbar.h \
	statusbar.c \
	search.h \
	search.c \
	scrolled.h \
	scrolled.c \
	menubar.h \
	menubar.c \
	definitions.h


editorx_LDFLAGS = \
	-Wl,--export-dynamic

editorx_LDADD = $(EDITORX_LIBS)




