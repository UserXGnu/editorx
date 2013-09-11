/*
 * scrolled.c
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


// callbacks :: ----------------------------------

void x_text_buffer_modified_notify_callback (GtkTextBuffer * TextBuffer, gpointer data) {
	XEditor * xeditor = (XEditor *)data;

	gchar * title = NULL;
	
	if(*(x_editor_get_save_status (xeditor)) == TRUE){
		x_editor_set_save_status (xeditor, FALSE);
		title = x_window_get_title (xeditor->win);
		title = g_strconcat(title, "*", NULL);
		x_window_set_title(xeditor->win, title);

	}
}




// getters :: ----------------------------------
GtkSourceLanguageManager * x_scrolled_get_language_manager (Scrolled * swindow) {
	return swindow->private_data->lm;
}



GtkSourceLanguage * x_scrolled_get_language (Scrolled * swindow) {
	return swindow->private_data->language;
}



GtkWidget * x_scrolled_get_source_view (Scrolled * swindow) {
	return swindow->private_data->SourceView;
}



GtkSourceBuffer * x_scrolled_get_source_buffer (Scrolled * swindow) {
	return swindow->private_data->SourceBuffer;
}



GtkClipboard * x_scrolled_get_clipboard (Scrolled * swindow) {
	return swindow->private_data->clipboard;
}



PangoFontDescription * x_scrolled_get_font_description (Scrolled * swindow) {
	return swindow->private_data->font_description;
}



gchar * x_scrolled_get_sourcebuffer_content (Scrolled * scrolled) {
	GtkTextIter begin;
	GtkTextIter end;

	gchar * content;

	gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER (x_scrolled_get_source_buffer (scrolled)),
	                                &begin);
	gtk_text_buffer_get_end_iter (GTK_TEXT_BUFFER (x_scrolled_get_source_buffer (scrolled)),
	                                &end);
	content = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(x_scrolled_get_source_buffer (scrolled) ),
	                                    &begin, &end, TRUE);
	return content;
}

gchar * x_scrolled_get_mimetype (Scrolled * swindow) {
	return swindow->private_data->mime_type;
}

gchar * x_scrolled_get_font_name (Scrolled * swindow) {
	gchar * font_name;

	font_name = pango_font_description_to_string (x_scrolled_get_font_description (swindow));
/*	g_print("FontName: %s\n", font_name);*/
	
	return font_name;
}

// Methods :: ----------------------------------

void x_scrolled_set_language_manager (Scrolled * swindow, GtkSourceLanguageManager * lnmg) {
	swindow->private_data->lm = lnmg;
}


void x_scrolled_set_language (Scrolled * swindow, GtkSourceLanguage * lang) {
	swindow->private_data->language = lang;
}


void x_scrolled_set_mimetype (Scrolled * swindow, gchar * mimetype) {
		swindow->private_data->mime_type = g_strdup(mimetype);
}

void x_scrolled_set_font_desc (Scrolled * swindow, PangoFontDescription * font_desc) {
	swindow->private_data->font_description = font_desc;
}


void x_text_view_set_default_font (Scrolled * swindow, gchar * font_desc) {
	if(font_desc == NULL){
		 pango_font_description_set_family (x_scrolled_get_font_description (swindow), "Monospace");
		 pango_font_description_set_size (x_scrolled_get_font_description (swindow),
										9000);
		 gtk_widget_modify_font (GTK_WIDGET(x_scrolled_get_source_view (swindow)),
										x_scrolled_get_font_description (swindow));
	}else{
		
		x_scrolled_set_font_desc (swindow, pango_font_description_from_string (font_desc));
		gtk_widget_modify_font (GTK_WIDGET(x_scrolled_get_source_view (swindow)),
		                        x_scrolled_get_font_description (swindow));
	}
}




// Methods :: -------------------------------------
void x_scrolled_language_self_config(Scrolled * swindow, gchar * filename) {
	GtkSourceLanguage * lang;
	GtkSourceLanguageManager * lm;
	GtkSourceBuffer * sBuff;
	gchar * content_type;
	gboolean try;

	content_type = g_content_type_guess (filename, NULL, 0, &try);
	if(try){
		g_free(content_type);
		content_type = NULL;
	}
	lang = x_scrolled_get_language (swindow);
	lm = x_scrolled_get_language_manager (swindow);
	sBuff = x_scrolled_get_source_buffer (swindow);

	lang = gtk_source_language_manager_guess_language (lm, filename, content_type);
	gtk_source_buffer_set_language (GTK_SOURCE_BUFFER(sBuff), GTK_SOURCE_LANGUAGE(lang));

/*	g_print("Content: %s\n", content_type);*/
	g_free(content_type);
/*	content_type = NULL;*/
}




// start private data from Scrolled class :: -------------------------------------------
void x_scrolled_init (Scrolled * swindow){
	
	swindow->private_data = (ScrolledPrivate *) g_malloc(sizeof(ScrolledPrivate));
	swindow->private_data->font_description = pango_font_description_new ();
	swindow->private_data->clipboard = gtk_clipboard_get (GDK_NONE);

	swindow->private_data->lm = gtk_source_language_manager_new ();
	
	swindow->private_data->SourceBuffer = gtk_source_buffer_new(NULL);
	
	g_object_ref (swindow->private_data->lm);
	g_object_set_data_full (G_OBJECT(x_scrolled_get_source_buffer (swindow)), "language-manager",
	                        swindow->private_data->lm,
	                        (GDestroyNotify)g_object_unref);
	
	swindow->private_data->SourceView = gtk_source_view_new_with_buffer (x_scrolled_get_source_buffer (swindow) );
	
	gtk_source_view_set_indent_on_tab (GTK_SOURCE_VIEW(x_scrolled_get_source_view(swindow)), TRUE);

	x_scrolled_set_language_manager (swindow, g_object_get_data (G_OBJECT(x_scrolled_get_source_buffer (swindow)),
	                                                             "language-manager"));
	x_scrolled_set_language (swindow, gtk_source_language_manager_get_language (GTK_SOURCE_LANGUAGE_MANAGER(x_scrolled_get_language_manager (swindow)),
	                                                                            X_EDITOR_DEFAULT_MIMETYPE));
	gtk_source_buffer_set_language (GTK_SOURCE_BUFFER(x_scrolled_get_source_buffer(swindow)),
	                                GTK_SOURCE_LANGUAGE(x_scrolled_get_language (swindow)));

	
	gtk_text_view_set_left_margin (GTK_TEXT_VIEW(x_scrolled_get_source_view (swindow)), 5);
	gtk_text_view_set_right_margin (GTK_TEXT_VIEW(x_scrolled_get_source_view (swindow)),5);
	
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW(x_scrolled_get_source_view (swindow)),
	                             GTK_WRAP_WORD_CHAR);
}



// instanciate a GtkScrolledWindow and configure scrollbars :: ---------------------------------
GtkWidget * x_scrolled_window_new() {
	GtkWidget * scrolled_window = gtk_scrolled_window_new(NULL, NULL);

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled_window),
	                                GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	return scrolled_window;
}



// instanciate Scrolled class itself :: ---------------------------------------
Scrolled * x_scrolled_new () {
	Scrolled * swindow = (Scrolled *) g_malloc(sizeof(Scrolled));
	x_scrolled_init(swindow);

	swindow->ScrolledWindow = x_scrolled_window_new();
	
/*	x_text_view_set_default_font (swindow);*/
	
	gtk_container_add(GTK_CONTAINER(swindow->ScrolledWindow),
	                  x_scrolled_get_source_view (swindow));

	return swindow;
}