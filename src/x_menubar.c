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
            MenuItem = gtk_menu_item_new_with_mnemonic ("_File");
            
            priv->NewItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, priv->accel_g);
            priv->OpenItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, priv->accel_g);
            priv->SaveItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE, priv->accel_g);
            priv->SaveAsItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE_AS, priv->accel_g);
            priv->ExitItem = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, priv->accel_g);

            gtk_menu_item_set_submenu (GTK_MENU_ITEM(MenuItem), Menu);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->NewItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->OpenItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->SaveItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->SaveAsItem);
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), gtk_separator_menu_item_new ());
            gtk_menu_shell_append (GTK_MENU_SHELL(Menu), priv->ExitItem);

            x_menubar_bindmenu (self, MenuItem);

            break;
        }default: break;
    }
}

static void
x_menubar_init(XMenubar * self)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE(self);

    priv->accel_g = gtk_accel_group_new ();

    x_menubar_menu_new (self, XMenuFile); 

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
void
x_menubar_file_new_callback (GtkWidget * widget, gpointer data)
{
    x_notebook_append (X_NOTEBOOK(data));
}


void
x_menubar_file_save_callback (GtkWidget * self, gpointer data)
{
    
    info * element;
    XLinkedList * xl;
    XNotebook * note;
    GtkWidget * tView;

    GtkTextBuffer * tBuffer;
    GtkTextIter begin, end;

    gchar * content;
    guint page_pos;

    note = X_NOTEBOOK(data);

    page_pos = gtk_notebook_get_current_page (GTK_NOTEBOOK(data));

    xl = x_notebook_get_xlinkedlist (X_NOTEBOOK(note));
    element = x_linkedlist_get_element (xl, page_pos);

    if (element == NULL) {
	return;
    }
    tBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(element->tView));

    gtk_text_buffer_get_bounds (GTK_TEXT_BUFFER(tBuffer),
				&begin, &end);
    content = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(tBuffer), &begin, &end, TRUE);

    g_print("\n\n%s\n\n", content);
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

void
x_menubar_connect_saveitem_signal (XMenubar * self, GtkWidget * widget)
{
    XMenubarPrivate * priv = X_MENUBAR_GET_PRIVATE (self);

    g_signal_connect (priv->SaveItem, "activate", 
			G_CALLBACK (x_menubar_file_save_callback), widget);
}
