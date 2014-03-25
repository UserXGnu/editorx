PKG_CONFIG = `pkg-config --libs --cflags gtk+-3.0 gtksourceview-3.0`
CC = gcc
LIB_F = definitions.h x_menubar.h x_menubar.c x_button.h x_linkedlist.h x_linkedlist.c x_button.c x_notebook.h x_notebook.c x_window.h x_window.c x_editor.h x_editor.c
LIB_O = x_menubar.o x_linkedlist.o x_button.o x_notebook.o x_window.o x_editor.o
MAIN = main.c
OBJ = ../xeditor
TRASH = x_menubar.h.gch x_linkedlist.h.gch x_button.h.gch x_notebook.h.gch x_window.h.gch x_editor.h.gch definitions.h.gch


libs:
	$(CC) $(LIB_F) -c $(PKG_CONFIG) 
	rm -rf $(TRASH)

all:
	$(CC) $(LIB_F) -c $(PKG_CONFIG) 
	$(CC) $(MAIN) $(LIB_O) -o $(OBJ) $(PKG_CONFIG)
	rm -rf $(TRASH)

clean:
	rm -rf $(TRASH) $(OBJ) $(LIB_O)
