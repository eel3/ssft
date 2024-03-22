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
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>

/* Third party library */
/* FIXME: include header files. */

/* User library */
/* FIXME: include header files. */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#define ATOMIC_TRUE  ((sig_atomic_t) 1)
#define ATOMIC_FALSE ((sig_atomic_t) 0)

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static const char *program_name;

static volatile sig_atomic_t want_to_exit = ATOMIC_FALSE;

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
writelog(const char * const fmt, ...)
{
	assert(fmt != NULL);

	FILE * const out = stderr;
	va_list args;

	va_start(args, fmt);

	(void) fputs(program_name, out);
	(void) fputs(": ", out);

	time_t now = time(NULL);
	struct tm *tmp = localtime(&now);
	char str[64];

	size_t len = strftime(str, sizeof(str), "%Y-%m-%dT%H:%M:%S%z: ", tmp);
	if (len != 0) {
		(void) fputs(str, out);
	}

	(void) vfprintf(out, fmt, args);

	(void) fputc('\n', out);
	(void) fflush(out);

	va_end(args);
}

#define error(...)  writelog("<error> "   __VA_ARGS__)
#if 0
#define warn(...)   writelog("<warning> " __VA_ARGS__)
#endif
#define notice(...) writelog("<notice> "  __VA_ARGS__)
#define info(...)   writelog("<info> "    __VA_ARGS__)
#if 0
#define debug(...)  writelog("<debug> "   __VA_ARGS__)
#endif

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
usage(FILE * const out)
{
	assert(out != NULL);

	(void) fprintf(out, "usage: %s [-hv]\n", program_name);
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
trap_exit(int signum)
{
	assert((signum == SIGINT) || (signum == SIGTERM));
	(void) signum;

	want_to_exit = ATOMIC_TRUE;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
set_signal_handler(void)
{
	(void) signal(SIGINT,  trap_exit);
	(void) signal(SIGTERM, trap_exit);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static bool
setup_submodules(void)
{
	/* FIXME: write a code here. */

	return true;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
teardown_submodules(void)
{
	/* FIXME: write a code here. */
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static bool
start_service(void)
{
	/* FIXME: write a code here. */

	return true;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
stop_service(void)
{
	/* FIXME: write a code here. */
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static bool
do_job(void)
{
	/* FIXME: write a code here. */

	return true;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static int
service_main(void)
{
	static const struct timespec period_nsec = { .tv_nsec = 10000000 };     /* 10msec */

	set_signal_handler();

	if (!setup_submodules()) {
		error("failed to setup submodules.");
		return EXIT_FAILURE;
	}
	if (!start_service()) {
		error("failed to start service.");
		teardown_submodules();
		return EXIT_FAILURE;
	}

	notice("service started.");
	int retval = EXIT_FAILURE;

	for (; !want_to_exit; (void) thrd_sleep(&period_nsec, NULL)) {
		/* FIXME: modify the code below if you need. */

		if (!do_job()) {
			error("failed to continue service.");
			goto DONE;
		}
	}

	retval = EXIT_SUCCESS;
	notice("catch signal, start exit process.");

DONE:
	stop_service();
	teardown_submodules();

	return retval;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int
main(int argc, char *argv[])
{
	program_name = my_basename(argv[0]);

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
		case 'v':
			version();
			return EXIT_SUCCESS;
		default:
			usage(stderr);
			return EXIT_FAILURE;
		} while (*++p != '\0');
	}

	if (argc >= 2) {
		usage(stderr);
		return EXIT_FAILURE;
	}

	info("service starting...");

	int retval = service_main();

	notice("service stopped (exit program).");

	return retval;
}
