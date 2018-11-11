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
#	ifndef _BSD_SOURCE
#		define _BSD_SOURCE
#	endif /* ndef _BSD_SOURCE */

#	ifndef _POSIX_C_SOURCE
#		define _POSIX_C_SOURCE 199309L
#	endif /* ndef _POSIX_C_SOURCE */
#endif /* def __linux__ */

/* C standard library */
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Unix system call and library */
#include <libgen.h>
#include <syslog.h>
#include <unistd.h>

/* Third party library */
/* FIXME: include header files. */

/* User library */
/* FIXME: include header files. */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#define ATOMIC_TRUE  ((sig_atomic_t) 1)
#define ATOMIC_FALSE ((sig_atomic_t) 0)

#define MY_SYSLOG_FACILITY LOG_LOCAL7

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static const char *program_name;

static bool debug_mode = false;

static volatile sig_atomic_t want_to_exit = ATOMIC_FALSE;
static volatile sig_atomic_t want_to_restart = ATOMIC_FALSE;

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#define BZERO(p, size) ((void) memset((p), 0, (size)))
#if 0
#define NELEMS(ary)    (sizeof(ary) / sizeof((ary)[0]))
#define STREQ(s1, s2)  (((s1)[0] == (s2)[0]) && (strcmp((s1), (s2)) == 0))
#endif

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
writelog(const int pri, const char * const fmt, ...)
{
	va_list args;

	assert(fmt != NULL);

	va_start(args, fmt);

	if (debug_mode) {
		FILE * const out = stderr;
		time_t now;
		struct tm tmp;
		size_t len;
		char str[64];

		(void) fputs(program_name, out);
		(void) fputs(": ", out);

		now = time(NULL);
		tzset();
		(void) localtime_r(&now, &tmp);
		len = strftime(str, sizeof(str), "%Y-%m-%dT%H:%M:%S%z: ", &tmp);
		if (len != 0) {
			(void) fputs(str, out);
		}

		(void) vfprintf(out, fmt, args);

		(void) fputc('\n', out);
		(void) fflush(out);
	} else {
		vsyslog(pri, fmt, args);
	}

	va_end(args);
}

#define error(...)  writelog(LOG_ERR,     "<error> "   __VA_ARGS__)
#if 0
#define warn(...)   writelog(LOG_WARNING, "<warning> " __VA_ARGS__)
#endif
#define notice(...) writelog(LOG_NOTICE,  "<notice> "  __VA_ARGS__)
#define info(...)   writelog(LOG_INFO,    "<info> "    __VA_ARGS__)
#if 0
#define debug(...)  writelog(LOG_DEBUG,   "<debug> "   __VA_ARGS__)
#endif

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
usage(FILE * const out)
{
	assert(out != NULL);

	(void) fprintf(out,
	               "usage: %s [options]\n"
	               "    -d\n"
	               "     start in debug mode (work on foreground and use stderr)\n",
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
trap_exit(int signum)
{
	assert((signum == SIGINT) || (signum == SIGTERM) || (signum == SIGQUIT));
	(void) signum;

	want_to_exit = ATOMIC_TRUE;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
trap_restart(int signum)
{
	assert(signum == SIGHUP);
	(void) signum;

	want_to_restart = ATOMIC_TRUE;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static void
set_sigaction(void)
{
	struct sigaction sa;

	BZERO(&sa, sizeof(sa));
	sa.sa_flags = SA_RESTART;

	sa.sa_handler = trap_exit;
	(void) sigaction(SIGINT, &sa, NULL);
	(void) sigaction(SIGTERM, &sa, NULL);
	(void) sigaction(SIGQUIT, &sa, NULL);

	sa.sa_handler = trap_restart;
	(void) sigaction(SIGHUP, &sa, NULL);
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
restart_service(void)
{
	/* FIXME: modify the code below. */

	stop_service();

	return start_service();
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
	static const struct timespec period_nsec = { 0, 10000000 };     /* 10msec */

	int retval;

	set_sigaction();

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
	retval = EXIT_FAILURE;

	for (; !want_to_exit; (void) nanosleep(&period_nsec, NULL)) {
		/* FIXME: modify the code below if you need. */

		if (want_to_restart) {
			want_to_restart = ATOMIC_FALSE;

			info("service restarting...");

			if (!restart_service()) {
				error("failed to restart service.");
				goto DONE;
			}

			notice("service restarted.");
		}

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
	int c, retval;

	program_name = basename(argv[0]);

	while ((c = getopt(argc, argv, "dhv")) != -1) {
		switch (c) {
		case 'd':
			debug_mode = true;
			break;
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

	if (optind < argc) {
		usage(stderr);
		return EXIT_FAILURE;
	}

	retval = EXIT_FAILURE;

	if (!debug_mode) {
		openlog(program_name, LOG_PID | LOG_NDELAY, MY_SYSLOG_FACILITY);
		errno = 0;
		if (daemon(0, 0) < 0) {
			error("failed to become daemon: %m.");
			goto DONE;
		}
	}

	info("service starting...");

	retval = service_main();

DONE:
	notice("service stopped (exit program).");

	if (!debug_mode) {
		closelog();
	}

	return retval;
}
