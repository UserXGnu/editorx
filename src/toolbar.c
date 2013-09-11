/*
 * toolbar.c
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

void x_font_select_callback (GtkWidget * widget, gpointer data) {
	XEditor * xeditor = (XEditor *)data;
	GtkResponseType answer;
	PangoFontDescription * font_desc;
	GtkWidget * dialog = gtk_font_chooser_dialog_new ("- EditroX - Font Selector -", GTK_WINDOW(xeditor->win->window));

	gtk_font_chooser_set_preview_text (GTK_FONT_CHOOSER(dialog), "EditorX is the best text editor than ever.");
	answer = gtk_dialog_run(GTK_DIALOG(dialog));
	
	if(answer == GTK_RESPONSE_OK) {
		font_desc = gtk_font_chooser_get_font_desc (GTK_FONT_CHOOSER(dialog));
		x_scrolled_set_font_desc (xeditor->scrolled, font_desc);
		gtk_widget_override_font (GTK_WIDGET(x_scrolled_get_source_view (xeditor->scrolled)),
		                        x_scrolled_get_font_description (xeditor->scrolled));
		x_toolbar_set_font_desc (xeditor->toolbar,
		                         pango_font_description_to_string (x_scrolled_get_font_description (xeditor->scrolled)));
		
	}
	gtk_widget_destroy(dialog);
}


// ----------------------------------------- Callbacks ------------------------------------------- //


// getters ::
gchar * x_toolbar_get_font_desc (ToolBar * toolbar) {
	return toolbar->private_data->font_desc;
}

// setters ::
void x_toolbar_set_font_desc (ToolBar * toolbar, gchar * font) {
	toolbar->private_data->font_desc = font;
}

gboolean x_toolbar_load_font_config (ToolBar * toolbar) {
	GError * err = NULL;
	gchar * path;
	gchar * font_desc;
	path = g_strconcat (X_USER_DEFAULT_PATH, X_EDITOR_FONT_CONFIG_FILE, NULL);

	if((g_file_get_contents (path, &font_desc, NULL, &err)) == FALSE) {
		return FALSE;
	}else{
		x_toolbar_set_font_desc (toolbar, g_strdup(font_desc));
/*		g_print("[DEBUG]: FontDescStr: %s\n", x_toolbar_get_font_desc(toolbar));*/
		return TRUE;
	}
}

void x_toolbar_init(ToolBar * toolbar) {
	toolbar->private_data = (ToolBarPrivate *) g_malloc(sizeof(ToolBarPrivate));
	if((x_toolbar_load_font_config (toolbar)) == FALSE){
		x_toolbar_set_font_desc (toolbar, NULL);
	}
	
}

ToolBar * x_toolbar_new(void) {
	ToolBar * toolbar = (ToolBar *) g_malloc(sizeof(ToolBar));
	x_toolbar_init(toolbar);
	toolbar->tBar = gtk_toolbar_new ();

	toolbar->SaveItem = gtk_tool_button_new_from_stock (GTK_STOCK_SAVE);
	toolbar->OpenItem = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);

	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->SaveItem), "Save buffer");
	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->OpenItem), "load some file contents");
	
	toolbar->FirstSeparatorItem = gtk_separator_tool_item_new ();
	
	toolbar->CutItem = gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
	toolbar->CopyItem = gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
	toolbar->PasteItem = gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	toolbar->SelectAllItem = gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_ALL);

	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->CutItem), "Cut selected bounds to clipboard");
	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->CopyItem), "Copy selected bounds to clipboard");
	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->PasteItem), "Paste from clipboard");
	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->SelectAllItem), "Select all (From start to end)");
	
	toolbar->SecondSeparatorItem = gtk_separator_tool_item_new ();

	toolbar->UndoItem = gtk_tool_button_new_from_stock (GTK_STOCK_UNDO);
	toolbar->RedoItem = gtk_tool_button_new_from_stock (GTK_STOCK_REDO);

	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->UndoItem), "Undo");
	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->RedoItem), "Redo");
	
	toolbar->ThirdSeparatorItem = gtk_separator_tool_item_new ();

	toolbar->FontSelectItem = gtk_tool_button_new_from_stock (GTK_STOCK_SELECT_FONT);
	toolbar->SearchItem = gtk_tool_button_new_from_stock (GTK_STOCK_FIND_AND_REPLACE);

	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->FontSelectItem), "Font selector dialog");
	gtk_widget_set_tooltip_text (GTK_WIDGET(toolbar->SearchItem), "Search something into buffer");


	x_toolbar_boxing (toolbar);

	x_toolbar_init(toolbar);
	
	return toolbar;
}

void x_toolbar_boxing (ToolBar * toolbar){
	
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->SaveItem, -1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->OpenItem, -1);
	
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->FirstSeparatorItem, -1);
	
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->CutItem, -1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->CopyItem, -1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->PasteItem, -1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->SelectAllItem, -1);

	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->UndoItem, -1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->RedoItem, -1);
	
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->ThirdSeparatorItem, -1);

	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->SearchItem, -1);
	gtk_toolbar_insert (GTK_TOOLBAR(toolbar->tBar), toolbar->FontSelectItem, -1);
	
	
}