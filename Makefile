CC = gcc
CFLAGS = -DNDEBUG -flto -I myopt
WARN = -Wwrite-strings -Wconversion -Wshadow -Wparentheses -Wlogical-op -Wunused -Wmissing-prototypes -Wmissing-declarations -Wdeclaration-after-statement -W -Wall -Wextra
OPT = -O3
LIBFLAGS = -lm

EXE = didimama

SRC = myopt/myopt.c proginfo.c rmsdcmp.c pdb.c fit.c strtools.c main.c
DEPS = bool.h  fit.h  pdb.h  proginfo.h  progname.h  rmsdcmp.h  strtools.h  version.h
OBJ = myopt/myopt.o proginfo.o rmsdcmp.o pdb.o fit.o strtools.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

didimama: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(WARN) $(OPT) $(LIBFLAGS)

all:
	$(CC) $(CFLAGS) $(WARN) $(OPT) -o $(EXE) $(SRC) $(LIBFLAGS)

install:
	cp $(EXE) /usr/local/bin/$(EXE)

clean:
	rm -f *.o *~ myopt/*.o 








