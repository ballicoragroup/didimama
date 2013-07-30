#!/bin/sh

gcc -DNDEBUG -Wall -Wextra -O3 myopt/myopt.c proginfo.c main.c rmsdcmp.c pdb.c fit.c strtools.c -I myopt -o localrmsd -lm

