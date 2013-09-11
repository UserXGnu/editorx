/*
 * statusbar.c
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
#include "definitions.h"
#endif

void x_statusbar_update_callback (GtkTextBuffer * TextBuffer, gpointer data){
	gint row, col;
	GtkTextIter iter;
	GtkTextMark * mark = gtk_text_buffer_get_insert (GTK_TEXT_BUFFER(TextBuffer));

	gtk_statusbar_pop (GTK_STATUSBAR(data), 0);

	gtk_text_buffer_get_iter_at_mark (GTK_TEXT_BUFFER(TextBuffer), &iter, mark);

	row = gtk_text_iter_get_line(&iter);
	col = gtk_text_iter_get_line_offset (&iter);

	gtk_statusbar_push (GTK_STATUSBAR(data), 0, g_strdup_printf("Row: %d Col: %d", row+1, col+1));
}

void x_mark_callback (GtkTextBuffer * TextBuffer, gpointer new, gpointer mark, gpointer data){
	x_statusbar_update_callback (GTK_TEXT_BUFFER(TextBuffer), data);
}


// -------------------------------- CALLBACKS ----------------------------------//


StatusBar * x_statusbar_new (void) {
	StatusBar * statusbar = (StatusBar *) g_malloc(sizeof(StatusBar));

	statusbar->sBar = gtk_statusbar_new ();
	gtk_statusbar_push (GTK_STATUSBAR(statusbar->sBar), 0, "Col: 0  Row: 0");
	
	return statusbar;
}