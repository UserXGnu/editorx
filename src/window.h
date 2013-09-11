/*
 * window.h
 *
 * Copyright (C) 2013 - userx
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _WINDOW_H
#define _WINDOW_H


/*
 * Window Class Private data definition
 */ 
typedef struct _windowprivate WindowPrivate;
struct _windowprivate {
	gchar * title;
};

/*
 * Window class definition
 */ 
typedef struct _window Window;
struct _window {
	GtkWidget * window;
	GtkWidget * box;

	WindowPrivate * private_data;
};

/***************
 * constructor
 * ************/
Window * x_window_new(void) G_GNUC_CONST;

/******************************
 * initialize private data 
 * ***************************/
void x_window_init(Window *);

/***************
 * getters
 * ************/
gchar * x_window_get_title(Window *) G_GNUC_CONST;

/***************
 * setters
 * ************/
void x_window_set_default_title (Window *);
void x_window_set_title (Window *, gchar *);

#endif /*_WINDOW_H */