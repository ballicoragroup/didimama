#include <stdio.h>
#include <stdlib.h>
#include "proginfo.h"

/*************************************************************************************************************/
#include "myopt.h"

const char *license_str =
"Copyright (c) 2012 Miguel A. Ballicora\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
"EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES\n"
"OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND\n"
"NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT\n"
"HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,\n"
"WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING\n"
"FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n"
"OTHER DEALINGS IN THE SOFTWARE."
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
		"Copyright (c) 2013 Miguel A. Ballicora\n"
		"There is NO WARRANTY of any kind\n"
		;

	static const char *intro_str =
		"Scan local differences (rmsd) between two different protein conformers\n"
		;

	static const char *example_str =
		"with a window of 11 residues, compare file1.pdb and file.pdb\noutput are comma separated values\n"
		;

	static const char *help_str =
		" -h        print this help\n"
		" -v        print version number and exit\n"
		" -L        display the license information\n"
		" -a <file> first  input file (pdb format)\n"
		" -b <file> second input file (pdb format)\n"
		" -w <num>  window size in residues, default=11\n"
		"\n"
	/*	 ....5....|....5....|....5....|....5....|....5....|....5....|....5....|....5....|*/
		;

const char *OPTION_LIST = "vha:b:Lw:";

/*
|
|	MAIN
|
\*--------------------------------------------------------------*/

int main (int argc, char *argv[])
{
	int op;
	char *fileA, *fileB, *extra;
	int Window;
	int version_mode, help_mode, license_mode, input_mode;

	/* defaults */
	version_mode = FALSE;
	license_mode = FALSE;
	help_mode    = FALSE;
	input_mode   = FALSE;
	fileA        = NULL;
	fileB        = NULL;
	extra		 = NULL;
	Window 		 = 11;

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
			case 'w': 	if (1 != sscanf(opt_arg,"%d", &Window)) {
							fprintf(stderr, "wrong window parameter\n");
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


printf ("Window=%d\n",Window);
printf ("FileA=%s\n",fileA?fileA:"NULL");
printf ("FileB=%s\n",fileB?fileB:"NULL");
printf ("Extra=%s\n",extra?extra:"NULL");

	exit(EXIT_SUCCESS);
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
	char *example_options = "-w 11 -a file1.pdb -b file2.pdb";
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