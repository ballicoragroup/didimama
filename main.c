#include <stdio.h>
#include <stdlib.h>
#include "proginfo.h"

#include "rmsdcmp.h"

/*************************************************************************************************************/
#include "myopt.h"

const char *license_str = "\n"
" Copyright (c) 2015 Miguel A. Ballicora\n"
" Didimama is program to obtain a delta distance matrix map in protein structures\n"
"\n"
" Didimama is free software: you can redistribute it and/or modify\n"
" it under the terms of the GNU General Public License as published by\n"
" the Free Software Foundation, either version 3 of the License, or\n"
" (at your option) any later version.\n"
"\n"
" Didimama is distributed in the hope that it will be useful,\n"
" but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" GNU General Public License for more details.\n"
"\n"
" You should have received a copy of the GNU General Public License\n"
" along with Didimama.  If not, see <http://www.gnu.org/licenses/>.\n"
;

static void parameter_error(void);
static void example (void);
static void usage (void);

/* TYPES */

	typedef int bool_t;
	#define FALSE 0
	#define TRUE !FALSE

/* VARIABLES */

	static const char *copyright_str = 
		"Copyright (c) 2015 Miguel A. Ballicora\n"
		"There is NO WARRANTY of any kind\n"
		;

	static const char *intro_str =
		"Obtain a delta distance matrix map (didimama)\n"
		;

	static const char *example_str =
		"delta distance matrix map is created from residues 260 to 519 in this example.\n"
		"files for comparison are file1.pdb and file2.pdb\n"
		"output is in comma separated values\n"
		;

	static const char *help_str =
		" -h        print this help\n"
		" -v        print version number and exit\n"
		" -L        display the license information\n"
		" -a <file> first  input file (pdb format)\n"
		" -b <file> second input file (pdb format)\n"
		" -f <num>  first residue number included in the analysis\n"
		" -t <num>  last  residue number included in the analysis\n"
		"\n"
	/*	 ....5....|....5....|....5....|....5....|....5....|....5....|....5....|....5....|*/
		;

const char *OPTION_LIST = "vha:b:Lw:f:t:";

/*
|
|	MAIN
|
\*--------------------------------------------------------------*/

int main (int argc, char *argv[])
{
	int op;
	char *fileA, *fileB, *extra;
	int Resfrom;
	int Resto;
	int version_mode, help_mode, license_mode, input_mode;

	/* defaults */
	version_mode = FALSE;
	license_mode = FALSE;
	help_mode    = FALSE;
	input_mode   = FALSE;
	fileA        = NULL;
	fileB        = NULL;
	extra		 = NULL;
	Resfrom      = 1;
	Resto        = 0;

	while (END_OF_OPTIONS != (op = options (argc, argv, OPTION_LIST))) {
		switch (op) {
			case 'v':	version_mode = TRUE; 	break;
			case 'L':	version_mode = TRUE; 	
						license_mode = TRUE;
						break;
			case 'h':	help_mode = TRUE;		break;
			case 'a': 	input_mode = TRUE;
					 	fileA = opt_arg;
						break;
			case 'b': 	input_mode = TRUE;
					 	fileB = opt_arg;
						break;
			case 'f': 	if (1 != sscanf(opt_arg,"%d", &Resfrom)) {
							fprintf(stderr, "wrong residue number (from)\n");
							exit(EXIT_FAILURE);
						}
						break;
			case 't': 	if (1 != sscanf(opt_arg,"%d", &Resto)) {
							fprintf(stderr, "wrong residue number (to)\n");
							exit(EXIT_FAILURE);
						}
						break;						
			//
			case '?': 	parameter_error();
						exit(EXIT_FAILURE);
						break;
			default:	fprintf (stderr, "ERROR: %d\n", op);
						exit(EXIT_FAILURE);
						break;
		}		
	}

	/*----------------------------------*\
	|	Return version
	\*----------------------------------*/
	if (version_mode) {
		printf ("%s %s\n",proginfo_name(),proginfo_version());
		if (license_mode)
 			printf ("%s\n", license_str);
		return EXIT_SUCCESS;
	}
	if (argc < 2) {
		fprintf (stderr, "%s %s\n",proginfo_name(),proginfo_version());
		fprintf (stderr, "%s", copyright_str);
		fprintf (stderr, "for help type:\n%s -h\n\n", proginfo_name());		
		exit (EXIT_FAILURE);
	}
	if (help_mode) {
		printf ("\n%s", intro_str);
		example();
		usage();
		printf ("%s\n", copyright_str);
		exit (EXIT_SUCCESS);
	}
	if ((argc - opt_index) > 1) {
		/* too many parameters */
		fprintf (stderr, "Extra parameters parameters present\n");
		exit(EXIT_FAILURE);
	}
	if (input_mode && argc != opt_index) {
		fprintf (stderr, "Extra parameters parameters present\n");
		exit(EXIT_FAILURE);
	}
	if (!input_mode && argc == opt_index) {
		fprintf (stderr, "Need file name to proceed\n");
		exit(EXIT_FAILURE);
	}
	/* get folder, should be only one at this point */
	while (opt_index < argc ) {
		extra = argv[opt_index++];
	}

	if (extra) printf ("Extra parameter = %s\n",extra);

	if (Resto <= Resfrom) {
		fprintf(stderr, "Residue if switch -t (to) should be higher than the one in switch -f (from)");
		exit(EXIT_FAILURE);
	}

	return	matdist(fileA, fileB, Resfrom, Resto);
}


/*--------------------------------------------------------------*\
|
|	END OF MAIN
|
\**/


static void parameter_error(void) {	printf ("Error in parameters\n"); return;}

static void
example (void)
{
	char *example_options = "-a file1.pdb -b file2.pdb -f 260 -t 519\n";
	fprintf (stderr, "\n"
		"quick example: %s %s\n"
		"%s"
		, proginfo_name()
		, example_options
		, example_str);
	return;
}

static void
usage (void)
{
	char *usage_options = "[-OPTION]";
	fprintf (stderr, "\n"
		"usage: %s %s\n"
		"%s"
		, proginfo_name()
		, usage_options
		, help_str);
}
