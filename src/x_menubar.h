/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
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

#ifndef _X_MENUBAR_H_
#define _X_MENUBAR_H_

#include "definitions.h"

G_BEGIN_DECLS

#define X_TYPE_MENUBAR              (x_menubar_get_type ())
#define X_MENUBAR(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), X_TYPE_MENUBAR, XMenubar))
#define X_MENUBAR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), X_TYPE_MENUBAR, XMenubarClass))
#define X_IS_MENUBAR(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), X_TYPE_MENUBAR))
#define X_IS_MENUBAR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), X_TYPE_MENUBAR))
#define X_MENUBAR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), X_TYPE_MENUBAR, XMenubarClass))

typedef struct _XMenubarClass XMenubarClass;
typedef struct _XMenubar    XMenubar;
typedef struct _XMenubarPrivate XMenubarPrivate;

typedef enum _XMenuType XMenuType;

struct _XMenubarClass {
    GtkMenuBarClass parent_class;

};

struct _XMenubar {
    GtkMenuBar parent_instance;

    XMenubarPrivate * priv;
};

enum _XMenuType {

    XMenuFile,
    XMenuEdit,
    XMenuView,
    XMenuAbout,

};


GType x_menubar_get_type (void) G_GNUC_CONST;

GtkWidget * x_menubar_new (void);


/*
 * Callbacks ::
 */
void x_menubar_file_new_callback (GtkWidget * widget, gpointer data);
void x_menubar_file_save_callback (GtkWidget * widget, gpointer data);
void x_menubar_load_file_callback (GtkWidget * widget, gpointer data);

void x_menubar_undo_callback (GtkWidget * widget, gpointer data);
void x_menubar_redo_callback (GtkWidget * widget, gpointer data);

void x_menubar_cut_callback (GtkWidget * widget, gpointer data);
void x_menubar_copy_callback (GtkWidget * widget, gpointer data);
void x_menubar_paste_callback (GtkWidget * widget, gpointer data);
void x_menubar_selectall_callback (GtkWidget * widget, gpointer data);
void x_menubar_clear_callback (GtkWidget * widget, gpointer data);

/*
 * Methods ::
 */
void x_menubar_connect_newitem_signal (XMenubar * self, GtkWidget * widget);
void x_menubar_connect_saveitem_signal (XMenubar * self, GtkWidget * widget);
void x_menubar_connect_openitem_signal (XMenubar * self, GtkWidget * widget);

void x_menubar_connect_undoitem_signal (XMenubar * self, GtkWidget * widget);
void x_menubar_connect_redoitem_signal (XMenubar * self, GtkWidget * widget);

void x_menubar_connect_cutitem_signal (XMenubar * self, GtkWidget * widget);
void x_menubar_connect_copyitem_signal (XMenubar * self, GtkWidget * widget);
void x_menubar_connect_pasteitem_signal (XMenubar * self, GtkWidget * widget);
void x_menubar_connect_selectallitem_signal (XMenubar * self, GtkWidget * widget);
void x_menubar_connect_clearitem_signal (XMenubar * self, GtkWidget * widget);

G_END_DECLS


#endif /* _X_MENUBAR_H_*/

