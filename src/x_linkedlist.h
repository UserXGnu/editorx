/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * x_linkedlist.h
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


#ifndef _X_LINKEDLIST_H_
#define _X_LINKEDLIST_H_

#include <glib-object.h>
#include <gtk/gtk.h>

#include <stdlib.h>

#include "x_button.h"

G_BEGIN_DECLS

typedef struct _info info;
typedef struct _XLinkedList XLinkedList;

struct _info {

    GtkWidget * button;
    GtkWidget * tView;
    gchar * filename;

    info * next;

};

struct _XLinkedList {

    info * begin;
    info * end;
    guint counter;

};

void x_linkedlist_init (XLinkedList * xl);
void x_linkedlist_insert (XLinkedList * xl, info * data);
void x_linkedlist_remove (XLinkedList * xl, info * data);
void x_linkedlist_show (XLinkedList * xl); // just for debug ::
void x_linkedlist_finalize (XLinkedList * xl);
void x_linkedlist_sort (XLinkedList * xl);

info * x_linkedlist_get_element (XLinkedList * xl, guint page_pos);
guint x_linkedlist_get_length (XLinkedList * xl);

G_END_DECLS

#endif /*_X_LINKEDLISG_H_ */

