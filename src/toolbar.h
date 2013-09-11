/*
 * toolbar.h
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
#ifndef _TOOLBAR_H
#define _TOOLBAR_H

typedef struct _toolbarprivate ToolBarPrivate;
struct _toolbarprivate {
	gchar * font_desc;
};

typedef struct _toolbar ToolBar;
struct _toolbar {
	GtkWidget * tBar;
	
	GtkToolItem * SaveItem;
    GtkToolItem * OpenItem;
	
    GtkToolItem * FirstSeparatorItem;
	
    GtkToolItem * CutItem;
    GtkToolItem * CopyItem;
    GtkToolItem * PasteItem;
    GtkToolItem * SelectAllItem;

	GtkToolItem * SecondSeparatorItem;
	
	GtkToolItem * UndoItem;
	GtkToolItem * RedoItem;
	
	GtkToolItem * ThirdSeparatorItem;

	GtkToolItem * SearchItem;
	GtkToolItem * FontSelectItem;

	ToolBarPrivate * private_data;

};

// Callbacks ::
void x_cut_callback(GtkWidget *, gpointer);
void x_copy_callback(GtkWidget *, gpointer);
void x_paste_callback(GtkWidget *, gpointer);
void x_select_all_callback(GtkWidget *, gpointer);
void x_font_select_callback(GtkWidget *, gpointer);
gboolean x_toolbar_load_font_config (ToolBar *) G_GNUC_CONST;

// getters && setters :: ----
gchar * x_toolbar_get_font_desc (ToolBar *) G_GNUC_CONST;

void x_toolbar_set_font_desc (ToolBar *, gchar *);

// Methods ::
void x_toolbar_boxing(ToolBar *);
void x_toolbar_init(ToolBar *);
ToolBar * x_toolbar_new(void) G_GNUC_CONST;

#endif /* _TOOLBAR_H */