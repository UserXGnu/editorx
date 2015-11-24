/*
 * menubar.c
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

#include "definitions.h"


// Preferences window settings :: --------------------------------------------------------------
void x_menu_pref_window_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	GtkWidget * note;
	GtkWidget * window;
	GtkWidget * fixed;
	GtkWidget * label;
	GtkWidget * combo;
	GtkWidget * cb_auto_ident;
	GtkWidget * cb_highlight;
	GtkWidget * cb_line_num;
	GtkWidget * cb_hl_correntline;
	GtkWidget * close_button;

	GtkWidget * n_label[2];
	GtkWidget * scale;
	GtkWidget * trans_label;
	GtkWidget * vbox,
			  *	hbox;

	
	//gint width;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW(window), 340, 145);
	gtk_window_set_title(GTK_WINDOW(window), "EditorX - Preferences ");
	gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
	gtk_window_set_type_hint (GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_UTILITY);
	gtk_window_set_transient_for (GTK_WINDOW(window), GTK_WINDOW(xeditor->win->window));

	note = gtk_notebook_new ();
	n_label[0] = gtk_label_new("Text settings");
	n_label[1] = gtk_label_new ("View Settings");
	
	
	fixed = gtk_fixed_new ();

	cb_auto_ident = gtk_check_button_new_with_label ("Auto Ident");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(cb_auto_ident),
	                              x_menu_get_auto_ident_status(xeditor->menu));
	
	cb_highlight = gtk_check_button_new_with_label ("Syntax Highlight");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(cb_highlight),
	                              x_menu_get_highlight_status (xeditor->menu));

	cb_line_num = gtk_check_button_new_with_label ("Show Line Numbers");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(cb_line_num),
	                              x_menu_get_show_line_numbers_status (xeditor->menu));
	
	cb_hl_correntline = gtk_check_button_new_with_label ("Highligh corrent line");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(cb_hl_correntline),
	                              x_menu_get_highlight_corrent_line_status (xeditor->menu));
	
	label = gtk_label_new ("Tab Width: ");
	gtk_label_set_justify (GTK_LABEL(label), GTK_JUSTIFY_LEFT);
	combo = gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo), "2");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo), "4");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo), "6");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT(combo), "8");

	x_menu_combo_box_set_active (xeditor->menu, GTK_COMBO_BOX(combo));

	close_button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
	
	gtk_fixed_put (GTK_FIXED(fixed), cb_auto_ident, 5, 5);
	gtk_fixed_put (GTK_FIXED(fixed), cb_highlight, 5, 30);
	gtk_fixed_put (GTK_FIXED(fixed), label, 10, 65);
	gtk_fixed_put (GTK_FIXED(fixed), cb_line_num, 130, 5);
	gtk_fixed_put (GTK_FIXED(fixed), cb_hl_correntline, 130, 30);
	gtk_fixed_put (GTK_FIXED(fixed), combo, 80, 55);
	
	gtk_fixed_put (GTK_FIXED(fixed), close_button, 240, 75);

	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

	trans_label = gtk_label_new ("opacity");
	gtk_label_set_justify (GTK_LABEL(trans_label), GTK_JUSTIFY_CENTER);
	scale = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0.5, 1, 0.05);
	gtk_widget_set_tooltip_text (GTK_WIDGET(scale), "Choose opacity level");
	gtk_range_set_value (GTK_RANGE(scale), x_menu_get_scale_value_status (xeditor->menu) );

	
	gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 10);
	gtk_box_pack_start (GTK_BOX(vbox), trans_label, FALSE, FALSE, 1);
	gtk_box_pack_start (GTK_BOX(vbox), scale, FALSE, FALSE, 1);

	
	gtk_notebook_insert_page (GTK_NOTEBOOK (note), GTK_WIDGET(fixed), n_label[0], -1);
	gtk_notebook_insert_page (GTK_NOTEBOOK (note), GTK_WIDGET(hbox), n_label[1], -1);
	
	gtk_container_add (GTK_CONTAINER(window), note);

	g_signal_connect (cb_auto_ident, "clicked", G_CALLBACK(x_menu_set_auto_ident_callback), xeditor);
	g_signal_connect (cb_highlight, "clicked", G_CALLBACK(x_menu_set_highlight_callback), xeditor);
	g_signal_connect (cb_line_num, "clicked", G_CALLBACK(x_menu_set_show_line_numbers_callback), xeditor);
	g_signal_connect (cb_hl_correntline, "clicked", G_CALLBACK(x_menu_set_highlight_corrent_line_callback), xeditor);
	g_signal_connect (combo, "changed", G_CALLBACK(x_menu_set_tab_width_callback), xeditor);
	g_signal_connect(scale, "value-changed", G_CALLBACK(x_menu_scale_callback), xeditor);
	
	g_signal_connect (close_button, "clicked", G_CALLBACK(x_menu_pref_window_close_callback), window);

	gtk_widget_show_all (window);

}

void x_menu_combo_box_set_active (Menu * menu, GtkComboBox * combo) {
	gint width;
	
	switch(x_menu_get_tab_width (menu)){
		case 2:{
			width = 0;
			break;
		}case 4:{
			width = 1;
			break;
		}case 6:{
			width = 2;
			break;
		}case 8:{
			width = 3;
			break;
		}default:{
			width = 4;
			break;
		}
	}

	gtk_combo_box_set_active (GTK_COMBO_BOX(combo), width);
}



// setting highlight corrent line TRUE/FALSE ::
void x_menu_set_highlight_corrent_line_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;
	gboolean status = x_menu_get_highlight_corrent_line_status (xeditor->menu);

	if(status == TRUE) {
		x_menu_set_highlight_corrent_line (xeditor->menu, FALSE);
	}else {
		x_menu_set_highlight_corrent_line (xeditor->menu, TRUE);
	}
/*	status = x_menu_get_highlight_corrent_line_status (xeditor->menu);*/

	gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW(x_scrolled_get_source_view (xeditor->scrolled)),
	                                            x_menu_get_highlight_corrent_line_status (xeditor->menu));	
}


// setting tab ident width ::
void x_menu_set_tab_width_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;
	gint width;
	gint active = gtk_combo_box_get_active (GTK_COMBO_BOX(widget));
	switch( active ) {
		case 0: {
			width = 2;
			break;
		}case 1: {
			width = 4;
			break;
		}case 2: {
			width = 6;
			break;
		}case 3: {
			width = 8;
			break;
		}default:{
			width = 4;
			break;
		}
	}
	
	x_menu_set_tab_width (xeditor->menu, width);

	gtk_source_view_set_indent_width (GTK_SOURCE_VIEW(x_scrolled_get_source_view (xeditor->scrolled)),
	                                  width);
	
}



// auto ident callback
void x_menu_set_auto_ident_callback(GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;
	gboolean status = x_menu_get_auto_ident_status (xeditor->menu);
	if(status == TRUE){
		x_menu_set_auto_ident (xeditor->menu, FALSE);
	}else{
		x_menu_set_auto_ident (xeditor->menu, TRUE);
	}

	gtk_source_view_set_auto_indent (GTK_SOURCE_VIEW(x_scrolled_get_source_view (xeditor->scrolled)),
	                                 x_menu_get_auto_ident_status (xeditor->menu));
}



// setting syntax highlight
void x_menu_set_highlight_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	gboolean status = x_menu_get_highlight_status (xeditor->menu);

	if(status == FALSE){
		x_menu_set_highlight (xeditor->menu, TRUE);
	}else{
		x_menu_set_highlight (xeditor->menu, FALSE);
	}

	gtk_source_buffer_set_highlight_syntax (GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled)),
	                                        x_menu_get_highlight_status (xeditor->menu));
}



// setting show line numbers TRUE/FALSE ::
void x_menu_set_show_line_numbers_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	gboolean status = x_menu_get_show_line_numbers_status (xeditor->menu);

	if(status == FALSE){
		x_menu_set_show_line_numbers (xeditor->menu, TRUE);
	}else{
		x_menu_set_show_line_numbers (xeditor->menu, FALSE);
	}

	gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW(x_scrolled_get_source_view (xeditor->scrolled)),
	                                       x_menu_get_show_line_numbers_status (xeditor->menu));
}

void x_menu_scale_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	gfloat opacity = gtk_range_get_value (GTK_RANGE(widget));
	gtk_window_set_opacity (GTK_WINDOW(xeditor->win->window), opacity);
	x_menu_set_scale_value (xeditor->menu, opacity);
}


void x_menu_pref_window_close_callback (GtkWidget * widget, gpointer data) {
	gtk_widget_destroy(GTK_WIDGET(data));
}




// View Menu Items callbacks :: -------------------------------------------------------------
// Syntax highlight to C programming language ::
void x_menu_view_c_item_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	x_scrolled_set_mimetype (xeditor->scrolled, "c");
	
	x_scrolled_set_language (xeditor->scrolled,
	                         gtk_source_language_manager_get_language (GTK_SOURCE_LANGUAGE_MANAGER(x_scrolled_get_language_manager (xeditor->scrolled)),
	                                                                   x_scrolled_get_mimetype (xeditor->scrolled)) );
	gtk_source_buffer_set_language (GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer(xeditor->scrolled)),
	                                GTK_SOURCE_LANGUAGE(x_scrolled_get_language (xeditor->scrolled)));
}



// Syntax highlight to C++ programming language :: -----------------
void x_menu_view_cpp_item_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	x_scrolled_set_mimetype (xeditor->scrolled, "cpp");
	
	x_scrolled_set_language (xeditor->scrolled,
	                         gtk_source_language_manager_get_language (GTK_SOURCE_LANGUAGE_MANAGER(x_scrolled_get_language_manager (xeditor->scrolled)),
	                                                                   x_scrolled_get_mimetype (xeditor->scrolled)) );
	gtk_source_buffer_set_language (GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer(xeditor->scrolled)),
	                                GTK_SOURCE_LANGUAGE(x_scrolled_get_language (xeditor->scrolled)));
	
}




// Syntax highlight to python programming language ::
void x_menu_view_py_item_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	x_scrolled_set_mimetype (xeditor->scrolled, "python");
	
	x_scrolled_set_language (xeditor->scrolled,
	                         gtk_source_language_manager_get_language (GTK_SOURCE_LANGUAGE_MANAGER(x_scrolled_get_language_manager (xeditor->scrolled)),
	                                                                   x_scrolled_get_mimetype (xeditor->scrolled)) );
	gtk_source_buffer_set_language (GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer(xeditor->scrolled)),
	                                GTK_SOURCE_LANGUAGE(x_scrolled_get_language (xeditor->scrolled)));
	
}




// Syntax highlight to java programming language ::
void x_menu_view_java_item_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	x_scrolled_set_mimetype (xeditor->scrolled, "java");
	
	x_scrolled_set_language (xeditor->scrolled,
	                         gtk_source_language_manager_get_language (GTK_SOURCE_LANGUAGE_MANAGER(x_scrolled_get_language_manager (xeditor->scrolled)),
	                                                                   x_scrolled_get_mimetype (xeditor->scrolled)) );
	gtk_source_buffer_set_language (GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer(xeditor->scrolled)),
	                                GTK_SOURCE_LANGUAGE(x_scrolled_get_language (xeditor->scrolled)));
	
}



// syntax highlight to php programming language ::
void x_menu_view_php_item_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	x_scrolled_set_mimetype (xeditor->scrolled, "php");
	x_scrolled_set_language(xeditor->scrolled,
	                        gtk_source_language_manager_get_language (GTK_SOURCE_LANGUAGE_MANAGER(x_scrolled_get_language_manager (xeditor->scrolled)),
	                                                                  x_scrolled_get_mimetype (xeditor->scrolled)) );
	gtk_source_buffer_set_language(GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled)),
	                               GTK_SOURCE_LANGUAGE(x_scrolled_get_language (xeditor->scrolled)) );
	                        
	                                                                  
}



// syntax highlight to HTML programming language ::
void x_menu_view_html_item_callback (GtkWidget * widget, gpointer data) {
		XEditor * xeditor = (XEditor *)data;

	x_scrolled_set_mimetype (xeditor->scrolled, "html");
	x_scrolled_set_language(xeditor->scrolled,
	                        gtk_source_language_manager_get_language (GTK_SOURCE_LANGUAGE_MANAGER(x_scrolled_get_language_manager (xeditor->scrolled)),
	                                                                  x_scrolled_get_mimetype (xeditor->scrolled)) );
	gtk_source_buffer_set_language(GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled)),
	                               GTK_SOURCE_LANGUAGE(x_scrolled_get_language (xeditor->scrolled)) );
}


// Just a simple about-dialog :: -----------------------------------------------------------------
void x_menu_about_dialog_callback (GtkWidget * widget, gpointer data) {
	GError * err = NULL;
	GdkPixbuf * pixbuf;
	
	GtkWidget * dialog = gtk_about_dialog_new ();
	const gchar * authors[] = {"Victor Flores (UserX)", NULL};
	const gchar * artists[] = {"Afonsto Dantas (Fonfas)", NULL};
	gchar * license = 
		"Copyright (C) 2013 UserX <userx.gnu@gmail.com>\n\n"
		"Editor X is free software: you can redistribute it and/or modify it\n"
		"under the terms of the GNU General Public License as published by the\n"
		"Free Software Foundation, either version 3 of the License, or\n"
		"(at your option) any later version.\n\n"
		"Editor X is distributed in the hope that it will be useful, but\n"
		"WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n"
		"See the GNU General Public License for more details.\n"
		"You should have received a copy of the GNU General Public License along\n"
		"with this program.  If not, see <http://www.gnu.org/licenses/>.";

#ifdef X_EDITOR_VERSION
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (dialog),
	                              X_EDITOR_VERSION);
#endif
	gtk_about_dialog_set_website (GTK_ABOUT_DIALOG(dialog), "https://gitorious.org/editorx");
	gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (dialog), authors);
	gtk_about_dialog_set_artists (GTK_ABOUT_DIALOG(dialog), artists);

#ifdef COPYRIGHT
	gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (dialog), COPYRIGHT);
#endif

	gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (dialog),
	                               "Simple Text Editor with full features and plugins.");
	gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (dialog), license);
	
	
	pixbuf = gdk_pixbuf_new_from_file ("splash/splash.png", NULL);
	if(pixbuf == NULL){
		pixbuf = gdk_pixbuf_new_from_file ("../splash/splash.png", NULL);
		if(pixbuf == NULL){
			pixbuf = gdk_pixbuf_new_from_file (X_EDITOR_SPLASH_ADDR, &err);
			if(pixbuf == NULL){
				g_print("[GTK-EDITORX] Warning: %s\n", err->message);
			}
		}
	}
	if(pixbuf != NULL){
		gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG (dialog), pixbuf);
		g_object_unref (pixbuf);
		pixbuf = NULL;
	}
		
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);	
}





// Start GtkTextBuffer from scrolled->private_data with no data to ...
// simulate a new blank file :: --------------------------------------------------------------------
void x_menu_new_file_callback (GtkWidget * widget, gpointer data){
	XEditor * xeditor = (XEditor *)data;

	x_window_set_default_title (xeditor->win);
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled)), "", 0);
}


// load file content to text buffer 
gboolean x_menu_load_file_content_to_text_buffer(gpointer data, gchar * filename) {
	XEditor * xeditor = (XEditor *)data;

	GFile * file;
	GError * err = NULL;
	GFileInputStream * f_input;
	GDataInputStream * d_input;
	gchar * content;

	file = g_file_new_for_path (filename);
	f_input = g_file_read(file, NULL, &err);

	if(f_input == FALSE) {
		x_editor_dialog_warn (g_strdup_printf("[GTK-EDITORX] Warning: %s\n", err->message));
		x_editor_set_filename (xeditor, NULL);
		g_object_unref(file);
		g_error_free(err);
		file = NULL;
		return FALSE;
	}else{
		err = NULL;
		d_input = g_data_input_stream_new ((GInputStream *) f_input);
		content = g_data_input_stream_read_upto (G_DATA_INPUT_STREAM(d_input), "\0", -1, NULL, NULL, &err);
		
		if(content == NULL){
			x_editor_dialog_warn (g_strdup_printf("[GTK-EDITORX] Warning: %s\n", err->message));
			x_editor_set_filename (xeditor, NULL);
			g_input_stream_close ((GInputStream *)f_input, NULL, NULL);

			g_error_free(err);
			g_object_unref(f_input);
			g_object_unref(d_input);
			return FALSE;
		}else{
			x_editor_set_file(xeditor, file);
			gtk_text_buffer_set_text (GTK_TEXT_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled)), content, strlen(content));
			x_editor_set_save_status (xeditor, TRUE);
			g_input_stream_close ((GInputStream *)f_input, NULL, NULL);
			g_free(content);
			g_object_unref(f_input);
			g_object_unref(d_input);

			return TRUE;
		}
	}
}


// load a content of selected file from GtkFileChooserDialog :: -----------------------------------------
void x_menu_load_file_content_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;
	gboolean try;
	GtkResponseType answer;
	gchar * title;
	
	GtkWidget * dialog = gtk_file_chooser_dialog_new ("XEditor - Load File Dialog",
	                                                  NULL,
	                                                  GTK_FILE_CHOOSER_ACTION_OPEN,
	                                                  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                                  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
	                                                  NULL);
	
#ifdef X_USER_DEFAULT_PATH
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(dialog), X_USER_DEFAULT_PATH);
#endif
	
	answer = gtk_dialog_run(GTK_DIALOG(dialog));
	if(answer == GTK_RESPONSE_ACCEPT) {

		x_editor_set_filename (xeditor, gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(dialog)) );
		
		try = x_menu_load_file_content_to_text_buffer (xeditor, x_editor_get_filename (xeditor));
		if(try == FALSE){
			gtk_widget_destroy(dialog);
			return;
		}

		// trying to discover and config language for highlight ::
		x_scrolled_language_self_config (xeditor->scrolled, x_editor_get_filename (xeditor));
		
		title = g_strdup (X_WINDOW_DEFAULT_TITLE);
		title = g_strconcat (title, "(", x_editor_get_filename (xeditor), ")", NULL);
		x_window_set_title (xeditor->win, title);
		
		
	}
	
	gtk_widget_destroy (dialog);
}




// save all GtkTextBuffer content to a selected file :: ----------------------------------
void x_menu_save_content_to_selected_file_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;
	GFile * file;
	gchar * content = NULL;
	gchar * title;
	gchar * path;

	content = x_scrolled_get_sourcebuffer_content (xeditor->scrolled);
	
	if((x_editor_get_file(xeditor)) != NULL) {
		
		x_editor_save_textbuffer_content (xeditor, content);

		title = g_strdup (X_WINDOW_DEFAULT_TITLE);
		title = g_strconcat(title, "(", x_editor_get_filename (xeditor), ")", NULL);
		x_window_set_title (xeditor->win, title);
		
		x_scrolled_language_self_config (xeditor->scrolled, x_editor_get_filename (xeditor));
		
	}else {

		GtkResponseType answer;

		GtkWidget * dialog = gtk_file_chooser_dialog_new("XEditor - Save Content Dialog",
		                                                 NULL,
		                                                 GTK_FILE_CHOOSER_ACTION_SAVE,
		                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
		                                                 GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
		                                                 NULL);
		gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog), TRUE);
		gtk_file_chooser_set_create_folders (GTK_FILE_CHOOSER(dialog), TRUE);

#ifdef X_USER_DEFAULT_PATH
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(dialog), X_USER_DEFAULT_PATH);
#endif

		answer = gtk_dialog_run(GTK_DIALOG(dialog));

		if(answer == GTK_RESPONSE_ACCEPT){
			file = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(dialog));
			path = g_file_get_path (file);

			x_editor_set_file(xeditor, file);
			x_editor_set_filename(xeditor, path);
			
			x_editor_save_textbuffer_content (xeditor, content);
			x_scrolled_language_self_config (xeditor->scrolled, x_editor_get_filename (xeditor));
			
			title = g_strdup (X_WINDOW_DEFAULT_TITLE);
			title = g_strconcat(title, "(", x_editor_get_filename (xeditor), ")", NULL);
			x_window_set_title (xeditor->win, title);

		}
		gtk_widget_destroy(dialog);
	}
	
}




// As before, but It will show Save Dialog (GtkFileChooserDialog)everytime :: ----------------------------------
void x_menu_save_as_content_to_selected_file_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	GtkResponseType answer;
	gchar * title;

	GtkWidget * dialog = gtk_file_chooser_dialog_new("XEditor - Save Content Dialog",
	                                                 NULL,
	                                                 GTK_FILE_CHOOSER_ACTION_SAVE,
	                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                                 GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
	                                                 NULL);
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER(dialog), TRUE);
	gtk_file_chooser_set_create_folders (GTK_FILE_CHOOSER(dialog), TRUE);
	
#ifdef X_USER_DEFAULT_PATH
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(dialog), X_USER_DEFAULT_PATH);
#endif

	answer = gtk_dialog_run(GTK_DIALOG(dialog));
	
	if(answer == GTK_RESPONSE_ACCEPT) {
		
		x_editor_set_file (xeditor, gtk_file_chooser_get_file (GTK_FILE_CHOOSER(dialog)) );

		x_editor_set_filename (xeditor, g_file_get_path (x_editor_get_file (xeditor)) );



		x_editor_save_textbuffer_content (xeditor, x_scrolled_get_sourcebuffer_content (xeditor->scrolled) );

		// trying 
		x_scrolled_language_self_config (xeditor->scrolled, x_editor_get_filename (xeditor));
		
		title = g_strdup (X_WINDOW_DEFAULT_TITLE);
		title = g_strconcat(title, "(", x_editor_get_filename (xeditor), ")", NULL);
		x_window_set_title (xeditor->win, title);

	}
	gtk_widget_destroy(dialog);			
}




// Edito menu items callbacks :: ------------------------------------------
// undo callback ::
void x_menu_undo_callback (GtkWidget * widget, gpointer data) {
	Scrolled * swindow = (Scrolled *)data;
	GtkSourceBuffer * sBuff = x_scrolled_get_source_buffer (swindow);
	
	if( (gtk_source_buffer_can_undo (GTK_SOURCE_BUFFER(sBuff)) ) == TRUE){
		gtk_source_buffer_undo (GTK_SOURCE_BUFFER (sBuff));
	}
}




// redo callback ::
void x_menu_redo_callback (GtkWidget * widget, gpointer data) {
	Scrolled * swindow = (Scrolled *)data;
	
	GtkSourceBuffer * sBuff = x_scrolled_get_source_buffer (swindow);

	if((gtk_source_buffer_can_redo (GTK_SOURCE_BUFFER(sBuff))) == TRUE){
		gtk_source_buffer_redo (GTK_SOURCE_BUFFER(sBuff));
	}
}




// Means like copy, cut, paste ... so easy :: ------------------------------------------------
void x_menu_cut_selected_range (GtkWidget * widget, gpointer data) {
	Scrolled * t_scrolled = (Scrolled *)data;

	
	gtk_text_buffer_cut_clipboard (GTK_TEXT_BUFFER(x_scrolled_get_source_buffer(t_scrolled)),
	                               GTK_CLIPBOARD(x_scrolled_get_clipboard (t_scrolled)), TRUE);
}




// As before :: ----------------------------------------------------------------------------
void x_menu_copy_selected_range (GtkWidget * widget, gpointer data) {
	Scrolled * t_scrolled = (Scrolled *)data;

	gtk_text_buffer_copy_clipboard (GTK_TEXT_BUFFER(x_scrolled_get_source_buffer(t_scrolled)),
	                                GTK_CLIPBOARD(x_scrolled_get_clipboard (t_scrolled)));
}

void x_menu_paste (GtkWidget * widget, gpointer data){
	Scrolled * t_scrolled = (Scrolled *)data;

	gtk_text_buffer_paste_clipboard (GTK_TEXT_BUFFER(x_scrolled_get_source_buffer (t_scrolled)),
	                                 GTK_CLIPBOARD(x_scrolled_get_clipboard (t_scrolled)),
	                                 NULL,
	                                 TRUE);
}




// It means select all of text editor  - obviously:: ------------------------
void x_menu_select_all_callback (GtkWidget * widget, gpointer data) {
	GtkTextIter begin;
	GtkTextIter end;

	gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(data), &begin);
	gtk_text_buffer_get_end_iter (GTK_TEXT_BUFFER(data), &end);
	gtk_text_buffer_select_range (GTK_TEXT_BUFFER(data), &begin, &end);
}




// clears source buffer ::
void x_menu_clear_source_buffer_callback (GtkWidget * widget, gpointer data) {
	gtk_text_buffer_set_text (GTK_TEXT_BUFFER(data), "", 0);
}


// search callback ::
void x_menu_search_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;
	search_app * search = x_editor_search_new ( xeditor );
	if(search != NULL){
		GtkWidget * vbox = GTK_WIDGET(xeditor->win->box);

		gtk_box_pack_end(GTK_BOX(vbox), search->box, FALSE, FALSE, 5);
		gtk_widget_grab_focus (GTK_WIDGET(search->s_entry));
	}
}



// -------------------------------- Callbacks ---------------------------------- //



// Initiate private data from Menu class:: -----------
void x_menu_init(Menu * menu) {
	menu->private_data = (MenuPrivate *) g_malloc(sizeof(MenuPrivate));
	FILE * fd;
	gchar * PATH;
	
	PATH = g_strconcat(X_USER_DEFAULT_PATH, X_EDITOR_CONFIG_FILE, NULL);	
	if((fd = fopen(PATH, "r")) != NULL) {
		if((fread(menu->private_data, sizeof(MenuPrivate), 1, fd)) <= 0){
			
			x_menu_set_scale_value (menu, 1);
			x_menu_set_auto_ident (menu, FALSE);
			x_menu_set_highlight (menu, FALSE);
			x_menu_set_show_line_numbers (menu, FALSE);
			x_menu_set_highlight_corrent_line (menu, FALSE);
			x_menu_set_tab_width (menu, 4);

			g_print("[GTK-EDITORX] Warning: error reading config file [!!]\n");
		}else{
			g_print("[GTK-EDITORX] Config file read successfully [!!]\n");
		}
		fclose(fd);
		fflush(fd);
	}else {
		// alteração ::
		x_menu_set_scale_value (menu, 1);
		x_menu_set_auto_ident (menu, FALSE);
		x_menu_set_highlight (menu, FALSE);
		x_menu_set_show_line_numbers (menu, FALSE);
		x_menu_set_highlight_corrent_line (menu, FALSE);
		x_menu_set_tab_width (menu, 4);
		
		PATH = g_strconcat("mkdir ", X_USER_DEFAULT_PATH, "/.xeditor", NULL);
		if(system(PATH) < 0){
			g_print("[GTK-EDITORX] WARNING: Error creating application folder [!!]\n");
		}
		
		PATH = NULL;
		PATH = g_strconcat(X_USER_DEFAULT_PATH, X_EDITOR_CONFIG_FILE, NULL);
		fd = fopen(PATH, "w");
		if(fd != NULL){
			if((fwrite(menu->private_data, sizeof(MenuPrivate), 1, fd)) <=  0){
				g_print("[GTK-EDITORX] WARNING: Error writing to config file [!!]\n");
			}else{
				g_print("[GTK-EDITORX] DATA was sucessfuly wrote [!!]\n");
			}
			fclose(fd);
			fflush(fd);
		}else{
			g_print("[GTK-EDITORX] WARNING: Error openning config file [!!]\n");
		}
	}
}




// create every menu :: ---------------------------------------------------------
void x_create_menus (Menu * menu){
	menu->MenuBar = gtk_menu_bar_new();

	menu->FileMenu = gtk_menu_new();
	menu->EditMenu = gtk_menu_new();
	menu->ViewMenu = gtk_menu_new();
	menu->HelpMenu = gtk_menu_new();
	menu->ViewSbmenu = gtk_menu_new ();

	menu->FileMenuItem = gtk_menu_item_new_with_mnemonic ("_File");
	menu->EditMenuItem = gtk_menu_item_new_with_mnemonic ("_Edit");
	menu->ViewMenuItem = gtk_menu_item_new_with_mnemonic ("_View");
	menu->HelpMenuItem = gtk_menu_item_new_with_mnemonic ("_Help");

	
	menu->NewFileItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, NULL);
	menu->OpenFileItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_OPEN, NULL);
	menu->SaveFileItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE, NULL);
	menu->SaveAsFileItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE_AS, NULL);
	menu->ExitFileItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);

	menu->UndoEditItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO, NULL);
	menu->RedoEditItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_REDO, NULL);
	menu->CutEditItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_CUT, NULL);
	menu->CopyEditItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY, NULL);
	menu->PasteEditEditem = gtk_image_menu_item_new_from_stock (GTK_STOCK_PASTE, NULL);
	menu->SelectAllEditItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_SELECT_ALL, NULL);
	menu->ClearEditItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLEAR, NULL);
	menu->SearchEditItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_FIND_AND_REPLACE, NULL);
	menu->PrefEditItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_PREFERENCES, NULL);

	menu->LangViewItem = gtk_menu_item_new_with_mnemonic ("_Source View");
	menu->cViewItem = gtk_menu_item_new_with_mnemonic ("_C");
	menu->cppViewItem = gtk_menu_item_new_with_mnemonic ("_C++");
	menu->pyViewItem = gtk_menu_item_new_with_mnemonic ("_Python");
	menu->jvViewItem = gtk_menu_item_new_with_mnemonic ("_Java");
	menu->phpViewItem = gtk_menu_item_new_with_mnemonic ("_Php");
	menu->htmlViewItem = gtk_menu_item_new_with_mnemonic ("_Html");
	
	menu->AboutHelpItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, NULL);
}




// Packing every menus from Menu class :: -----------------------------------------------------
void x_menu_pack_menus (Menu * menu){
	GtkWidget * sep[4];
	
	sep[0] = gtk_separator_menu_item_new ();
	sep[1] = gtk_separator_menu_item_new ();
	sep[2] = gtk_separator_menu_item_new ();
	sep[3] = gtk_separator_menu_item_new ();
	
	// File Menu ::
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu->FileMenuItem), menu->FileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->FileMenu), menu->NewFileItem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->FileMenu), menu->OpenFileItem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->FileMenu), menu->SaveFileItem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->FileMenu), menu->SaveAsFileItem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->FileMenu), sep[0]);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->FileMenu), menu->ExitFileItem);

	gtk_menu_shell_append(GTK_MENU_SHELL(menu->MenuBar), menu->FileMenuItem);

	// Edit Menu ::
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu->EditMenuItem), menu->EditMenu);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->EditMenu), menu->UndoEditItem);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->EditMenu), menu->RedoEditItem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->EditMenu), sep[1]);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu->EditMenu), menu->CutEditItem);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu->EditMenu), menu->CopyEditItem);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu->EditMenu), menu->PasteEditEditem);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu->EditMenu), menu->SelectAllEditItem);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu->EditMenu), menu->ClearEditItem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->EditMenu), sep[2]);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu->EditMenu), menu->SearchEditItem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu->EditMenu), sep[3]);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->EditMenu), menu->PrefEditItem);
	
	gtk_menu_shell_append (GTK_MENU_SHELL (menu->MenuBar), menu->EditMenuItem);

	// View Menu ::
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu->ViewMenuItem), menu->ViewMenu);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->ViewMenu), menu->LangViewItem);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu->MenuBar), menu->ViewMenuItem);
	
	// view Submenu ::
	gtk_menu_item_set_submenu (GTK_MENU_ITEM(menu->LangViewItem), menu->ViewSbmenu );
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->ViewSbmenu), menu->cViewItem);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->ViewSbmenu), menu->cppViewItem);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->ViewSbmenu), menu->pyViewItem);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->ViewSbmenu), menu->jvViewItem);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->ViewSbmenu), menu->phpViewItem);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->ViewSbmenu), menu->htmlViewItem);
	
	// Help Menu ::
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu->HelpMenuItem), menu->HelpMenu);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->HelpMenu), menu->AboutHelpItem);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu->MenuBar), menu->HelpMenuItem);
}


// creating and configuring accelerators ::
void x_menu_configure_accel (Menu * menu, gpointer data) {
	Window * win = (Window *)data;
	gint key;
	
	menu->accel_group = NULL;
	GtkAccelGroup * group = menu->accel_group;

	group = gtk_accel_group_new ();

	gtk_window_add_accel_group (GTK_WINDOW(win->window), GTK_ACCEL_GROUP(group));

	// file menu items accel
	key = gdk_keyval_from_name ("n");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->NewFileItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("o");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->OpenFileItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("s");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->SaveFileItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("a");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->SaveAsFileItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("e");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->ExitFileItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);

	

	// edit menu accel
	key = gdk_keyval_from_name ("z");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->UndoEditItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("r");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->RedoEditItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("x");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->CutEditItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("c");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->CopyEditItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("v");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->PasteEditEditem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("a");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->SelectAllEditItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("l");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->ClearEditItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("f");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->SearchEditItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	key = gdk_keyval_from_name ("p");
	gtk_widget_add_accelerator (GTK_WIDGET(menu->PrefEditItem), "activate", GTK_ACCEL_GROUP(group), key,
	                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

}

// getters :: ----------------------------------------------------------

gboolean * x_menu_get_auto_ident (Menu * menu) {
	return &(menu->private_data)->auto_ident;
}

gboolean * x_menu_get_highlight (Menu * menu) {
	return &(menu->private_data)->highlight;
}

gboolean * x_menu_get_line_numbers (Menu * menu) {
	return &(menu->private_data)->line_numbers;
}

gboolean * x_menu_get_highlight_corrent_line (Menu * menu) {
	return &(menu->private_data)->hl_correntline;
}

gint * x_menu_get_tab_width_ref (Menu * menu) {
	return &(menu->private_data)->tab_width;
}

gfloat * x_menu_get_scale_value (Menu * menu) {
	return &(menu->private_data)->opacity;	
}
gboolean x_menu_get_auto_ident_status (Menu * menu) {
	return menu->private_data->auto_ident;
}

gboolean x_menu_get_highlight_status (Menu * menu) {
	return menu->private_data->highlight;
}

gboolean x_menu_get_show_line_numbers_status (Menu * menu) {
	return menu->private_data->line_numbers;
}

gboolean x_menu_get_highlight_corrent_line_status (Menu * menu) {
	return menu->private_data->hl_correntline;
}

gint x_menu_get_tab_width (Menu * menu) {
	return menu->private_data->tab_width;
}

gfloat x_menu_get_scale_value_status (Menu * menu) {
	return menu->private_data->opacity;
}
// setters :: ----------------------------------------------------------------------------

void x_menu_set_auto_ident (Menu * menu, gboolean status) {
	menu->private_data->auto_ident = status;
}

void x_menu_set_highlight (Menu * menu, gboolean status) {
	menu->private_data->highlight = status;
}

void x_menu_set_show_line_numbers (Menu * menu, gboolean status) {
	menu->private_data->line_numbers = status;
}

void x_menu_set_highlight_corrent_line (Menu * menu, gboolean status) {
	menu->private_data->hl_correntline = status;
}

void x_menu_set_tab_width (Menu * menu, gint width) {
	menu->private_data->tab_width = width;
}

void x_menu_set_scale_value (Menu * menu, gfloat value) {
	menu->private_data->opacity = value;
}

// intanciate Menu class :: --------------------------------------------------------------
Menu * x_menu_new() {
	Menu * menu = (Menu *) g_malloc(sizeof(Menu));

	x_menu_init(menu);
	x_create_menus (menu);
	x_menu_pack_menus (menu);
	
	return menu;
}
