#!/usr/bin/perl

chdir "../../proj";
system("make clean_lib  TARGET=app");
system("make clean_lib  TARGET=widget");
system("make clean_lib  TARGET=mmicomn");