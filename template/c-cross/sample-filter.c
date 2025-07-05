/*
 * -*- coding: utf-8-with-signature-dos -*-
 * vim:fileencoding=utf-8:ff=dos
 *
 * FIXME: <edit a description of this file>
 */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#if defined(_WIN32) || defined(_WIN64)
#	if !defined(__MINGW32__) && !defined(__MINGW64__)
#		ifndef _CRT_SECURE_NO_WARNINGS
#			define _CRT_SECURE_NO_WARNINGS
#		endif /* ndef _CRT_SECURE_NO_WARNINGS */
#	endif /* !defined(__MINGW32__) && !defined(__MINGW64__) */
#endif /* defined(_WIN32) || defined(_WIN64) */

/* C standard library */
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static const char *
my_basename(const char * const name)
{
#if defined(_WIN32) || defined(_WIN64)
#	define PATH_SEP '\\'
#else /* defined(_WIN32) || defined(_WIN64) */
#	define PATH_SEP '/'
#endif /* defined(_WIN32) || defined(_WIN64) */

	assert(name != NULL);

	const char *bn = strrchr(name, PATH_SEP);
	return (bn == NULL) ? name : bn+1;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
usage(FILE * const out)
{
	assert(out != NULL);

	(void) fprintf(out, "usage: %s [-hv] [-o output] [file...]\n", program_name);
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
	program_name = my_basename(argv[0]);

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

	for (; (argc > 1) && (argv[1][0] == '-') && (argv[1][1] != '\0'); argc--, argv++) {
		const char *p = &argv[1][1];

		if (argv[1][1] == '-') {
			p = &argv[1][2];

			if (*p == '\0') {
				argc--, argv++;
				break;
			} else if (STREQ(p, "help")) {
				usage(stdout);
				return EXIT_SUCCESS;
			} else if (STREQ(p, "output")) {
				if (argc < 3) {
					usage(stderr);
					return EXIT_FAILURE;
				} else {
					argc--, argv++;
					output = argv[1];
				}
			} else if (STREQ(p, "version")) {
				version();
				return EXIT_SUCCESS;
			} else {
				usage(stderr);
				return EXIT_FAILURE;
			}
			continue;
		}

		do switch (*p) {
		case 'h':
			usage(stdout);
			return EXIT_SUCCESS;
		case 'o':
			if (p[1] != '\0') {
				output = &p[1];
				p += strlen(output);
			} else if (argc < 3) {
				usage(stderr);
				return EXIT_FAILURE;
			} else {
				argc--, argv++;
				output = argv[1];
			}
			break;
		case 'v':
			version();
			return EXIT_SUCCESS;
		default:
			usage(stderr);
			return EXIT_FAILURE;
		} while (*++p != '\0');
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

	if (argc <= 1) {
		do_job(stdin, out);
	} else {
		for (int i = 1; i < argc; i++) {
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
