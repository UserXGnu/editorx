/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  
*/
/*
 * x_notebook.c
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
#include "x_notebook.h"
#include "x_linkedlist.h"
#include "definitions.h"

struct _XNotebookPrivate {

    GtkWidget * new_btn;
    XLinkedList xl;

};



#define X_NOTEBOOK_GET_PRIVATE(obj)     (G_TYPE_INSTANCE_GET_PRIVATE((obj), X_TYPE_NOTEBOOK, XNotebookPrivate))



G_DEFINE_TYPE (XNotebook, x_notebook, GTK_TYPE_NOTEBOOK);


/*
 * **@brief: It will create a new tab to XNotebook, 
 * with a GtkButton included wich will serve to create 
 * another tabs ::
 */
static void
x_notebook_nbtn_create(XNotebook * self)
{
    XNotebookPrivate * priv = X_NOTEBOOK_GET_PRIVATE(self);

    /*
     * **@brief: GtkWidget's that will used to create a new tab button
     * handler::
     */
    GtkWidget * label;
    GtkWidget * image;
    GtkWidget * parent;

    image = gtk_image_new_from_stock (GTK_STOCK_NEW, GTK_ICON_SIZE_MENU);
    priv->new_btn = gtk_button_new ();
    gtk_button_set_image (GTK_BUTTON(priv->new_btn), image);
    gtk_button_set_relief(GTK_BUTTON(priv->new_btn), GTK_RELIEF_NONE);

    gtk_widget_set_vexpand (priv->new_btn, TRUE);
    
    label = gtk_label_new (NULL);

    gtk_notebook_append_page (GTK_NOTEBOOK(self), label, priv->new_btn);

    parent = gtk_widget_get_parent (GTK_WIDGET(priv->new_btn));

    gtk_widget_set_can_focus (GTK_WIDGET(parent), FALSE);

    g_signal_connect (priv->new_btn, "clicked",
                      G_CALLBACK (x_notebook_nbtn_callback), self);
    
}


/*
 * **@brief: XNotebook class is a child class from GtkNotebook, but
 * it will contain some implementation about close buttons into
 * every tab and a specific button to add another tabs ::
 */
static void
x_notebook_init (XNotebook * self)
{
    XNotebookPrivate * priv = X_NOTEBOOK_GET_PRIVATE(self);

    x_notebook_nbtn_create(self);
    x_linkedlist_init (&(priv->xl));

    gtk_widget_show_all (GTK_WIDGET(self));

}

/*
 * **@brief: Destructor ::
 */
static void
x_notebook_finalize (GObject * object)
{
    XNotebookPrivate * priv = X_NOTEBOOK_GET_PRIVATE(X_NOTEBOOK(object));

    x_linkedlist_finalize (&(priv->xl));
    G_OBJECT_CLASS  (x_notebook_parent_class)->finalize (object);
}

/*
 * **@brief: It gets the class inheritance and implementation
 * of the private data ::
 */
static void
x_notebook_class_init (XNotebookClass * klass)
{
    GObjectClass * object_class = G_OBJECT_CLASS(klass);
    GtkNotebookClass * parent_class = GTK_NOTEBOOK_CLASS(klass);

    g_type_class_add_private (klass, sizeof (XNotebookPrivate));

    object_class->finalize = x_notebook_finalize;

}


/*
 * **@brief: Constructor that will class <x_notebook_init(XNotebook * self)>
 * which will truly construct an instance object ::
 */
GtkWidget *
x_notebook_new (void)
{
    GTK_WIDGET(g_object_new (X_TYPE_NOTEBOOK, NULL));
}










/**********************************************************************************/
/*************************         CALLBACKS         ******************************/
/**********************************************************************************/


/*
 * **@brief: after new_btn to emit "clicked" signal, it will
 * be called to create a new tab to XNotebook object, which
 * will append this into it ::
 */
void
x_notebook_nbtn_callback (GtkWidget * widget, gpointer data)
{

    x_notebook_append (X_NOTEBOOK (data));

}


/*
 * **@brief: After close_button to emit "clicked" detailed signal,
 * this callback will be called to remove the tab which close_button is
 * inside of ::
 */
void
x_notebook_remove_tab_callback (GtkWidget * widget, gpointer data)
{
    XNotebookPrivate * priv = X_NOTEBOOK_GET_PRIVATE(X_NOTEBOOK(data));

    info * element;
    guint page_pos;
 
    page_pos = x_button_get_page_pos (X_BUTTON(widget));
    element = x_linkedlist_get_element (&(priv->xl), page_pos);

    /*
     * **@brief: Removing tab from the XNotebook, from the
     * XLinkedlist and reordanating elements ::
     */
    x_linkedlist_remove (&(priv->xl), element);

    gtk_notebook_remove_page(GTK_NOTEBOOK(data), page_pos);
    x_notebook_refresh (X_NOTEBOOK(data));

}











/*********************************************************************************/
/****************************       METHODS       ********************************/
/*********************************************************************************/

// getters ::
XLinkedList *
x_notebook_get_xlinkedlist (XNotebook * self)
{
    XNotebookPrivate * priv = X_NOTEBOOK_GET_PRIVATE (self);

    return &(priv->xl);
}
/*
 * **@brief: A simple method to append a new tab to XNotebook ::
 */
void
x_notebook_append (XNotebook * self)
{
    XNotebookPrivate * priv = X_NOTEBOOK_GET_PRIVATE (self);

    guint page_pos;
    guint i;

    info * element = (info *) g_malloc (sizeof (info));
    GtkWidget * box;
    GtkWidget * tab_label;
    GtkWidget * stock_img;
    GtkWidget * close_button; // It will be a XButton instance object ::
    GtkWidget * scrolled;
    GtkWidget * tView;


    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);

    tab_label = gtk_label_new (g_strdup_printf("Tab: %d",
                x_linkedlist_get_length (&(priv->xl))));

    stock_img = gtk_image_new_from_stock (GTK_STOCK_CLOSE, GTK_ICON_SIZE_MENU);
    close_button = x_button_new ();
    x_button_set_page_pos (X_BUTTON(close_button),
                           x_linkedlist_get_length (&(priv->xl)));
    gtk_button_set_image (GTK_BUTTON (close_button), stock_img);
    gtk_button_set_relief (GTK_BUTTON (close_button), GTK_RELIEF_NONE);

    element->button = GTK_WIDGET(close_button);

    x_linkedlist_insert (&(priv->xl), element);

    gtk_box_pack_start (GTK_BOX(box), tab_label, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(box), close_button, TRUE, TRUE, 0);

    gtk_widget_show_all (box);

    scrolled = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrolled),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    tView = gtk_text_view_new ();

    gtk_container_add (GTK_CONTAINER (scrolled), tView);
    gtk_widget_show_all (scrolled);

    gtk_notebook_append_page (GTK_NOTEBOOK(self), scrolled, box);

    element->tView = tView;
    x_notebook_refresh (X_NOTEBOOK(self));

    page_pos = x_linkedlist_get_length (&(priv->xl));
    
    for (i = 1; i <= page_pos; i++) {
        gtk_notebook_next_page (GTK_NOTEBOOK(self));
    }

    g_signal_connect(close_button, "clicked",
                    G_CALLBACK(x_notebook_remove_tab_callback),
                    self);
}

/*
 * **@brief: It will refresh XNotebook on the screen
 * to update it's status ::
 */
void
x_notebook_refresh (XNotebook * self)
{
    gtk_widget_hide (GTK_WIDGET(self));
    gtk_widget_show_all (GTK_WIDGET(self));
}

