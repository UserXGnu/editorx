/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  
*/
/*
 * x_button.h
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
 *
 */

/******************************************************************************
 *                              ##  WARNING  ##                               *
 *                                                                            *
 *                                                                            *
 *  I created this class with GtkButtonClass inheritance, I must be honest, I *
 * do not know how to make a GtkNotebook with close button on every tab, so   *
 * I decided to create a new Class that will contain the position of it's own *
 * tab handler. Yeah, I know, it's not a good idea, so I wish to receive some *
 * help here.                                                                 *
 *  Anyway, this class will be deleted soon when discover how to implement    *
 * this thing.                                                                *
 *                                                                            *
 *                                                                            *
 ******************************************************************************/

#ifndef _X_BUTTON_H_
#define _X_BUTTON_H_

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define X_TYPE_BUTTON               (x_button_get_type())
#define X_BUTTON(obj)               (G_TYPE_CHECK_INSTANCE_CAST((obj), X_TYPE_BUTTON, XButton))
#define X_BUTTON_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST((klass), X_TYPE_BUTTON, XButtonClass))
#define X_IS_BUTTON(obj)            (G_TYPE_CHECK_INSTANCE_TYPE((obj), X_TYPE_BUTTON))
#define X_IS_BUTTON_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE((klass), X_TYPE_BUTTON))
#define X_BUTTON_GET_CLASS(obj)     (G_TYPE_INTANCE_GET_CLASS((obj), X_TYPE_BUTTON, XButtonClass))

typedef struct _XButtonClass    XButtonClass;
typedef struct _XButton         XButton;
typedef struct _XButtonPrivate  XButtonPrivate;

struct _XButtonClass {
    GtkButtonClass parent_class;

};

struct _XButton {
    GtkButton parent_instance;

    XButtonPrivate * priv;
};

GType x_button_get_type (void) G_GNUC_CONST;
GtkWidget * x_button_new (void);

/*
 * Getters ::
 */
guint x_button_get_page_pos (XButton * self) G_GNUC_CONST;

/*
 * Setters ::
 */
void x_button_set_page_pos (XButton * self, guint page_pos);

G_END_DECLS

#endif /* _X_BUTTON_H_ */
