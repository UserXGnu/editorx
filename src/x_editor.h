/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * x_editor.h
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

#ifndef _X_EDITOR_H_
#define _X_EDITOR_H_

#include "definitions.h"

G_BEGIN_DECLS

#define X_TYPE_EDITOR             (x_editor_get_type ())
#define X_EDITOR(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), X_TYPE_EDITOR, XEditor))
#define X_EDITOR_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), X_TYPE_EDITOR, XEditorClass))
#define X_IS_EDITOR(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), X_TYPE_EDITOR))
#define X_IS_EDITOR_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), X_TYPE_EDITOR))
#define X_EDITOR_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), X_TYPE_EDITOR, XEditorClass))

typedef struct _XEditorClass XEditorClass;
typedef struct _XEditor XEditor;
typedef struct _XEditorPrivate XEditorPrivate;


struct _XEditorClass
{
	GObjectClass parent_class;
};

struct _XEditor
{
	GObject parent_instance;

	XEditorPrivate *priv;
};

GType x_editor_get_type (void) G_GNUC_CONST;
GObject * x_editor_new (void);


/*
 * getters::
 */
GtkWidget * x_editor_get_window (XEditor * self);
GtkWidget * x_editor_get_menubar (XEditor * self);
GtkWidget * x_editor_get_notebook (XEditor * self);

/*
 * setters ::
 */


/*
 * Another methods ::
 */
void x_editor_menubar_connect_all_signals (XEditor * self);
void x_editor_show (XEditor * self);
G_END_DECLS

#endif /* _X_EDITOR_H_ */

