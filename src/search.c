/*
 * search.c
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
// replace ALL callback ::
void x_replace_all_button_clicked (GtkWidget * widget, gpointer data) {
	search_app * search = (search_app *)data;
	GtkTextIter begin,
				end;
	gboolean try;
	const gchar * content;
	GtkTextView * tView = GTK_TEXT_VIEW(search->SourceView);
	GtkTextBuffer * tBuff = gtk_text_view_get_buffer (GTK_TEXT_VIEW(tView));
	try = TRUE;
	while(try != FALSE){
		g_signal_emit_by_name (search->s_button, "clicked");
		try = gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER(tBuff), &begin, &end);
		if(try == TRUE) {
			gtk_text_buffer_place_cursor (GTK_TEXT_BUFFER(tBuff), &begin);
			content = gtk_entry_get_text(GTK_ENTRY(search->r_entry));
			gtk_text_buffer_delete(GTK_TEXT_BUFFER(tBuff), &begin, &end);
			gtk_text_buffer_insert (GTK_TEXT_BUFFER(tBuff), &begin, content, strlen(content));
		}
	}
}




// replace callback ::
void x_replace_button_clicked (GtkWidget * widget, gpointer data) {
	search_app * search = (search_app *)data;
	GtkTextIter begin,
				end;
	gboolean try;
	const gchar * content;
	GtkTextView * tView = GTK_TEXT_VIEW(search->SourceView);
	GtkTextBuffer * tBuff = gtk_text_view_get_buffer (GTK_TEXT_VIEW(tView));

	g_signal_emit_by_name (search->s_button, "clicked");
	try = gtk_text_buffer_get_selection_bounds (GTK_TEXT_BUFFER(tBuff), &begin, &end);
	if(try == TRUE) {
		gtk_text_buffer_place_cursor (GTK_TEXT_BUFFER(tBuff), &begin);
		content = gtk_entry_get_text(GTK_ENTRY(search->r_entry));
		gtk_text_buffer_delete(GTK_TEXT_BUFFER(tBuff), &begin, &end);
		gtk_text_buffer_insert (GTK_TEXT_BUFFER(tBuff), &begin, content, strlen(content));
	}
	
}


// keep looking for ::
void x_search_next_button_clicked (GtkWidget * widget, gpointer data) {
	search_app * search = (search_app *)data;

	GtkTextBuffer * tBuff;
	GtkTextIter iter;
	GtkTextMark * last_position;
	const gchar * text;

	text = gtk_entry_get_text(GTK_ENTRY(search->s_entry));
	tBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(search->SourceView));

	gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(tBuff), &iter);
	last_position = gtk_text_buffer_get_mark (GTK_TEXT_BUFFER(tBuff), "last-pos");

	if(last_position == NULL){
		return;
	}else{
		gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER(tBuff), &iter, last_position);
		x_search_default_search (GTK_TEXT_VIEW(search->SourceView), text, &iter);
	}
	
}



// search for typed string into TextBuffer's content ::
void x_search_button_clicked (GtkWidget * widget, gpointer data) {
	search_app * search = (search_app *)data;

	const gchar * text;
	GtkTextBuffer * tBuff;
	GtkTextIter iter;

	text = gtk_entry_get_text(GTK_ENTRY(search->s_entry));

	tBuff = gtk_text_view_get_buffer (GTK_TEXT_VIEW(search->SourceView));

	gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER(tBuff), &iter);

	x_search_default_search (GTK_TEXT_VIEW(search->SourceView), text, &iter);
}



// Common Methods ::
void x_search_default_search (GtkTextView * tView, const gchar * text, GtkTextIter * iter){
	GtkTextIter begin,
				end;
	GtkTextBuffer * tBuff;
	gboolean found;

	tBuff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tView));
	found = gtk_text_iter_forward_search (iter, text, GTK_TEXT_SEARCH_VISIBLE_ONLY,
	                                      &begin, &end, NULL);
	if(found == TRUE){
		gtk_text_buffer_select_range (GTK_TEXT_BUFFER(tBuff), &begin, &end);
		gtk_text_buffer_create_mark (GTK_TEXT_BUFFER(tBuff), "last-pos", &end, FALSE);
		gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(tView), &begin, FALSE, FALSE, 0, 0);
	}
}

// destructor ::
void x_search_destroy (GtkWidget * widget, gpointer data) {
	search_app * search = (search_app *)data;
	*search->searchflg = FALSE; 
	gtk_widget_destroy(GTK_WIDGET(search->box));
	g_free(search);
}


// Getters ::
GtkWidget * x_search_get_entry (search_app * search) {
	return search->s_entry;
}

GtkWidget * x_search_get_source_view (search_app * search) {
	return search->SourceView;
}



// constructor :: -------------------
search_app * x_editor_search_new(XEditor * xeditor) {
	if((x_editor_get_search_flag_status (xeditor)) == FALSE) {
		search_app * search = (search_app *) g_malloc(sizeof(search_app));
		
		GtkWidget * s_label;
		GtkWidget * r_label;
		
		search->searchflg = x_editor_get_search_flag (xeditor);
		search->s_entry = gtk_entry_new ();
		search->r_entry = gtk_entry_new ();

		gtk_widget_set_tooltip_text (GTK_WIDGET(search->s_entry), "string to find");
		gtk_widget_set_tooltip_text (GTK_WIDGET(search->r_entry), "string used to replace");
		
		GtkWidget * image[5];

		image[0] = gtk_image_new_from_stock (GTK_STOCK_FIND, 2);
		image[1] = gtk_image_new_from_stock (GTK_STOCK_GO_FORWARD, 2);
		image[2] = gtk_image_new_from_stock (GTK_STOCK_CLOSE, 2);
		image[3] = gtk_image_new_from_stock (GTK_STOCK_FIND_AND_REPLACE, 2);
		image[4] = gtk_image_new_from_stock (GTK_STOCK_GOTO_LAST, 2);
		
		search->s_button = gtk_button_new ();
		search->n_button = gtk_button_new ();
		search->r_button = gtk_button_new ();
		search->rn_button = gtk_button_new ();
		search->e_button = gtk_button_new ();

		gtk_widget_set_tooltip_text (GTK_WIDGET(search->s_button), "search");
		gtk_widget_set_tooltip_text (GTK_WIDGET(search->n_button), "next");
		gtk_widget_set_tooltip_text (GTK_WIDGET(search->r_button), "replace with ...");
		gtk_widget_set_tooltip_text (GTK_WIDGET(search->rn_button), "replace all with ...");
		gtk_widget_set_tooltip_text (GTK_WIDGET(search->e_button), "close");

		gtk_button_set_image (GTK_BUTTON(search->s_button), image[0]);
		gtk_button_set_image (GTK_BUTTON(search->n_button), image[1]);
		gtk_button_set_image (GTK_BUTTON(search->e_button), image[2]);
		gtk_button_set_image (GTK_BUTTON(search->r_button), image[3]);
		gtk_button_set_image (GTK_BUTTON(search->rn_button), image[4]);

		search->SourceView = GTK_WIDGET(x_scrolled_get_source_view (xeditor->scrolled) );

		search->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		s_label = gtk_label_new ("Search");
		r_label = gtk_label_new ("Replace with");
		
		gtk_box_pack_start (GTK_BOX(search->box), s_label, FALSE, FALSE, 1);
		gtk_box_pack_start (GTK_BOX(search->box), search->s_entry, FALSE, FALSE, 1);
		gtk_box_pack_start (GTK_BOX(search->box), search->s_button, FALSE, FALSE, 1);
		gtk_box_pack_start (GTK_BOX(search->box), search->n_button, FALSE, FALSE, 1);
		gtk_box_pack_start (GTK_BOX(search->box), r_label, FALSE, FALSE, 1);
		gtk_box_pack_start (GTK_BOX(search->box), search->r_entry, FALSE, FALSE, 1);
		gtk_box_pack_start (GTK_BOX(search->box), search->r_button, FALSE, FALSE, 1);
		gtk_box_pack_start (GTK_BOX(search->box), search->rn_button, FALSE, FALSE, 1);
		gtk_box_pack_end (GTK_BOX(search->box), search->e_button, FALSE, FALSE, 0);
		
		gtk_widget_show_all(search->box);

		gtk_widget_set_can_default (GTK_WIDGET(search->s_button), TRUE);
		gtk_window_set_default (GTK_WINDOW(xeditor->win->window), search->s_button);

		
		g_signal_connect(search->s_button, "clicked", G_CALLBACK(x_search_button_clicked), search);
		g_signal_connect(search->n_button, "clicked", G_CALLBACK(x_search_next_button_clicked), search);
		g_signal_connect(search->r_button, "clicked", G_CALLBACK(x_replace_button_clicked), search);
		g_signal_connect(search->rn_button, "clicked", G_CALLBACK(x_replace_all_button_clicked), search);
		g_signal_connect(search->e_button, "clicked", G_CALLBACK(x_search_destroy), search);
		
		x_editor_set_search_flag (xeditor, TRUE);

		return search;
	}
	return NULL;
}