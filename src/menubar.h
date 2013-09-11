/*
 * menubar.h
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
#ifndef _MENUBAR_H
#define _MENUBAR_H

typedef struct _menuprivate MenuPrivate;
struct _menuprivate {
	
	gboolean auto_ident, 
			 highlight,
			 line_numbers,
			 hl_correntline;
	
	gfloat opacity;
	gint tab_width;
/*	gint time;*/
	
};

typedef struct _menu Menu;
struct _menu {
	GtkWidget * MenuBar;

	GtkWidget * FileMenu;
	GtkWidget * EditMenu;
	GtkWidget * ViewMenu;
	GtkWidget * HelpMenu;
	
	GtkWidget * FileMenuItem;
	GtkWidget * EditMenuItem;
	GtkWidget * ViewMenuItem;
	GtkWidget * HelpMenuItem;
	
	GtkWidget * NewFileItem;
	GtkWidget * OpenFileItem;
	GtkWidget * SaveFileItem;
	GtkWidget * SaveAsFileItem;
	GtkWidget * ExitFileItem;

	GtkWidget * UndoEditItem;
	GtkWidget * RedoEditItem;
	GtkWidget * CopyEditItem;
	GtkWidget * CutEditItem;
	GtkWidget * PasteEditEditem;
	GtkWidget * SelectAllEditItem;
	GtkWidget * ClearEditItem;
	GtkWidget * SearchEditItem;
	GtkWidget * PrefEditItem;

	GtkWidget * ViewSbmenu;
	GtkWidget * LangViewItem;
	GtkWidget * cViewItem;
	GtkWidget * cppViewItem;
	GtkWidget * pyViewItem;
	GtkWidget * jvViewItem;
	GtkWidget * phpViewItem;
	GtkWidget * htmlViewItem;
	
	GtkWidget * AboutHelpItem;

	GtkAccelGroup * accel_group;
	MenuPrivate * private_data;

};

// callbacks ::
// help menu items callbacks ::
void x_menu_about_dialog_callback (GtkWidget *, gpointer);

// File menu items callbacks ::
void x_menu_new_file_callback (GtkWidget *, gpointer);
void x_menu_load_file_content_callback (GtkWidget *, gpointer);
void x_menu_save_content_to_selected_file_callback (GtkWidget *, gpointer);
void x_menu_save_as_content_to_selected_file_callback (GtkWidget *, gpointer);

// Edit menu items callbacks ::
void x_menu_undo_callback (GtkWidget *, gpointer);
void x_menu_redo_callback (GtkWidget *, gpointer);
void x_menu_cut_selected_range (GtkWidget *, gpointer);
void x_menu_copy_selected_range (GtkWidget *, gpointer);
void x_menu_paste (GtkWidget *, gpointer);
void x_menu_select_all_callback (GtkWidget *, gpointer);
void x_menu_clear_source_buffer_callback (GtkWidget *, gpointer);
void x_menu_search_callback (GtkWidget *, gpointer);
void x_menu_pref_window_callback(GtkWidget *, gpointer);

// preferences winindow callbacks ::
void x_menu_set_auto_ident_callback (GtkWidget *, gpointer);
void x_menu_set_highlight_callback (GtkWidget *, gpointer);
void x_menu_set_show_line_numbers_callback (GtkWidget *, gpointer);
void x_menu_set_highlight_corrent_line_callback (GtkWidget *, gpointer);
void x_menu_set_tab_width_callback (GtkWidget *, gpointer);
void x_menu_scale_callback (GtkWidget *, gpointer);
void x_menu_pref_window_close_callback (GtkWidget *, gpointer);
void x_menu_combo_box_set_active (Menu *, GtkComboBox *);


// View menu items callbacks ::
void x_menu_view_c_item_callback (GtkWidget *, gpointer);
void x_menu_view_py_item_callback (GtkWidget *, gpointer);
void x_menu_view_cpp_item_callback (GtkWidget *, gpointer);
void x_menu_view_java_item_callback (GtkWidget *, gpointer);
void x_menu_view_php_item_callback (GtkWidget *, gpointer);
void x_menu_view_html_item_callback (GtkWidget *, gpointer);


// methods ::
gboolean x_menu_load_file_content_to_text_buffer(gpointer, gchar *) G_GNUC_CONST;
void x_menu_init (Menu *);
void x_create_menus (Menu *);
void x_menu_pack_menus (Menu *);
void x_menu_configure_accel (Menu *, gpointer);

// getters ::
gboolean * x_menu_get_auto_ident (Menu *) G_GNUC_CONST;
gboolean * x_menu_get_highlight (Menu *) G_GNUC_CONST;
gboolean * x_menu_get_line_numbers (Menu *) G_GNUC_CONST;
gboolean * x_menu_get_highlight_corrent_line (Menu *) G_GNUC_CONST;
gint * x_menu_get_tab_width_ref (Menu *) G_GNUC_CONST;
gfloat * x_menu_get_scale_value (Menu *) G_GNUC_CONST;

gboolean x_menu_get_auto_ident_status (Menu *) G_GNUC_CONST;
gboolean x_menu_get_highlight_status (Menu *) G_GNUC_CONST;
gboolean x_menu_get_show_line_numbers_status (Menu *) G_GNUC_CONST;
gboolean x_menu_get_highlight_corrent_line_status (Menu *) G_GNUC_CONST;
gint x_menu_get_tab_width (Menu *) G_GNUC_CONST;
gfloat x_menu_get_scale_value_status (Menu *) G_GNUC_CONST;


// setters ::
void x_menu_set_auto_ident (Menu *, gboolean);
void x_menu_set_highlight (Menu *, gboolean);
void x_menu_set_show_line_numbers (Menu *, gboolean);
void x_menu_set_highlight_corrent_line (Menu *, gboolean);
void x_menu_set_tab_width (Menu *, gint);
void x_menu_set_scale_value (Menu *, gfloat);

// constructor :: ---------------
Menu * x_menu_new(void) G_GNUC_CONST;

#endif /* _MENUBAR_H */
