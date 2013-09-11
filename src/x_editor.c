/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * x_editor.c
 * Copyright (C) 2013 UserX <userx@AdventChildren>
 *
 * teste is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * teste is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "x_editor.h"
#include "definitions.h"

struct _XEditorPrivate
{
    GtkWidget * xWindow;
    
};


#define X_EDITOR_GET_PRIVATE(obj)       (G_TYPE_INSTANCE_GET_PRIVATE((obj), X_TYPE_EDITOR, XEditorPrivate))

G_DEFINE_TYPE (XEditor, x_editor, G_TYPE_OBJECT);

static void
x_editor_init (XEditor * self)
{
	XEditorPrivate * priv = X_EDITOR_GET_PRIVATE(self);

	priv->xWindow = x_window_new ();

    x_editor_menubar_connect_all_signals(self);

}

static void
x_editor_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (x_editor_parent_class)->finalize (object);
}

static void
x_editor_class_init (XEditorClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (XEditorPrivate));

	object_class->finalize = x_editor_finalize;
}


GObject *
x_editor_new (void)
{
	return g_object_new (X_TYPE_EDITOR, NULL);

}

/*
 * getters ::
 */
GtkWidget *
x_editor_get_window (XEditor * self)
{
    XEditorPrivate * priv = X_EDITOR_GET_PRIVATE(self);

    return priv->xWindow;
}

GtkWidget *
x_editor_get_menubar (XEditor * self)
{
    XEditorPrivate * priv = X_EDITOR_GET_PRIVATE(self);

    return x_window_get_menubar (X_WINDOW(x_editor_get_window(self)));
}

GtkWidget *
x_editor_get_notebook (XEditor * self)
{
    XEditorPrivate * priv = X_EDITOR_GET_PRIVATE(self);

    return x_window_get_notebook (X_WINDOW(x_editor_get_window(self)));
}



/*
 * Another methods ::
 */
void
x_editor_menubar_connect_all_signals (XEditor * self)
{
   // XEditorPrivate * priv = X_EDITOR_GET_PRIVATE (self);

    //x_notebook_append (X_NOTEBOOK(x_editor_get_notebook(self)));
    //x_notebook_refresh (X_NOTEBOOK(x_editor_get_notebook(self)));a
    x_menubar_connect_newitem_signal(X_MENUBAR(x_editor_get_menubar(self)),
                                    x_editor_get_notebook(self));
    x_menubar_connect_saveitem_signal (X_MENUBAR(x_editor_get_menubar(self)),
				    x_editor_get_notebook(self));
}

void
x_editor_show (XEditor * self)
{
    gtk_widget_show_all (x_editor_get_window (self));
}
