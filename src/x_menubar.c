/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  
*/
/*
 * .
 * Copyright (C) 2013 UserX <userx.gnu@gmail.com>
 *
 * xeditor is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * xeditor is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "definitions.h"

struct _XMenubarPrivate {

    GtkWidget * NewItem;
    GtkWidget * OpenItem;
    GtkWidget * SaveItem;
    GtkWidget * SaveAsItem;
    GtkWidget * ExitItem;

    GtkWidget * UndoItem;
    GtkWidget * RedoItem;
    GtkWidget * CutItem;
    GtkWidget * CopyItem;
    GtkWidget * PasteItem;
    GtkWidget * SelectAllItem;
    GtkWidget * ClearItem;
    GtkWidget * FindReplaceItem;
    GtkWidget * Preferences;

    GtkAccelGroup * accel_g;
};

#define X_MENUBAR_GET_PRIVATE(obj)  (G_TYPE_INSTANCE_GET_PRIVATE((obj), X_TYPE_MENUBAR, XMenubarPrivate))

G_DEFINE_TYPE (XMenubar, x_menubar, GTK_TYPE_MENU_BAR);

static void
x_menubar_bindmenu (XMenubar * self, GtkWidget * MenuItem) 
{
    gtk_menu_shell_append (GTK_MENU_SHELL(X_MENUBAR(self)), MenuItem);
}

static void
x_menubar_menu_new (XMenubar * self, XMenuType type)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE(self);

    GtkWidget * Menu;
    GtkWidget * MenuItem;
    switch (type) {
        case XMenuFile: {
            Menu = gtk_menu_new ();
            gtk_menu_set_accel_group (GTK_MENU (Menu), priv->accel_g);
            MenuItem = gtk_menu_item_new_with_mnemonic ("_File");
            
            priv->NewItem = gtk_menu_item_new_with_mnemonic ("_New");
            //priv->NewItem = gtk_menu_item_new_with_label ("New");
            priv->OpenItem = gtk_menu_item_new_with_label ("Open");
            priv->SaveItem = gtk_menu_item_new_with_label ("Save");
            priv->SaveAsItem = gtk_menu_item_new_with_label ("SaveAs");
            priv->ExitItem = gtk_menu_item_new_with_label ("Quit");

            gtk_menu_item_set_submenu (GTK_MENU_ITEM(MenuItem), Menu);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->NewItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->OpenItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->SaveItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->SaveAsItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), 
                                    gtk_separator_menu_item_new ());
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->ExitItem);

            x_menubar_bindmenu (self, MenuItem);

            break;
        } case XMenuEdit:{

            Menu = gtk_menu_new ();
            MenuItem = gtk_menu_item_new_with_mnemonic ("_Edit");

            priv->UndoItem = gtk_menu_item_new_with_label ("Undo");
            priv->RedoItem = gtk_menu_item_new_with_label ("Redo");
            priv->CutItem = gtk_menu_item_new_with_label ("Cut");
            priv->CopyItem = gtk_menu_item_new_with_label ("Copy");
            priv->PasteItem = gtk_menu_item_new_with_label ("Paste");
            priv->SelectAllItem = gtk_menu_item_new_with_label ("Select All");
            priv->ClearItem = gtk_menu_item_new_with_label ("Clear");
            priv->FindReplaceItem = gtk_menu_item_new_with_label ("Find/Replace");
            priv->Preferences = gtk_menu_item_new_with_label ("Preferences");

        
            gtk_menu_item_set_submenu (GTK_MENU_ITEM(MenuItem), Menu);

            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->UndoItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->RedoItem);

            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), 
                                   gtk_separator_menu_item_new ());

            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->CutItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->CopyItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->PasteItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->SelectAllItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->ClearItem);

            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), 
                                   gtk_separator_menu_item_new ());

            gtk_menu_shell_append (GTK_MENU_SHELL (Menu), priv->FindReplaceItem);

            gtk_menu_shell_append (GTK_MENU_SHELL (Menu), 
                                   gtk_separator_menu_item_new () );

            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->Preferences);
    
            x_menubar_bindmenu  (self, MenuItem);

            break;
        }default: break;
    }
}

static void
x_menubar_init(XMenubar * self)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE(self);

    // Need to add support for shortcut ::
    priv->accel_g = gtk_accel_group_new ();

    x_menubar_menu_new (self, XMenuFile);
    x_menubar_menu_new (self, XMenuEdit);

    g_signal_connect(priv->ExitItem, "activate", G_CALLBACK(gtk_main_quit), NULL);
}

static void
x_menubar_finalize (GObject * object)
{
    G_OBJECT_CLASS(x_menubar_parent_class)->finalize (object);
}

static void
x_menubar_class_init (XMenubarClass * klass)
{
    GObjectClass * object_class = G_OBJECT_CLASS (klass);

    g_type_class_add_private (klass, sizeof (XMenubarPrivate));

    object_class->finalize = x_menubar_finalize;
}

GtkWidget *
x_menubar_new (void)
{
    return GTK_WIDGET(g_object_new (X_TYPE_MENUBAR, NULL));
}




/***********************************************************************************
 ******************************     Callbacks     **********************************
 ***********************************************************************************/


/*
 * **@brief: Callback to create a new tab on the notebook
 * in response to NewItem's signal from menu ::
 */
void 
x_menubar_file_new_callback (GtkWidget * widget, gpointer data)
{
    x_notebook_append (X_NOTEBOOK(data));
}



/* 
 * **@brief: callback to SaveItem and SaveAsItem 
 * that will, obviously save the content on the file ::
 */
void
x_menubar_file_save_callback (GtkWidget * self, gpointer data)
{
    
    info * element;
    XLinkedList * xl;
    XNotebook * note;
    GtkWidget * sView;
    GtkWidget * dialog;
    GtkWidget * tab_label;

    GtkSourceBuffer * sBuffer;
    GtkTextIter begin, end;
    GtkResponseType answer;

    GFile * file;

    const gchar * content;
    const gchar * menuitem_label;
    guint page_pos;

    note = X_NOTEBOOK(data);

    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK(data));

    xl = x_notebook_get_xlinkedlist (X_NOTEBOOK(note));
    element = x_linkedlist_get_element (xl, page_pos);

    if (element == NULL) {
	    return;
    }

    sBuffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (element->sView)));

    gtk_text_buffer_get_bounds (GTK_TEXT_BUFFER (sBuffer),
                                &begin, &end);

    content = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (sBuffer),
                                        &begin, &end,
                                        TRUE);

    //g_print("\n\n%s\n\n", content); ** just for debugging ::
    
    menuitem_label = gtk_menu_item_get_label (GTK_MENU_ITEM (self));

    if ((g_strcmp0 (menuitem_label, "SaveAs") == 0) || ((x_linkedlist_get_element_file_status (element) == FALSE) )) {

        dialog = gtk_file_chooser_dialog_new ("XEditor - Save File Dialog",
                                              NULL,
                                              GTK_FILE_CHOOSER_ACTION_SAVE,
                                              "Cancel" , GTK_RESPONSE_CANCEL,
                                              "Save", GTK_RESPONSE_ACCEPT,
                                              NULL);
        gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
        gtk_file_chooser_set_create_folders (GTK_FILE_CHOOSER (dialog), TRUE);

#ifdef DEFAULT_PATH
        gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), DEFAULT_PATH);
#endif

        answer = gtk_dialog_run (GTK_DIALOG (dialog));

        if (answer == GTK_RESPONSE_ACCEPT) {

            file = gtk_file_chooser_get_file (GTK_FILE_CHOOSER (dialog));

            x_linkedlist_set_element_filepath (element, g_file_get_path (file));
            x_linkedlist_set_element_filename (element, gtk_file_chooser_get_current_name (GTK_FILE_CHOOSER (dialog)));
            
            tab_label = x_linkedlist_get_element_tab_label (xl, page_pos);
            if (tab_label != NULL) {

                gtk_label_set_label (GTK_LABEL(tab_label), x_linkedlist_get_element_filename (xl, NULL, page_pos));

            }

            x_editor_save_current_content (file, content);           
            x_linkedlist_set_element_file_status (element, TRUE);
            x_linkedlist_set_element_save_status (element, FALSE);

        }

        gtk_widget_destroy (dialog);

    } else {


        file = g_file_new_for_path (element->filepath);
        x_editor_save_current_content (file, content);

        x_linkedlist_set_element_file_status (element, TRUE);
        x_linkedlist_set_element_save_status (element, FALSE);

        tab_label = x_linkedlist_get_element_tab_label (xl, page_pos);
        gtk_label_set_label (GTK_LABEL (tab_label), x_linkedlist_get_element_filename (xl, NULL, page_pos));

    }
}


/*
 * **@brief: Just to load the content of selected file through
 * the GtkFileChooser.
 */
void
x_menubar_load_file_callback (GtkWidget * self, gpointer data) 
{
    XNotebook * note;
    XLinkedList * xl;
    info * element;
    GtkWidget * tab_label;
    GtkWidget * dialog;
    GtkSourceBuffer * sBuffer;

    GFile * file;

    GtkResponseType answer;
    guint page_pos;

    gchar * content = NULL;

    dialog = gtk_file_chooser_dialog_new ("XEditor - Load File Dialog -",
                                          NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          "Cancel", GTK_RESPONSE_CANCEL,
                                          "Open", GTK_RESPONSE_ACCEPT,
                                          NULL);
#ifdef DEFAULT_PATH
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), DEFAULT_PATH);
#endif

    answer = gtk_dialog_run (GTK_DIALOG (dialog));

    if (answer == GTK_RESPONSE_ACCEPT) {

        file = gtk_file_chooser_get_file (GTK_FILE_CHOOSER (dialog));
    
        //g_print ("[DEBUG] - 1\n");
        content = x_editor_load_file_content (file);
        //g_print ("\n%s\n", content);

        
        note = X_NOTEBOOK (data);
        xl = x_notebook_get_xlinkedlist (note);

        x_notebook_append (note);
    
        page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK(note));
        element = x_linkedlist_get_element (xl, page_pos);
        

        if (element == NULL) {
            return;
        }

        x_linkedlist_set_element_filepath (element, g_file_get_path (file));
        x_linkedlist_set_element_filename (element, g_file_get_basename (file));
    
        x_linkedlist_set_element_file_status (element, TRUE);
        
        tab_label = x_linkedlist_get_element_tab_label (xl, page_pos);

        if (tab_label != NULL) {

            gtk_label_set_label (GTK_LABEL (tab_label), x_linkedlist_get_element_filename (xl, NULL, page_pos));

        }

        sBuffer = gtk_source_buffer_new (NULL);
        gtk_text_buffer_set_text (GTK_TEXT_BUFFER(sBuffer), content, -1);
        gtk_text_view_set_buffer (GTK_TEXT_VIEW (element->sView), GTK_TEXT_BUFFER (sBuffer));

        g_signal_connect (GTK_TEXT_BUFFER (sBuffer), "changed", 
                          G_CALLBACK (x_notebook_mark_file_as_saved_callback),
                          X_NOTEBOOK(note));

    }

    gtk_widget_destroy (dialog);


}

void
x_menubar_undo_callback (GtkWidget * widget, gpointer data)
{
    GtkSourceView * sView;
    GtkSourceBuffer * sBuffer;
    XNotebook * note;
    XLinkedList * xl;

    guint page_pos;

    note = X_NOTEBOOK (data);
    
    xl = x_notebook_get_xlinkedlist (note);
    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK (note));
    if (page_pos == 0 ) {
    	return;
    }

    sView = GTK_SOURCE_VIEW (x_linkedlist_get_element_sview (xl, page_pos));

    sBuffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (sView)));

    if (gtk_source_buffer_can_undo (GTK_SOURCE_BUFFER (sBuffer)) == TRUE) {

        gtk_source_buffer_undo (GTK_SOURCE_BUFFER (sBuffer));

    }

}

void
x_menubar_redo_callback (GtkWidget * widget, gpointer data)
{

    GtkSourceView * sView;
    GtkSourceBuffer * sBuffer;
    XNotebook * note;
    XLinkedList * xl;

    GtkTextIter end;
    guint page_pos;

    note = X_NOTEBOOK (data);

    xl = x_notebook_get_xlinkedlist (note);

    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK (note));
	if (page_pos == 0) {
		return;
	}
    sView = GTK_SOURCE_VIEW (x_linkedlist_get_element_sview (xl, page_pos));

    sBuffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (sView)));



    if (gtk_source_buffer_can_redo (GTK_SOURCE_BUFFER (sBuffer)) == TRUE) {

        gtk_source_buffer_redo (GTK_SOURCE_BUFFER (sBuffer));
        gtk_text_buffer_get_end_iter (GTK_TEXT_BUFFER (sBuffer), &end);
        gtk_text_buffer_place_cursor (GTK_TEXT_BUFFER (sBuffer), &end);

    }

}


/*
 * **@brief: So, here we go...
 * below we have the callbacks for CutItem, CopyItem, PasteItem and ClearItem  ::
 */
void
x_menubar_cut_callback (GtkWidget * widget, gpointer data )
{

    XNotebook * note;
    XLinkedList * xl;

    GtkWidget * sView;
    GtkSourceBuffer * sBuffer;
    
    GtkTextIter begin;
    GtkTextIter end;

    guint page_pos;

    note = X_NOTEBOOK (data);
    xl = x_notebook_get_xlinkedlist (note);
    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK (note));

    sView = x_linkedlist_get_element_sview (xl, page_pos);

    sBuffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (sView)));

    gtk_text_buffer_cut_clipboard (GTK_TEXT_BUFFER (sBuffer), GTK_CLIPBOARD (x_notebook_get_clipboard (note)), TRUE);
    
}

void
x_menubar_copy_callback (GtkWidget * widget, gpointer data)
{

    XNotebook * note;
    XLinkedList * xl;
    
    GtkWidget * sView;
    GtkSourceBuffer * sBuffer;
    guint page_pos;

    note = X_NOTEBOOK (data);
    xl = x_notebook_get_xlinkedlist (note);

    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK (note));

    sView = x_linkedlist_get_element_sview (xl, page_pos);
    sBuffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (sView)));

    gtk_text_buffer_copy_clipboard (GTK_TEXT_BUFFER (sBuffer), x_notebook_get_clipboard (note));

}

void
x_menubar_paste_callback (GtkWidget * widget, gpointer data)
{

    XNotebook * note;
    XLinkedList * xl;

    GtkSourceView * sView;
    GtkSourceBuffer * sBuffer;

    guint page_pos;


    note = X_NOTEBOOK (data);
    xl = x_notebook_get_xlinkedlist (note);
    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK (note));

    sView = GTK_SOURCE_VIEW (x_linkedlist_get_element_sview (xl, page_pos));
    sBuffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW(sView)));

    gtk_text_buffer_paste_clipboard (GTK_TEXT_BUFFER (sBuffer), x_notebook_get_clipboard (note),
                                     NULL, TRUE);

}

void
x_menubar_selectall_callback (GtkWidget * widget, gpointer data)
{
    XNotebook * note;
    XLinkedList * xl;

    GtkSourceView * sView;
    GtkSourceBuffer * sBuffer;
    
    GtkTextIter begin;
    GtkTextIter end;
    
    guint page_pos;

    note = X_NOTEBOOK (data);
    xl = x_notebook_get_xlinkedlist (note);

    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK (note));

    sView = GTK_SOURCE_VIEW (x_linkedlist_get_element_sview (xl, page_pos));

    sBuffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (sView)));

    gtk_text_buffer_get_bounds (GTK_TEXT_BUFFER (sBuffer), &begin, &end);

    gtk_text_buffer_select_range (GTK_TEXT_BUFFER (sBuffer), &begin, &end);

}

void
x_menubar_clear_callback (GtkWidget * widget, gpointer data)
{
    XNotebook * note;
    XLinkedList * xl;

    GtkSourceView * sView;
    GtkSourceBuffer * sBuffer;

    guint page_pos;

    note = X_NOTEBOOK (data);
    xl = x_notebook_get_xlinkedlist (note);

    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK (note));

    sView = GTK_SOURCE_VIEW (x_linkedlist_get_element_sview (xl, page_pos));

    sBuffer = GTK_SOURCE_BUFFER (gtk_text_view_get_buffer (GTK_TEXT_VIEW (sView)));

    gtk_text_buffer_set_text (GTK_TEXT_BUFFER (sBuffer), "", 0);
}

/***********************************************************************************
 *******************************     methods     ***********************************
 ***********************************************************************************/
void
x_menubar_connect_newitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE(self);

    //g_print("[DEBUG] - 1\n ");
    g_signal_connect(priv->NewItem, "activate", 
			G_CALLBACK (x_menubar_file_new_callback), widget);
}


/*
 * SaveItem and SaveAsItem will have its signals connected to respective callbacks
 * here ::
 */
void
x_menubar_connect_saveitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->SaveItem, "activate", 
			G_CALLBACK (x_menubar_file_save_callback), widget);

    g_signal_connect (priv->SaveAsItem, "activate", 
            G_CALLBACK (x_menubar_file_save_callback), widget);
}

/*
 * OpenItem is just an item from Menu to open a new file, as you can see,
 * this method will connect that item with an apropriated callback
 * to open a new file content ::
 */
void
x_menubar_connect_openitem_signal (XMenubar * self, GtkWidget * widget)
{
    
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->OpenItem, "activate",
            G_CALLBACK (x_menubar_load_file_callback), widget);
}

/*
 * Undo and Redo itens are obvious enough, so I think that I don't need
 * to explain that :: =D
 */
void
x_menubar_connect_undoitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->UndoItem, "activate", 
            G_CALLBACK (x_menubar_undo_callback), widget);
                    
}



void
x_menubar_connect_redoitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->RedoItem, "activate",
            G_CALLBACK (x_menubar_redo_callback), widget);
}


void
x_menubar_connect_cutitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->CutItem, "activate",
            G_CALLBACK (x_menubar_cut_callback), widget);
}

void
x_menubar_connect_copyitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->CopyItem, "activate",
            G_CALLBACK (x_menubar_copy_callback), widget);

}


void
x_menubar_connect_pasteitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->PasteItem, "activate",
            G_CALLBACK (x_menubar_paste_callback), widget);
}

void
x_menubar_connect_selectallitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->SelectAllItem, "activate", 
            G_CALLBACK (x_menubar_selectall_callback), widget);
}

void
x_menubar_connect_clearitem_signal (XMenubar * self, GtkWidget * widget)
{

    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->ClearItem, "activate",
            G_CALLBACK (x_menubar_clear_callback), widget);

}
