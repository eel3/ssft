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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Unix system call and library */
#include <libgen.h>
#include <unistd.h>

/* Third party library */
/* FIXME: include header files. */

/* User library */
/* FIXME: include header files. */

#if defined(_WIN32) || defined(_WIN64)
#	include <fcntl.h>
#	include <io.h>
#	ifndef STDIN_FILENO
#		define STDIN_FILENO 0
#	endif
#	ifndef STDOUT_FILENO
#		define STDOUT_FILENO 1
#	endif
#endif /* defined(_WIN32) || defined(_WIN64) */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static const char *program_name;

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#if 0
#define BZERO(p, size) ((void) memset((p), 0, (size)))
#define NELEMS(ary)    (sizeof(ary) / sizeof((ary)[0]))
#endif
#define STREQ(s1, s2)  (((s1)[0] == (s2)[0]) && (strcmp((s1), (s2)) == 0))

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
usage(FILE * const out)
{
	assert(out != NULL);

	(void) fprintf(out,
	               "usage: %s [options] [file...]\n"
	               "    -o FILE\n"
	               "     place output in file FILE\n",
	               program_name);
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

static void
do_job(FILE * const in, FILE * const out)
{
	assert((in != NULL) && (out != NULL));

	/* FIXME: write a code here. */
	(void) in;
	(void) fputs("hello, world\n", out);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int
main(int argc, char *argv[])
{
	program_name = basename(argv[0]);

#if defined(_WIN32) || defined(_WIN64)
	errno = 0;
	if (_setmode(STDIN_FILENO, O_BINARY) == -1) {
		perror("_setmode");
		return EXIT_FAILURE;
	}
	errno = 0;
	if (_setmode(STDOUT_FILENO, O_BINARY) == -1) {
		perror("_setmode");
		return EXIT_FAILURE;
	}
#endif /* defined(_WIN32) || defined(_WIN64) */

	const char *output = "-";

	int c;
	while ((c = getopt(argc, argv, "ho:v")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			return EXIT_SUCCESS;
		case 'o':
			output = optarg;
			break;
		case 'v':
			version();
			return EXIT_SUCCESS;
		default:
			usage(stderr);
			return EXIT_FAILURE;
		}
	}

	FILE *out;

	if (STREQ(output, "-")) {
		out = stdout;
	} else if (errno = 0, (out = fopen(output, "wb")) == NULL) {
		perror(output);
		return EXIT_FAILURE;
	} else {
		/*EMPTY*/
	}

	int retval = EXIT_SUCCESS;

	if (optind >= argc) {
		do_job(stdin, out);
	} else {
		for (int i = optind; i < argc; i++) {
			FILE *in;

			if (STREQ(argv[i], "-")) {
				in = stdin;
			} else if (errno = 0, (in = fopen(argv[i], "rb")) == NULL) {
				perror(argv[i]);
				retval = EXIT_FAILURE;
				continue;
			} else {
				/*EMPTY*/
			}

			do_job(in, out);

			if (in != stdin) {
				(void) fclose(in);
			}
		}
	}

	if (out != stdout) {
		(void) fclose(out);
	}

	return retval;
}
