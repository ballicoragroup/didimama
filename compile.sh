#!/bin/sh

gcc -DNDEBUG -Wall -Wextra -O3 myopt/myopt.c proginfo.c rmsdcmp.c pdb.c fit.c strtools.c main.c -I myopt -o didimama -lm

