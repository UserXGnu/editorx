/*
 * definitions.h
 *
 * Copyright (C) 2013 - userx
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#include <gtk/gtk.h>

#include <gtksourceview/gtksourceview.h>
#include <gtksourceview/gtksourcebuffer.h>
#include <gtksourceview/gtksourcelanguage.h>
#include <gtksourceview/gtksourcelanguagemanager.h>

#include <glib/gi18n.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// MAIN HEADERS ::
#include "window.h"

#include "menubar.h"

#include "toolbar.h"

#include "scrolled.h"

#include "statusbar.h" 

#include "xeditor.h"

#include "search.h"

#ifndef SET_EXPORT_HOME
#define SET_EXPORT_HOME	system("export HOME=~")
#endif

#ifndef X_USER_DEFAULT_PATH
#define X_USER_DEFAULT_PATH		getenv("HOME")
#endif 

#ifndef X_EDITOR_PROGRAM_NAME
#define X_EDITOR_PROGRAM_NAME	"EditorX"
#endif

#ifndef X_WINDOW_DEFAULT_TITLE
#define X_WINDOW_DEFAULT_TITLE	"Editor X -"
#endif

#ifndef X_DEFAULT_FILENAME
#define X_DEFAULT_FILENAME		"\'Untitled Document\'"
#endif

#ifndef X_WINDOW_DEFAULT_X_LEN
#define X_WINDOW_DEFAULT_X_LEN	640
#endif

#ifndef X_WINDOW_DEFAULT_Y_LEN
#define X_WINDOW_DEFAULT_Y_LEN	480
#endif

#ifndef X_EDITOR_VERSION
#define X_EDITOR_VERSION		"0.3.1"
#endif

#ifndef COPYRIGHT
#define COPYRIGHT				"Copyright © 2012-2013 Victor Flores (UserX)"
#endif

#ifndef X_EDITOR_REPO
#define X_EDITOR_REPO			"git@gitorious.org:editorx/editorx.git"
#endif 

#ifndef X_EDITOR_DEFAULT_MIMETYPE
#define X_EDITOR_DEFAULT_MIMETYPE   "c"
#endif

#ifndef X_EDITOR_CONFIG_FILE
#define X_EDITOR_CONFIG_FILE	"/.xeditor/config.dat"
#endif

#ifndef X_EDITOR_FONT_CONFIG_GILE
#define X_EDITOR_FONT_CONFIG_FILE "/.xeditor/font_config"
#endif

#ifndef X_EDITOR_SPLASH_ADDR
#define X_EDITOR_SPLASH_ADDR	"/usr/local/doc/xeditor/splash.png"
#endif

#endif /* _DEFINITIONS_H */
