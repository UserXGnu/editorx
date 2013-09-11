/*
 * window.c
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

#include "definitions.h"


/*****************
 * Constructor
 ****************/
Window * x_window_new(void) {
	// allocatting to HEAP memory sector ::
	Window * win = (Window *) g_malloc(sizeof(Window));
	
	// new window, setting title, default position and default length ::
	win->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW(win->window), GTK_WIN_POS_CENTER);

	// initializing window class private data ::
	x_window_init(win);

#ifdef X_WINDOW_DEFAULT_X_LEN
#ifdef X_WINDOW_DEFAULT_Y_LEN
	gtk_window_set_default_size(GTK_WINDOW(win->window),
	                            X_WINDOW_DEFAULT_X_LEN, X_WINDOW_DEFAULT_Y_LEN);
#endif
#endif

	// new vertical box that will handle everything ::
	win->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // inserting box into window container ::
	gtk_container_add(GTK_CONTAINER(win->window), win->box);

	return win;
}


/*******************************
 * initializing private data        
 ******************************/
void x_window_init(Window * win) {
	win->private_data = (WindowPrivate *) g_malloc(sizeof(WindowPrivate));
	x_window_set_default_title (win);
}

/*************
 * Getters 
 ************/
// return corrent window title :: ----------------------------------
gchar * x_window_get_title(Window * win) {
	return g_strdup(win->private_data->title);
}

/*************
 * Setters
 ************/
// It will set default title :: ------------------------------------
void x_window_set_default_title (Window * win) {
	win->private_data->title = g_strdup_printf("%s %s", X_WINDOW_DEFAULT_TITLE, X_DEFAULT_FILENAME);
	x_window_set_title(win, win->private_data->title);
}

// It will set title :: --------------------------------------
void x_window_set_title(Window * win, gchar * title){
	gtk_window_set_title(GTK_WINDOW(win->window), title);
	win->private_data->title = g_strdup(title);
	
}