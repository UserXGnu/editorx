/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  
*/
/*
 * x_linkedlist.c
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
#include "x_linkedlist.h"
#include "definitions.h"

void
x_linkedlist_init (XLinkedList * xl)
{
    xl->begin = NULL;
    xl->end = NULL;
    xl->counter = 1; // in this case, it will not start from 0 ::
}


/*
 * **@brief: insert a node into the XLinkedList ::
 */
void
x_linkedlist_insert (XLinkedList * xl, info * data)
{
    data->next = NULL;
    if (xl->counter == 1) {

        xl->begin = data;
        xl->end = data;
        xl->counter++;

    } else {
        
        xl->end->next = data;
        xl->end = data;
        xl->counter++;

    }

}

/*
 * **@brief: Erase a node from XLinkedList
 */
void
x_linkedlist_remove (XLinkedList * xl, info * data)
{
    info * iterator = xl->begin;
    info * aux;

    if (data->button == xl->begin->button) {
        iterator = xl->begin;
        xl->begin = xl->begin->next;

        g_free(iterator);
    } else {

        for (iterator = xl->begin; iterator; iterator = iterator->next) {

            if (iterator->button == data->button) {
                break;
            }

            aux = iterator;

        }

        aux->next = iterator->next;
        g_free(iterator);

    }

    xl->counter--;

    x_linkedlist_sort(xl);

}

/*
 *  **@brief: This next method must be called just for debug and it will 
 *  iterate the XLinkedList and show every element on the stdout ::
 */
void
x_linkedlist_show (XLinkedList * xl)
{
    info * iterator;
    guint counter;
    guint page_pos;

    for (iterator = xl->begin; iterator; iterator = iterator->next) {

        page_pos = x_button_get_page_pos (X_BUTTON (iterator->button));
        g_print("NODE[%d] - Page_Pos: %d\n", counter, page_pos);
        counter++;

    }

}

/*
 * **@brief: XLinkedList destructor ::
 */
void
x_linkedlist_finalize (XLinkedList * xl)
{
    info * iterator = xl->begin;
    info * aux;

    while (iterator) {

        aux = iterator;
        iterator = iterator->next;

        g_free(aux);

    }  
}

void
x_linkedlist_sort (XLinkedList * xl)
{
    
    info * iterator;
    guint page_pos = 1;
    
    for (iterator = xl->begin; iterator; iterator = iterator->next) {

        x_button_set_page_pos (X_BUTTON(iterator->button), page_pos);
        page_pos++;

    }

}

/*
 * **@brief: This method return the node at page_pos, it's useful at same
 * cases, anyway, created to help when I wnat to remove some node ::
 */
info *
x_linkedlist_get_element (XLinkedList * xl, guint page_pos)
{
    info * iterator;

    for (iterator = xl->begin; iterator; iterator = iterator->next) {

        if ((x_button_get_page_pos (X_BUTTON(iterator->button))) == page_pos) {
            
            break;

        }

    }

    return iterator;
}

guint
x_linkedlist_get_length (XLinkedList * xl)
{
    return xl->counter;
}

