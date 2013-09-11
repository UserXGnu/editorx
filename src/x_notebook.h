/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  
*/
/*
 * x_notebook.h
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
#ifndef _X_NOTEBOOK_H_
#define _X_NOTEBOOK_H_

#include <glib-object.h>
#include <gtk/gtk.h>
#include "definitions.h"

G_BEGIN_DECLS

#define X_TYPE_NOTEBOOK             (x_notebook_get_type())
#define X_NOTEBOOK(obj)             (G_TYPE_CHECK_INSTANCE_CAST((obj), X_TYPE_NOTEBOOK, XNotebook))
#define X_NOTEBOOK_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST((klass), X_TYPE_NOTEBOOK, XNotebookClass))
#define X_IS_NOTEBOOK(obj)          (G_TYPE_CHECK_INSTANCE_TYPE((obj), X_TYPE_NOTEBOOK))
#define X_IS_NOTEBOOK_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE((klass), X_TYPE_NOTEBOOK))
#define X_NOTEBOOK_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), X_TYPE_NOTEBOOK, XNotebookClass))

typedef struct _XNotebookClass      XNotebookClass;
typedef struct _XNotebook           XNotebook;
typedef struct _XNotebookPrivate    XNotebookPrivate;

struct _XNotebookClass {
    GtkNotebookClass parent_class;

};

struct _XNotebook {
    GtkNotebook parent_intance;

    XNotebookPrivate * priv;
};

GType x_notebook_get_type (void) G_GNUC_CONST;
GtkWidget * x_notebook_new (void);


// callbacks ::
void x_notebook_nbtn_callback (GtkWidget * widget, gpointer data);
void x_notebook_remove_tab_callback (GtkWidget * widget, gpointer data);

// getters ::
XLinkedList * x_notebook_get_xlinkedlist (XNotebook * self);
// another methods ::
void x_notebook_append (XNotebook * self);
void x_notebook_refresh (XNotebook * self);

G_END_DECLS

#endif /* _X_NOTEBOOK_H_ */

