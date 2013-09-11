/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  
*/
/*
 * x_button.c
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

#include "x_button.h"
#include "definitions.h"
/*
 * **@brief: It will contain just the position on the list
 * of it's own tab handler, however, I think that I will need
 * some other things, I don't know what yet.
 */
struct _XButtonPrivate {

    guint page_pos;

};

#define X_BUTTON_GET_PRIVATE(obj)   (G_TYPE_INSTANCE_GET_PRIVATE((obj), X_TYPE_BUTTON, XButtonPrivate))

enum {
    PROP_0,

    PROP_PAGE_POS
};

G_DEFINE_TYPE (XButton, x_button, GTK_TYPE_BUTTON);

static void
x_button_init (XButton * self)
{
    // Nothing to put here for now.
}

/*
 * Destructor ::
 */
static void
x_button_finalize (GObject * object)
{
    // Need to insert deinitalization here.
    
    G_OBJECT_CLASS(x_button_parent_class)->finalize (object);
}

static void
x_button_set_property (GObject * object, guint prop_id, const GValue * value, GParamSpec * pspec)
{
    g_return_if_fail (X_IS_BUTTON (object));

    XButtonPrivate * priv = X_BUTTON_GET_PRIVATE (X_BUTTON (object));

    switch (prop_id) {

        case PROP_PAGE_POS:
            priv->page_pos = g_value_get_uint (value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;

    }
}

static void
x_button_get_property (GObject * object, guint prop_id, GValue * value, GParamSpec * pspec)
{
    g_return_if_fail (X_IS_BUTTON (object));

    XButtonPrivate * priv = X_BUTTON_GET_PRIVATE (X_BUTTON (object));

    switch (prop_id) {

        case PROP_PAGE_POS:
            g_value_set_uint (value, priv->page_pos);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;

    }
}

/*
 * **@brief: Here all loose knot will be tied ::
 */
static void
x_button_class_init (XButtonClass * klass)
{
    GObjectClass * object_class = G_OBJECT_CLASS (klass);
    GtkButtonClass * parent_class = GTK_BUTTON_CLASS(klass);

    g_type_class_add_private (klass, sizeof (XButtonPrivate));

    object_class->finalize = x_button_finalize;
    object_class->set_property = x_button_set_property;
    object_class->get_property = x_button_get_property;

    g_object_class_install_property (object_class,
                                     PROP_PAGE_POS,
                                     g_param_spec_uint ("page_pos",
                                                   "Page_pos",
                                                   "Position",
                                                   0, /* **@brief: adjust minimum property value */
                                                   G_MAXUINT, /* **@brief: adjust the maximum property value */
                                                   0,
                                                   G_PARAM_READABLE | G_PARAM_WRITABLE));
}

/*
 * constructor ::
 */
GtkWidget *
x_button_new (void)
{
    return GTK_WIDGET(g_object_new (X_TYPE_BUTTON, NULL));
}

/*
 * Getters ::
 */
guint
x_button_get_page_pos (XButton * self)
{
    guint page_pos;

    g_object_get (self, "page_pos", &page_pos, NULL);

    return page_pos;
}

/*
 * Setters ::
 */
void
x_button_set_page_pos (XButton * self, guint page_pos)
{
    g_object_set (self, "page_pos", page_pos, NULL);
}

