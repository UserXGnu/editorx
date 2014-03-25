EditorX
========

A Gtk/C simple text editor with some features.



Update
======

* added notebook support to editing multiple files.

* adding GtkSourceView support to:
        syntax highlight,
        auto-identation,
        smart tab,
        auto-completion,
        line-numbering.

* added syntax highlight for:
        C,
        C++,
        Python,
        Java,
        PHP,
        HTML.


Release Notes
=============

* To make everything works with OO paradigm it was needed to make a massive modification
on the whole code. I don't know how to use the GSList from GLib API so I needed
to create my own linkedlist instead of use from there.

* It's important to know that GtkSourceView has a lot of features and I'm implementing
one-by-one and it's not completly working well yet.


Observation
===========

* As just a enthusiast I hope you understand that there's a lot of things that I don't even 
know and/or understand yet about GTK and OO into GLib perspective. Sorry about my mistakes and
any warning or help will be welcomed.

