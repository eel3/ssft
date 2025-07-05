/*
 * -*- coding: utf-8-unix -*-
 * vim:fileencoding=utf-8:ff=unix
 *
 * FIXME: <edit a description of this file>
 */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#ifdef __linux__
#	ifndef _POSIX_C_SOURCE
#		define _POSIX_C_SOURCE 2
#	endif /* ndef _POSIX_C_SOURCE */
#endif /* def __linux__ */

/* C standard library */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Unix system call and library */
#include <libgen.h>
#include <unistd.h>

/* Third party library */
/* FIXME: include header files. */

/* User library */
/* FIXME: include header files. */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static const char *program_name;

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
usage(FILE * const out)
{
	assert(out != NULL);

	(void) fprintf(out, "usage: %s [-hv] [argument...]\n", program_name);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
version(void)
{
	(void) fprintf(stdout, "%s 1.0.0\n", program_name);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int
main(int argc, char *argv[])
{
	program_name = basename(argv[0]);

	int c;
	while ((c = getopt(argc, argv, "hv")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			return EXIT_SUCCESS;
		case 'v':
			version();
			return EXIT_SUCCESS;
		default:
			usage(stderr);
			return EXIT_FAILURE;
		}
	}

	if (optind >= argc) {
		usage(stderr);
		return EXIT_FAILURE;
	}

	/* FIXME: write a code here. */

	for (int i = optind; i < argc; i++) {
		(void) puts(argv[i]);
	}

	return EXIT_SUCCESS;
}
