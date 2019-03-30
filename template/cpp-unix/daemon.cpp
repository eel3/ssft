// -*- coding: utf-8-unix -*-
// vim:fileencoding=utf-8:ff=unix
//
// FIXME: <edit a description of this file>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#ifdef __linux__
#	ifndef _BSD_SOURCE
#		define _BSD_SOURCE
#	endif /* ndef _BSD_SOURCE */

#	ifndef _DEFAULT_SOURCE
#		define _DEFAULT_SOURCE
#	endif /* ndef _DEFAULT_SOURCE */

#	ifndef _POSIX_C_SOURCE
#		define _POSIX_C_SOURCE 199309L
#	endif /* ndef _POSIX_C_SOURCE */
#endif /* def __linux__ */

// C++ standard library
#include <cassert>
#include <cerrno>
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

// Unix system call and library
#include <libgen.h>
#include <signal.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

// C++ third party library
// FIXME: include header files.

// C third party library
extern "C" {
// FIXME: include header files.
}

// C++ user library
// FIXME: include header files.

// C user library
extern "C" {
// FIXME: include header files.
}

namespace {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

constexpr sig_atomic_t ATOMIC_TRUE  { static_cast<sig_atomic_t>(1) };
constexpr sig_atomic_t ATOMIC_FALSE { static_cast<sig_atomic_t>(0) };

constexpr int MY_SYSLOG_FACILITY { LOG_LOCAL7 };

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

std::string program_name;

bool debug_mode { false };

volatile sig_atomic_t want_to_exit    { ATOMIC_FALSE };
volatile sig_atomic_t want_to_restart { ATOMIC_FALSE };

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#define BZERO(p, size) ((void) memset((p), 0, (size)))

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void writelog(const int pri, const char * const fmt, ...)
{
	using std::chrono::system_clock;

	assert(fmt != nullptr);

	va_list args;
	va_start(args, fmt);

	if (debug_mode) {
		std::ostringstream oss;

		oss << program_name << ": ";

		auto now = system_clock::to_time_t(system_clock::now());
		tzset();
		struct tm tmp;
		(void) localtime_r(&now, &tmp);
		oss << std::put_time(&tmp, "%Y-%m-%dT%H:%M:%S%z: ");

		const auto out = stderr;
		(void) fputs(oss.str().c_str(), out);
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

void usage(std::ostream &out)
{
	out << "usage: " << program_name << " [options]\n"
	    << "    -d\n"
	    << "     start in debug mode (work on foreground and use stderr)"
	    << std::endl;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void version()
{
	std::cout << program_name << " 1.0.0" << std::endl;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void trap_exit(int signum)
{
	assert((signum == SIGINT) || (signum == SIGTERM) || (signum == SIGQUIT));
	(void) signum;

	want_to_exit = ATOMIC_TRUE;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void trap_restart(int signum)
{
	assert(signum == SIGHUP);
	(void) signum;

	want_to_restart = ATOMIC_TRUE;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void set_sigaction()
{
	struct sigaction sa;

	BZERO(&sa, sizeof(sa));
	sa.sa_flags = SA_RESTART;

	sa.sa_handler = trap_exit;
	(void) sigaction(SIGINT, &sa, nullptr);
	(void) sigaction(SIGTERM, &sa, nullptr);
	(void) sigaction(SIGQUIT, &sa, nullptr);

	sa.sa_handler = trap_restart;
	(void) sigaction(SIGHUP, &sa, nullptr);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

bool setup_submodules()
{
	// FIXME: write a code here.

	return true;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void teardown_submodules()
{
	// FIXME: write a code here.
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

bool start_service()
{
	// FIXME: write a code here.

	return true;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void stop_service()
{
	// FIXME: write a code here.
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

bool restart_service()
{
	// FIXME: modify the code below.

	stop_service();

	return start_service();
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

bool do_job()
{
	// FIXME: write a code here.

	return true;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int service_main()
{
	using std::chrono::milliseconds;
	using std::this_thread::sleep_for;

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
	auto retval = EXIT_FAILURE;

	for (milliseconds timeout { 10 }; !want_to_exit; sleep_for(timeout)) {
		// FIXME: modify the code below if you need.

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

} // namespace

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
	using std::cerr;

	program_name = basename(argv[0]);

	int c;
	while ((c = getopt(argc, argv, "dhv")) != -1) {
		switch (c) {
		case 'd':
			debug_mode = true;
			break;
		case 'h':
			usage(std::cout);
			return EXIT_SUCCESS;
		case 'v':
			version();
			return EXIT_SUCCESS;
		default:
			usage(cerr);
			return EXIT_FAILURE;
		}
	}

	if (optind < argc) {
		usage(cerr);
		return EXIT_FAILURE;
	}

	auto retval = EXIT_FAILURE;

	if (!debug_mode) {
		openlog(program_name.c_str(), LOG_PID | LOG_NDELAY, MY_SYSLOG_FACILITY);
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
