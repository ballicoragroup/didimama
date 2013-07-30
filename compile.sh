#!/bin/sh

gcc -DNDEBUG -Wall -Wextra -O3 myopt/myopt.c proginfo.c main.c -I myopt -o localrmsd

