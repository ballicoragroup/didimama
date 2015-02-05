#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "bool.h"
#include "pdb.h"
#include "fit.h"
#include <math.h>

#include "rmsdcmp.h"

static void coord_extract (const struct coordinates *c, struct coordinates *o, int from, int to);

//-----------------------------------------------------------------------------

void mod2_CAcoord(const struct model *m, struct coordinates *c);
void mod2_ALLcoord(const struct model *m, struct coordinates *c, int from, int to);
static void mod2_CAcoord_resfrom_resto(const struct model *m, struct coordinates *c, int resfrom, int resto);

//=============================================================================

static void
collectmypdb	(const char *name_i, struct model *pmodel_input);


extern int 
rmsdcmp(char *FILE1, char* FILE2, int window)
{
	double rmsd;
	struct coordinates SCA, SCB, SCA_all, SCB_all;   
	struct transrot tr;
	struct model MIA, MIB;

	int n_slices, fr, to, av, j;

	collectmypdb	(FILE1, &MIA);
	collectmypdb	(FILE2, &MIB);

	mod2_CAcoord (&MIA, &SCA_all);
	mod2_CAcoord (&MIB, &SCB_all);

	n_slices = (SCA_all.n - window + 1);

	for (j = 0; j < n_slices; j++) {

		fr = j;
		to = fr + window - 1;
		av = (fr+to)/2;

		coord_extract (&SCA_all, &SCA, fr, to);
		coord_extract (&SCB_all, &SCB, fr, to);

		if (SCA.n == 0 || SCB.n == 0 || SCA.n != SCB.n) {
			fprintf (stderr, "Warning: File could be empty\n"); 
			return EXIT_FAILURE;
		} 

		rmsd = fit (&SCA, &SCB, &tr);
				
		printf("%d, %lf\n",av+16,rmsd);
	}

    return EXIT_SUCCESS;
}

static double distA[1000000], distB[1000000];

extern int 
matdist(char *FILE1, char* FILE2, int resfrom, int resto)
{
int i,j,k,n;
double d0,d1,d2;

double max = 0;
int maxi = 0;
int maxj = 0;

double min = 0;
int mini = 0;
int minj = 0;

	struct coordinates *a, *b; 
	struct coordinates SCA, SCB;   
	struct model MIA, MIB;

	collectmypdb	(FILE1, &MIA);
	collectmypdb	(FILE2, &MIB);
	
	mod2_CAcoord_resfrom_resto(&MIA, &SCA, resfrom, resto);
	mod2_CAcoord_resfrom_resto(&MIB, &SCB, resfrom, resto);

	if (SCA.n == 0 || SCB.n == 0 || SCA.n != SCB.n) {
		fprintf (stderr, "Warning: File could be empty\n"); 
		return EXIT_FAILURE;
	} 

	a = &SCA;
	b = &SCB;

	n = resto - resfrom + 1;
	k = 0;
	
for (i = 0; i < n; i++) {	
	for (j = 0; j < n; j++) {

		d0 = a->atm[i][0] - a->atm[j][0];
		d1 = a->atm[i][1] - a->atm[j][1];
		d2 = a->atm[i][2] - a->atm[j][2];

		distA[k++] = sqrt (d0*d0 + d1*d1 + d2*d2);
	}
}

k = 0;
for (i = 0; i < n; i++) {	
	for (j = 0; j < n; j++) {

		d0 = b->atm[i][0] - b->atm[j][0];
		d1 = b->atm[i][1] - b->atm[j][1];
		d2 = b->atm[i][2] - b->atm[j][2];

		distB[k++] = sqrt (d0*d0 + d1*d1 + d2*d2);
	}
}

max = 0;
maxi = 0;
maxj = 0;

min = 0;
mini = 0;
minj = 0;

#if 0
k = 0;
for (i = 0; i < n; i++) {	
	for (j = 0; j < n; j++) {
		double diff = distA[k]-distB[k];


//printf ("%d %d %lf\n",i+16,j+16,diff);

		printf ("%lf, ",diff); 
		
		k++;

		if (diff > max) {max = diff; maxi = i; maxj = j;}
		if (diff < min) {min = diff; mini = i; minj = j;}
	}
	printf ("\n");

}
#endif

k = 0;
for (i = 0; i < n; i++) {	
	for (j = 0; j < n; j++) {
		double diff = distA[k]-distB[k];

		printf ("%d, %d, %lf\n",resfrom+i,resfrom+j,diff);
		k++;

		if (diff > max) {max = diff; maxi = i; maxj = j;}
		if (diff < min) {min = diff; mini = i; minj = j;}
	}
}
printf ("\n");



fprintf(stderr, "(in pdb) max=%lf, maxi=%d, maxj=%d\n", max, maxi+resfrom, maxj+resfrom);
fprintf(stderr, "(in pdb) min=%lf, mini=%d, minj=%d\n", min, mini+resfrom, minj+resfrom);

fprintf(stderr, "max=%lf, maxi=%d, maxj=%d\n", max, maxi, maxj);
fprintf(stderr, "min=%lf, mini=%d, minj=%d\n", min, mini, minj);

return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------

static void
collectmypdb	(const char *name_i, struct model *pmodel_input)
{
	FILE *fi;
	if (NULL != (fi = fopen(name_i, "r"))) {
		modelload(fi, pmodel_input);
		fclose(fi);
	} else {
		printf("problems with %s\n", name_i);
		exit(EXIT_FAILURE);
	}
	return;
}

//=============================================================================

static
void coord_extract (const struct coordinates *c, struct coordinates *o, int from, int to)
{
	int i, j, end;
	int n = c->n;
	
	end = to+1 > n? n: to+1;
		
	for (i = from, j = 0; i < end; i++) {
			o->atm[j][0] = c->atm[i][0];
			o->atm[j][1] = c->atm[i][1];
			o->atm[j][2] = c->atm[i][2];
  			j++;
 	}
 	o->n = j;
}

void mod2_CAcoord(const struct model *m, struct coordinates *c)
{
	int i, j;
	int n = m->n;
	
	for (i = 0, j = 0; i < n ; i++) {
		
		if (m->a[i].atmlabel[0] == 'C' && m->a[i].atmlabel[1] == 'A') {
  			c->atm[j][0] = m->a[i].x;
  			c->atm[j][1] = m->a[i].y;
  			c->atm[j][2] = m->a[i].z;
  			j++;
    	} 
    	if (j >= MAXATOMS) {
    		fprintf (stderr, "Number of atoms exceeded limit\n");
    		break;
		}
 	}
 	c->n = j;
}

static void 
mod2_CAcoord_resfrom_resto(const struct model *m, struct coordinates *c, int resfrom, int resto)
{
	int i, j;
	int n = m->n;
	
	for (i = 0, j = 0; i < n ; i++) {

		if (m->a[i].resnumber < resfrom || m->a[i].resnumber > resto) {
			continue;
		}
		
		if (m->a[i].atmlabel[0] == 'C' && m->a[i].atmlabel[1] == 'A') {
  			c->atm[j][0] = m->a[i].x;
  			c->atm[j][1] = m->a[i].y;
  			c->atm[j][2] = m->a[i].z;
  			j++;
    	} 
    	if (j >= MAXATOMS) {
    		fprintf (stderr, "Number of atoms exceeded limit\n");
    		break;
		}

 	}
 	
 	
 	
 	c->n = j;
}

void mod2_ALLcoord(const struct model *m, struct coordinates *c, int from, int to)
{
	int i, j;
	int n = m->n;

	for (i = 0, j = 0; i < n ; i++) {
		
		if (   m->a[i].atmnum >= from 
			&& m->a[i].atmnum <= to
			&& m->a[i].atmlabel[0] != 'H'
			) {
  			c->atm[j][0] = m->a[i].x;
  			c->atm[j][1] = m->a[i].y;
  			c->atm[j][2] = m->a[i].z;
  			j++;
    	} 
    	if (j >= MAXATOMS) {
    		fprintf (stderr, "Number of atoms exceeded limit\n");
    		break;
		}
 	}
 	c->n = j;
}

//==================================================================================

