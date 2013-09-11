/* teste
 * scrolled.h
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
#ifndef _SCROLLED_H
#define _SCROLLED_H

typedef struct _scrolledprivate ScrolledPrivate;
struct _scrolledprivate {
	GtkWidget * SourceView;
	GtkSourceBuffer * SourceBuffer;
	
	GtkSourceLanguageManager * lm;
	GtkSourceLanguage * language;
	
	GtkClipboard * clipboard;
	PangoFontDescription * font_description;

	gchar * mime_type;
};

typedef struct _scrolled Scrolled;
struct _scrolled {
	GtkWidget * ScrolledWindow;
	
	ScrolledPrivate * private_data;
};
// callbacks :: --------------------------
void x_text_buffer_modified_notify_callback(GtkTextBuffer *, gpointer);


// Getters :: ----------------
GtkSourceLanguageManager * x_scrolled_get_language_manager (Scrolled *) G_GNUC_CONST;
GtkSourceLanguage * x_scrolled_get_language (Scrolled *) G_GNUC_CONST;
GtkWidget * x_scrolled_get_source_view (Scrolled *) G_GNUC_CONST;
GtkSourceBuffer * x_scrolled_get_source_buffer (Scrolled *) G_GNUC_CONST;
GtkClipboard * x_scrolled_get_clipboard (Scrolled *) G_GNUC_CONST;
PangoFontDescription * x_scrolled_get_font_description (Scrolled *) G_GNUC_CONST;
gchar * x_scrolled_get_sourcebuffer_content (Scrolled *) G_GNUC_CONST;
gchar * x_scrolled_get_mimetype (Scrolled *) G_GNUC_CONST;
gchar * x_scrolled_get_font_name (Scrolled *) G_GNUC_CONST;

// setters :: -----------------------
void x_text_view_set_default_font (Scrolled *, gchar *);
void x_scrolled_set_language_manager (Scrolled *, GtkSourceLanguageManager *);
void x_scrolled_set_language (Scrolled *, GtkSourceLanguage *);
void x_scrolled_set_mimetype (Scrolled *, gchar * mimetype);
void x_scrolled_set_font_desc (Scrolled *, PangoFontDescription *);


// methods :: ------------------------
void x_scrolled_language_self_config (Scrolled *, gchar *);

// constructors :: -----
void x_scrolled_init(Scrolled *);
GtkWidget * x_scrolled_window_new() G_GNUC_CONST;
Scrolled * x_scrolled_new(void) G_GNUC_CONST;

#endif /* _SCROLLED_H */