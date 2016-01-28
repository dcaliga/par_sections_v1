static char const cvsid[] = "$Id: main.c,v 2.1 2005/06/14 22:16:49 jls Exp $";

/*
 * Copyright 2005 SRC Computers, Inc.  All Rights Reserved.
 *
 *	Manufactured in the United States of America.
 *
 * SRC Computers, Inc.
 * 4240 N Nevada Avenue
 * Colorado Springs, CO 80907
 * (v) (719) 262-0213
 * (f) (719) 262-0223
 *
 * No permission has been granted to distribute this software
 * without the express permission of SRC Computers, Inc.
 *
 * This program is distributed WITHOUT ANY WARRANTY OF ANY KIND.
 */

#include <libmap.h>
#include <stdlib.h>

#define SZ 65536


void subr (int64_t A[], int64_t B[], int64_t C[], int64_t D[], int64_t Out1[],
            int64_t Out2[], int N0, int N1, int64_t *time, int mapnum);

int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, num0, num1;
    int64_t *A, *B, *C, *D, *Out1, *Out2;
    int64_t tm;
    int mapnum = 0;

 int64_t i64;

    if ((res_map = fopen ("res_map", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_map'\n");
        exit (1);
        }

    if ((res_cpu = fopen ("res_cpu", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_cpu'\n");
        exit (1);
        }

    if (argc < 3) {
	fprintf (stderr, "need two elements counts (each up to %d) as args\n", SZ);
	exit (1);
	}

    if (sscanf (argv[1], "%d", &num0) < 1) {
	fprintf (stderr, "need two elements counts (each up to %d) as args\n", SZ);
	exit (1);
	}

    if (sscanf (argv[2], "%d", &num1) < 1) {
	fprintf (stderr, "need two elements counts (each up to %d) as args\n", SZ);
	exit (1);
	}

    if ((num0 > SZ) || (num1 > SZ)) {
	fprintf (stderr, "need two elements counts (each up to %d) as args\n", SZ);
	exit (1);
	}

    A    = (int64_t*) malloc (num0 * sizeof (int64_t));
    B    = (int64_t*) malloc (num0 * sizeof (int64_t));
    C    = (int64_t*) malloc (num1 * sizeof (int64_t));
    D    = (int64_t*) malloc (num1 * sizeof (int64_t));
    Out1 = (int64_t*) malloc (num0 * sizeof (int64_t));
    Out2 = (int64_t*) malloc (num1 * sizeof (int64_t));

    srandom (99);

    for (i=0; i<num0; i++) {
        A[i] = random ();
        B[i] = random ();
	}

    for (i=0; i<num1; i++) {
        C[i] = random ();
        D[i] = random ();
	}

    map_allocate (1);

    // call the MAP routine
    subr (A, B, C, D, Out1, Out2, num0, num1, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    for (i=0; i<num0; i++) {
        fprintf (res_map, "%lld\n", Out1[i]);
        fprintf (res_cpu, "%lld\n", A[i]+B[i]);
	}

    for (i=0; i<num1; i++) {
        fprintf (res_map, "%lld\n", Out2[i]);
        fprintf (res_cpu, "%lld\n", C[i]*D[i]);
	}

    map_free (1);

    exit(0);
    }
