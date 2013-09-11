/*
 * xeditor.h
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

#ifndef _XEDITOR_H
#define _XEDITOR_H

#include "definitions.h"

typedef struct _xeditorprivate XEditorPrivate;
struct _xeditorprivate {
	GFile * file;	
	
	gchar * filename;
	gboolean search_flag;
	gboolean save;
};

// thats the MainClass, or the principal class so...
// every class will be into it ::
typedef struct _xeditor XEditor;
struct _xeditor {
	Window * win;
	Menu * menu;
	ToolBar * toolbar;
	Scrolled * scrolled;
	StatusBar * statusbar;

	XEditorPrivate * private_data;
};

// Callbacks ::
void x_editor_destroy_callback(GtkWidget *, gpointer);
void x_window_close_callback (GtkWidget *, gpointer);
void x_dialog_warn_quit(GtkWidget *, gpointer);

// getters and setters methods ::
GFile * x_editor_get_file(XEditor *) G_GNUC_CONST;
gchar * x_editor_get_filename (XEditor *) G_GNUC_CONST;
gboolean * x_editor_get_save_status (XEditor *) G_GNUC_CONST;
gboolean * x_editor_get_search_flag (XEditor *) G_GNUC_CONST;

gboolean x_editor_get_save (XEditor *) G_GNUC_CONST;
gboolean x_editor_get_search_flag_status (XEditor *) G_GNUC_CONST;


void x_editor_set_file(XEditor *, GFile *);
void x_editor_set_filename (XEditor *, gchar *);
void x_editor_set_save_status (XEditor *, gboolean);
void x_editor_set_search_flag (XEditor *, gboolean);

// Another methods ::
void x_editor_splash_create_and_show ();
void x_editor_save_textbuffer_content (XEditor *, gchar *);
void x_editor_save_font_config (XEditor *);
void x_editor_show_all (XEditor *);
void x_editor_pack_all (XEditor *);
void x_editor_connect_all_signals(XEditor *);
void x_editor_init(XEditor *);
void x_editor_config(XEditor *);
void x_editor_apply_font_config (XEditor *);
void x_editor_dialog_warn (gchar *);
void x_editor_config_menu (XEditor *);
XEditor * x_editor_new(void) G_GNUC_CONST;


#endif /* _XEDITOR_H */