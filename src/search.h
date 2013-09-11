/*
 * search.h
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
#ifndef _SEARCH_H
#define _SEARCH_H

typedef struct _search {
	GtkWidget * box,
			  * s_entry,
			  * r_entry,
			  * s_button,
			  * n_button,
			  * r_button,
			  * rn_button,
			  * e_button;
	
	gboolean * searchflg;
	GtkWidget * SourceView;
}search_app;


// callbacks ::
void x_replace_all_button_clicked (GtkWidget *, gpointer);
void x_replace_button_clicked (GtkWidget *, gpointer);
void x_search_button_clicked (GtkWidget *, gpointer);
void x_search_next_button_clicked (GtkWidget *, gpointer);
void x_search_destroy (GtkWidget *, gpointer);

// common method ::
void x_search_default_search (GtkTextView *, const gchar *, GtkTextIter *);

// getters ::
GtkWidget * x_search_get_entry (search_app *) G_GNUC_CONST;
GtkWidget * x_search_get_source_view (search_app *) G_GNUC_CONST;

// constructor :: ---------------
search_app * x_editor_search_new(XEditor *) G_GNUC_CONST;

#endif /* _SEARCH_H */