/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * x_window.h
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

#ifndef _X_WINDOW_H_
#define _X_WINDOW_H_

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define X_TYPE_WINDOW             (x_window_get_type ())
#define X_WINDOW(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), X_TYPE_WINDOW, XWindow))
#define X_WINDOW_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), X_TYPE_WINDOW, XWindowClass))
#define X_IS_WINDOW(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), X_TYPE_WINDOW))
#define X_IS_WINDOW_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), X_TYPE_WINDOW))
#define X_WINDOW_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), X_TYPE_WINDOW, XWindowClass))

typedef struct _XWindowClass XWindowClass;
typedef struct _XWindow XWindow;
typedef struct _XWindowPrivate XWindowPrivate;


struct _XWindowClass
{
	GtkWindowClass parent_class;
};

struct _XWindow
{
	GtkWindow parent_instance;

	XWindowPrivate *priv;
};

GType x_window_get_type (void) G_GNUC_CONST;
GtkWidget * x_window_new (void);


/*
 * getters ::
 */
GtkWidget * x_window_get_box (XWindow * self);
GtkWidget * x_window_get_menubar (XWindow * self);
GtkWidget * x_window_get_notebook (XWindow * self);

G_END_DECLS

#endif /* _X_WINDOW_H_ */

