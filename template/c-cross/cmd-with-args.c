/*
 * -*- coding: utf-8-with-signature-dos -*-
 * vim:fileencoding=utf-8:ff=dos
 *
 * FIXME: <edit a description of this file>
 */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#if defined(WIN32) || defined(WIN64)
#	if !defined(__MINGW32__) && !defined(__MINGW64__)
#		ifndef _CRT_SECURE_NO_WARNINGS
#			define _CRT_SECURE_NO_WARNINGS
#		endif /* ndef _CRT_SECURE_NO_WARNINGS */
#	endif /* !defined(__MINGW32__) && !defined(__MINGW64__) */
#endif /* defined(WIN32) || defined(WIN64) */

/* C standard library */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define STREQ(s1, s2) (((s1)[0] == (s2)[0]) && (strcmp((s1), (s2)) == 0))

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

	const char *bn;

	assert(name != NULL);

	bn = strrchr(name, PATH_SEP);
	return (bn == NULL) ? name : bn+1;
}

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
	int i;

	program_name = my_basename(argv[0]);

	while ((argc > 1) && (argv[1][0] == '-') && (argv[1][1] != '\0')) {
		const char *p = &argv[1][1];

		if (STREQ(argv[1], "--")) {
			argc--, argv++;
			break;
		}

		do switch (*p) {
		case 'h':
			usage(stdout);
			return EXIT_SUCCESS;
		case 'v':
			version();
			return EXIT_SUCCESS;
		case '-':
			if (STREQ(&p[1], "help")) {
				usage(stdout);
				return EXIT_SUCCESS;
			}
			if (STREQ(&p[1], "version")) {
				version();
				return EXIT_SUCCESS;
			}
			/*FALLTHRU*/
		default:
			usage(stderr);
			return EXIT_FAILURE;
		} while (*++p != '\0');

		argc--, argv++;
	}

	if (argc <= 1) {
		usage(stderr);
		return EXIT_FAILURE;
	}

	/* FIXME: write a code here. */

	for (i = 1; i < argc; i++) {
		(void) puts(argv[i]);
	}

	return EXIT_SUCCESS;
}
