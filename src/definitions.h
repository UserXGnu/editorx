#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#include <glib-object.h>
#include <gtk/gtk.h>

#include <gtksourceview/gtksourceview.h>
#include <gtksourceview/gtksourcebuffer.h>
#include <gtksourceview/gtksourcelanguage.h>
#include <gtksourceview/gtksourcelanguagemanager.h>

#include <stdlib.h>
#include <unistd.h>

#include "x_button.h"

#include "x_linkedlist.h"

#include "x_notebook.h"

//#include "xsearch.h"

#include "x_menubar.h"

#include "x_window.h"

#include "x_editor.h"



#ifndef DEFAULT_TITLE
#define DEFAULT_TITLE(n)   (g_strdup_printf("Untitled Document %d", (n)))
#endif

#ifndef SET_HOME_PATH
#define SET_HOME_PATH   (system ("export HOME=~"))
#endif 

#ifndef DEFAULT_PATH
#define DEFAULT_PATH    (getenv ("HOME"))
#endif

#ifndef DEFAULT_TITLE
#define DEFAULT_TITLE(n)    (g_strdup_printf ("Untitled Document %d", (n)))
#endif

#endif /* _DEFIITIONS_H_ */
