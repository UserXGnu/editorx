/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * x_window.c
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

struct _XWindowPrivate
{
	GtkWidget * Box;

    GtkWidget * xMenubar;
    GtkWidget * xNotebook;
};


#define X_WINDOW_GET_PRIVATE(obj)    (G_TYPE_INSTANCE_GET_PRIVATE ((obj), X_TYPE_WINDOW, XWindowPrivate))


G_DEFINE_TYPE (XWindow, x_window, GTK_TYPE_WINDOW);

static void
x_window_init (XWindow * self)
{
    XWindowPrivate * priv = X_WINDOW_GET_PRIVATE (self);
    
    gtk_window_set_default_size(GTK_WINDOW(self), 640, 480);
    gtk_window_set_title (GTK_WINDOW(self), "Default Title");
    gtk_window_set_type_hint (GTK_WINDOW(self), GDK_WINDOW_TYPE_HINT_NORMAL);
    gtk_window_set_position (GTK_WINDOW(self), GTK_WIN_POS_CENTER);

    priv->Box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

    priv->xMenubar = x_menubar_new ();
    priv->xNotebook = x_notebook_new ();

    gtk_box_pack_start (GTK_BOX(priv->Box), priv->xMenubar, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(priv->Box), priv->xNotebook, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(self), priv->Box);

    g_signal_connect(self, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

static void
x_window_finalize (GObject *object)
{


	G_OBJECT_CLASS (x_window_parent_class)->finalize (object);
}

static void
x_window_class_init (XWindowClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (XWindowPrivate));

	object_class->finalize = x_window_finalize;
}


GtkWidget *
x_window_new (void)
{
	return GTK_WIDGET(g_object_new(X_TYPE_WINDOW, NULL));
}


/*
 * getters ::
 */
GtkWidget *
x_window_get_menubar (XWindow * self) 
{
    XWindowPrivate * priv = X_WINDOW_GET_PRIVATE(self);

    return priv->xMenubar;
}

GtkWidget * 
x_window_get_notebook (XWindow * self)
{
    XWindowPrivate * priv = X_WINDOW_GET_PRIVATE(self);

    return priv->xNotebook;
}
