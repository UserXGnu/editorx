/*
 * xeditor.c
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

// Callbacks ::


// the function's pseudo-name says everything :: --------------------------------------------------------
static gboolean x_editor_delete_event_callback (GtkWidget * widget, gpointer data){
	GtkResponseType answer;

	GtkWidget * dialog = gtk_dialog_new_with_buttons("Are you sure?",
	                                                 NULL,
	                                                 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
	                                                 GTK_STOCK_YES, GTK_RESPONSE_OK,
	                                                 GTK_STOCK_NO, GTK_RESPONSE_NO,
	                                                 NULL);
	gtk_dialog_set_default_response (GTK_DIALOG(dialog), GTK_RESPONSE_NO);

	answer = gtk_dialog_run(GTK_DIALOG(dialog));
	if(answer == GTK_RESPONSE_OK){
		return FALSE;
	}else{
		gtk_widget_destroy(dialog);
		return TRUE;
	}
}




// desctructor :: -------------------------------------------------------------------------
void x_editor_destroy_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;
	gchar * PATH = g_strconcat(X_USER_DEFAULT_PATH, X_EDITOR_CONFIG_FILE, NULL);
	FILE * fd = fopen(PATH, "w");
	if(fd != NULL){
		if( (fwrite(xeditor->menu->private_data, sizeof(MenuPrivate), 1, fd)) != 1) {
			g_print("[GTK-EDITORX] WARNING: Error writing to config file [!!]\n");
		}
		fclose(fd);
		fflush(fd);
	}

	g_free(xeditor->statusbar);
	xeditor->statusbar = NULL;

	pango_font_description_free (x_scrolled_get_font_description (xeditor->scrolled));
	x_editor_save_font_config (xeditor);
	
	g_free(xeditor->scrolled->private_data);
	g_free(xeditor->scrolled);

	g_free(xeditor->toolbar);

	g_free(xeditor->menu->private_data);
	g_free(xeditor->menu);

	g_free(xeditor->win->private_data);
	g_free(xeditor->win);

	if(xeditor->private_data->file != NULL){
		g_object_unref (xeditor->private_data->file);
		x_editor_set_file (xeditor, NULL);
	}

	g_free (xeditor->private_data);
	g_free(xeditor);

	gtk_main_quit();
}



void x_window_close_callback (GtkWidget * widget, gpointer data) {

	if((x_editor_delete_event_callback (NULL, NULL)) == FALSE){
		gtk_widget_destroy (data);
	}

}




// getters for private data :: ----------------------------------
GFile * x_editor_get_file (XEditor * xeditor){
	return xeditor->private_data->file;
}

gchar * x_editor_get_filename (XEditor * xeditor) {
	return xeditor->private_data->filename;
}

gboolean * x_editor_get_save_status (XEditor * xeditor) {
	return &(xeditor->private_data)->save;
}

gboolean x_editor_get_save (XEditor * xeditor) {
	return xeditor->private_data->save;
}

gboolean * x_editor_get_search_flag (XEditor * xeditor) {
	return &(xeditor->private_data)->search_flag;
}

gboolean x_editor_get_search_flag_status (XEditor * xeditor) {
	return xeditor->private_data->search_flag;
}




// setters for private dada :: --------------------------------------------
void x_editor_set_file (XEditor * xeditor, GFile * file_t) {
	xeditor->private_data->file = file_t;
}

void x_editor_set_filename (XEditor * xeditor, gchar * filename) {
	xeditor->private_data->filename = g_strdup(filename);
}

void x_editor_set_save_status (XEditor * xeditor, gboolean status) {
	xeditor->private_data->save = status;
}

void x_editor_set_search_flag (XEditor * xeditor, gboolean status){
	xeditor->private_data->search_flag = status;
}




// another methods :: -----------------------------------------------


void x_editor_save_textbuffer_content(XEditor * xeditor, gchar * content) {
	GFileOutputStream * output;
	GDataOutputStream * data_output;

	output = g_file_replace (x_editor_get_file (xeditor),
	                         NULL, TRUE,
	                         G_FILE_CREATE_REPLACE_DESTINATION,
	                         NULL, NULL);
	data_output = g_data_output_stream_new ( (GOutputStream *) output);
	g_data_output_stream_put_string (G_DATA_OUTPUT_STREAM(data_output),
	                                 content, NULL, NULL);
	g_output_stream_close ( (GOutputStream *) output, NULL, NULL);
	x_editor_set_save_status (xeditor, TRUE);

	g_object_unref (output);
	g_object_unref (data_output);

}





void x_editor_save_font_config (XEditor * xeditor){
	GFile * fd;
	GError * err = NULL;
	GFileOutputStream * o_stream;
	GDataOutputStream * do_stream;
	gchar * font_desc = x_toolbar_get_font_desc (xeditor->toolbar);
	gboolean try;
	
	if(font_desc == NULL){
		font_desc = pango_font_description_to_string (x_scrolled_get_font_description (xeditor->scrolled));
		x_toolbar_set_font_desc (xeditor->toolbar, font_desc);
	}
	gchar * path = g_strconcat (X_USER_DEFAULT_PATH, X_EDITOR_FONT_CONFIG_FILE, NULL);

	fd = g_file_new_for_path (path);
	o_stream = g_file_replace (fd, NULL, TRUE,
	                           G_FILE_CREATE_REPLACE_DESTINATION, NULL, &err);
	if(o_stream == NULL){
		g_print("[GTK-EDITORX] Warning: %s\n", err->message);
		g_object_unref(fd);
		return;
	}
	do_stream = g_data_output_stream_new ((GOutputStream *)o_stream);
	try = g_data_output_stream_put_string (G_DATA_OUTPUT_STREAM(do_stream),
	                                       x_toolbar_get_font_desc (xeditor->toolbar), NULL, &err);
	if(try == FALSE){
		g_print("[GTK-EDITORX] Warning: %s\n", err->message);
		g_output_stream_clear_pending ((GOutputStream *) o_stream);
		g_output_stream_close ((GOutputStream *)o_stream, NULL, NULL);
		
		g_object_unref (fd);
		g_object_unref (o_stream);
		g_object_unref (do_stream);
		return;
	}else{
		g_object_unref (fd);
		g_object_unref (o_stream);
		g_object_unref (do_stream);
		g_print("[GTK-EDITORX] Font Config File saved with successfully [!!]\n");
	}
}





void x_editor_apply_font_config (XEditor * xeditor) {
	gchar * font_desc = x_toolbar_get_font_desc (xeditor->toolbar);
	x_text_view_set_default_font (xeditor->scrolled, font_desc);
}


void x_dialog_warn_quit(GtkWidget * widget, gpointer  data){
	gtk_widget_destroy (GTK_WIDGET(data));
}

void x_editor_dialog_warn (gchar * warning) {
	GtkWidget * dialog = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_type_hint (GTK_WINDOW(dialog), GDK_WINDOW_TYPE_HINT_NOTIFICATION);
	gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	
	GtkWidget * image = gtk_image_new_from_stock (GTK_STOCK_DIALOG_WARNING, GTK_ICON_SIZE_DIALOG);
	GtkWidget * label = gtk_label_new(warning);
	GtkWidget * button = gtk_button_new_from_stock (GTK_STOCK_OK);
	GtkWidget * box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget * hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	
	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(box), hbox, TRUE, TRUE, 5);
	
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, TRUE, 10);

	gtk_container_add(GTK_CONTAINER(dialog), box);
	
	g_signal_connect(button, "clicked", G_CALLBACK(x_dialog_warn_quit), dialog);
	g_signal_connect(dialog, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
	
	gtk_widget_show_all(dialog);

}



void x_editor_show_all(XEditor * xeditor){
	gtk_widget_show_all(xeditor->win->window);

	x_statusbar_update_callback (GTK_TEXT_BUFFER(x_scrolled_get_source_buffer(xeditor->scrolled)),
	                             xeditor->statusbar->sBar);
	gtk_widget_grab_focus (GTK_WIDGET(x_scrolled_get_source_view (xeditor->scrolled)));
}




// connect all signals of every widget of XEditor class and its subclasses ::
void x_editor_connect_all_signals (XEditor * xeditor){


	// callback for statusbar :: -------------------------------
	g_signal_connect(GTK_TEXT_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled) ), "changed",
	                 G_CALLBACK(x_statusbar_update_callback), xeditor->statusbar->sBar);

	g_signal_connect_object(GTK_TEXT_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled) ), "mark_set",
	                        G_CALLBACK(x_mark_callback), xeditor->statusbar->sBar, 0);



	// callbacks for tool itens from toolbar class :: ---------------------------
	g_signal_connect(xeditor->toolbar->SaveItem, "clicked",
	                 G_CALLBACK(x_menu_save_content_to_selected_file_callback),
	                 xeditor);

	g_signal_connect(xeditor->toolbar->OpenItem, "clicked",
	                 G_CALLBACK(x_menu_load_file_content_callback), xeditor);

	g_signal_connect(xeditor->toolbar->CutItem, "clicked",
	                 G_CALLBACK(x_menu_cut_selected_range), xeditor->scrolled);

	g_signal_connect(xeditor->toolbar->CopyItem, "clicked",
	                 G_CALLBACK(x_menu_copy_selected_range), xeditor->scrolled);

	g_signal_connect(xeditor->toolbar->PasteItem, "clicked",
	                 G_CALLBACK(x_menu_paste), xeditor->scrolled);

	g_signal_connect(xeditor->toolbar->SelectAllItem, "clicked",
	                 G_CALLBACK(x_menu_select_all_callback),
	                 x_scrolled_get_source_buffer (xeditor->scrolled));

	g_signal_connect(xeditor->toolbar->UndoItem, "clicked",
	                 G_CALLBACK(x_menu_undo_callback), xeditor->scrolled);

	g_signal_connect(xeditor->toolbar->RedoItem, "clicked",
	                 G_CALLBACK(x_menu_redo_callback), xeditor->scrolled);
	
	g_signal_connect(xeditor->toolbar->SearchItem, "clicked",
	                 G_CALLBACK(x_menu_search_callback), xeditor);

	g_signal_connect(xeditor->toolbar->FontSelectItem, "clicked",
	                 G_CALLBACK(x_font_select_callback), xeditor);

	

	
	// callbacks for menu items from menu class :: ---------------------------
	g_signal_connect(xeditor->menu->NewFileItem, "activate",
	                 G_CALLBACK(x_menu_new_file_callback), xeditor);

	g_signal_connect(xeditor->menu->OpenFileItem, "activate",
	                 G_CALLBACK(x_menu_load_file_content_callback), xeditor);

	g_signal_connect(xeditor->menu->SaveFileItem, "activate",
	                 G_CALLBACK(x_menu_save_content_to_selected_file_callback), xeditor);

	g_signal_connect(xeditor->menu->SaveAsFileItem, "activate",
	                 G_CALLBACK(x_menu_save_as_content_to_selected_file_callback), xeditor);

	g_signal_connect(xeditor->menu->ExitFileItem, "activate",
	                 G_CALLBACK(x_window_close_callback), xeditor->win->window);

	g_signal_connect(xeditor->menu->AboutHelpItem, "activate",
	                 G_CALLBACK(x_menu_about_dialog_callback), NULL);



	
	// Edit Menu items signals connect ::
	g_signal_connect(xeditor->menu->UndoEditItem, "activate",
	                 G_CALLBACK(x_menu_undo_callback), xeditor->scrolled);

	g_signal_connect(xeditor->menu->RedoEditItem, "activate",
	                 G_CALLBACK(x_menu_redo_callback), xeditor->scrolled);
	
	g_signal_connect(xeditor->menu->CutEditItem, "activate",
	                 G_CALLBACK(x_menu_cut_selected_range), xeditor->scrolled);

	g_signal_connect(xeditor->menu->CopyEditItem, "activate",
	                 G_CALLBACK(x_menu_copy_selected_range), xeditor->scrolled);

	g_signal_connect(xeditor->menu->PasteEditEditem, "activate",
	                 G_CALLBACK(x_menu_paste), xeditor->scrolled);

	g_signal_connect(xeditor->menu->SelectAllEditItem, "activate",
	                 G_CALLBACK(x_menu_select_all_callback),
	                 x_scrolled_get_source_buffer (xeditor->scrolled));

	g_signal_connect(xeditor->menu->ClearEditItem, "activate",
	                 G_CALLBACK(x_menu_clear_source_buffer_callback),
	                 x_scrolled_get_source_buffer (xeditor->scrolled));

	g_signal_connect(xeditor->menu->SearchEditItem, "activate",
	                 G_CALLBACK(x_menu_search_callback), xeditor);
	
	g_signal_connect(xeditor->menu->PrefEditItem, "activate",
	                 G_CALLBACK(x_menu_pref_window_callback), xeditor);

	g_signal_connect(xeditor->menu->cViewItem, "activate",
	                 G_CALLBACK(x_menu_view_c_item_callback), xeditor);
	
	g_signal_connect(xeditor->menu->cppViewItem, "activate",
	                 G_CALLBACK(x_menu_view_cpp_item_callback), xeditor);

	g_signal_connect(xeditor->menu->pyViewItem, "activate",
	                 G_CALLBACK(x_menu_view_py_item_callback), xeditor);
	
	g_signal_connect(xeditor->menu->jvViewItem, "activate",
	                 G_CALLBACK(x_menu_view_java_item_callback), xeditor);

	g_signal_connect(xeditor->menu->phpViewItem, "activate",
	                 G_CALLBACK(x_menu_view_php_item_callback), xeditor);
	
	g_signal_connect(xeditor->menu->htmlViewItem, "activate",
	                 G_CALLBACK(x_menu_view_html_item_callback), xeditor);

	                 
	// callbacks for window :: ---------------------------
	g_signal_connect(GTK_TEXT_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled)), "changed",
	                 G_CALLBACK(x_text_buffer_modified_notify_callback), xeditor);

	g_signal_connect(GTK_WIDGET(xeditor->win->window), "delete-event",
	                 G_CALLBACK(x_editor_delete_event_callback), NULL);

	g_signal_connect(GTK_WIDGET(xeditor->win->window), "destroy",
	                 G_CALLBACK(x_editor_destroy_callback), xeditor);

}




// insert everything into de xeditor->win-box :: ---------------------------
void x_editor_pack_all (XEditor * xeditor) {
	gtk_box_pack_start (GTK_BOX(xeditor->win->box), xeditor->menu->MenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(xeditor->win->box), xeditor->toolbar->tBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(xeditor->win->box), xeditor->scrolled->ScrolledWindow, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX(xeditor->win->box), xeditor->statusbar->sBar, FALSE, FALSE, 0);
}




void x_editor_config(XEditor * xeditor) {

	gtk_window_set_opacity (GTK_WINDOW(xeditor->win->window), x_menu_get_scale_value_status (xeditor->menu));
	
	gtk_source_view_set_show_line_numbers (GTK_SOURCE_VIEW(x_scrolled_get_source_view(xeditor->scrolled)),
	                                       x_menu_get_show_line_numbers_status (xeditor->menu));
	
	gtk_source_view_set_auto_indent (GTK_SOURCE_VIEW(x_scrolled_get_source_view (xeditor->scrolled)),
	                                 x_menu_get_auto_ident_status (xeditor->menu));
	
	gtk_source_view_set_indent_width (GTK_SOURCE_VIEW(x_scrolled_get_source_view (xeditor->scrolled)),
	                                  x_menu_get_tab_width (xeditor->menu));

	gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW(x_scrolled_get_source_view (xeditor->scrolled)),
	                                            x_menu_get_highlight_corrent_line_status (xeditor->menu));
	
	gtk_source_buffer_set_highlight_syntax (GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer (xeditor->scrolled)),
	                                        x_menu_get_highlight_status (xeditor->menu));
	
}




// start private data from XEditor class :: ---------------------------
void x_editor_init(XEditor * xeditor) {
	xeditor->private_data = (XEditorPrivate *) g_malloc(sizeof(XEditorPrivate));

#ifdef X_EDITOR_PROGRAM_NAME
	g_set_application_name (X_EDITOR_PROGRAM_NAME);
#endif

#ifdef X_DEFAULT_FILENAME
	/*	xeditor->private_data->filename = g_strdup(X_DEFAULT_FILENAME);*/
	x_editor_set_filename (xeditor, X_DEFAULT_FILENAME);
#else
	/*	xeditor->private_data->filename = NULL;*/
	x_editor_set_filename (xeditor, NULL);
#endif

	/*	xeditor->private_data->save = TRUE;*/
	x_editor_set_save_status (xeditor, TRUE);
	/*	xeditor->private_data->file = NULL;*/
	x_editor_set_file (xeditor, NULL);

	if(SET_EXPORT_HOME < 0){
		g_print("[GTK-EDITORX] WARNING: Error setting environment [!!]\n");
	}
	x_editor_set_search_flag (xeditor, FALSE);
}




gboolean x_editor_splash_delay(gpointer data) {
	GtkWidget * splash = (GtkWidget *)data;
	gtk_widget_hide(splash);
	return FALSE;
}




void x_editor_splash_create_and_show(void) {
	GtkWidget * splash = gtk_window_new (GTK_WINDOW_POPUP);
	GtkWidget * fixed = gtk_fixed_new ();
	GtkWidget * label = gtk_label_new (g_strdup_printf ("Version %s", X_EDITOR_VERSION));
	
	gtk_window_set_position (GTK_WINDOW(splash), GTK_WIN_POS_CENTER);
	gtk_window_set_keep_above (GTK_WINDOW(splash), TRUE);
	GdkPixbuf * image = gdk_pixbuf_new_from_file ("splash/splash.png", NULL);
	if(image == NULL){
		image = gdk_pixbuf_new_from_file ("../splash/splash.png", NULL);
			if(image == NULL){
				image = gdk_pixbuf_new_from_file (X_EDITOR_SPLASH_ADDR, NULL);
			}
	}
	GtkWidget * img = gtk_image_new_from_pixbuf (GDK_PIXBUF(image));
	g_object_unref (image);

	gtk_fixed_put (GTK_FIXED(fixed), img, 4, 4);
	gtk_fixed_put (GTK_FIXED(fixed), label, 50, 90);
	gtk_container_add(GTK_CONTAINER(splash), fixed);

	
	gtk_widget_show_all(splash);
	g_timeout_add(2000, x_editor_splash_delay, splash);
}

// Menu Config accel ::
void x_editor_config_menu (XEditor * xeditor) {
	x_menu_configure_accel (xeditor->menu, xeditor->win);
}

// instanciate XEditor Class :: ---------------------------
XEditor * x_editor_new(void) {	
	XEditor * xeditor = (XEditor *) g_malloc(sizeof(XEditor));
	x_editor_init(xeditor);
	
	xeditor->win = x_window_new ();
	
	xeditor->menu = x_menu_new ();
	x_editor_config_menu (xeditor);
	
	xeditor->toolbar = x_toolbar_new ();
	xeditor->scrolled = x_scrolled_new ();
	x_editor_apply_font_config (xeditor);
	xeditor->statusbar = x_statusbar_new ();
	
	x_editor_config(xeditor);
	
	x_editor_pack_all (xeditor);	

	x_editor_connect_all_signals (xeditor);
	x_editor_splash_create_and_show ();
	
	return xeditor;
}