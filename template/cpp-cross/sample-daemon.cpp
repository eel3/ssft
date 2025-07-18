﻿// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// FIXME: <edit a description of this file>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#if defined(_WIN32) || defined(_WIN64)
#	if !defined(__MINGW32__) && !defined(__MINGW64__)
#		ifndef _CRT_SECURE_NO_WARNINGS
#			define _CRT_SECURE_NO_WARNINGS
#		endif // ndef _CRT_SECURE_NO_WARNINGS
#	endif // !defined(__MINGW32__) && !defined(__MINGW64__)
#endif // defined(_WIN32) || defined(_WIN64)

// C++ standard library
#include <cassert>
#include <chrono>
#include <csignal>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>

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

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

std::string program_name;

volatile sig_atomic_t want_to_exit { ATOMIC_FALSE };

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

std::string my_basename(std::string_view s)
{
	std::filesystem::path path { s };

	return path.empty() ? "."
	       : path.has_filename() ? path.filename().string()
	       : path.string();
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void writelog(const char * const fmt, ...)
{
	using std::chrono::system_clock;

	assert(fmt != nullptr);

	va_list args;
	va_start(args, fmt);

	std::ostringstream oss;

	auto now = system_clock::to_time_t(system_clock::now());
	auto tmp = localtime(&now);
	oss << std::put_time(tmp, "%Y-%m-%dT%H:%M:%S%z: ");

	const auto out = stderr;
	(void) fputs(oss.str().c_str(), out);
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

void usage(std::ostream& out)
{
	out << "usage: " << program_name << " [-hv]" << std::endl;
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

void trap_exit(int signum) noexcept
{
	assert((signum == SIGINT) || (signum == SIGTERM));
	(void) signum;

	want_to_exit = ATOMIC_TRUE;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void set_signal_handler() noexcept
{
	(void) signal(SIGINT,  trap_exit);
	(void) signal(SIGTERM, trap_exit);
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
	using namespace std::literals::chrono_literals;

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
	auto retval = EXIT_FAILURE;

	for (; !want_to_exit; std::this_thread::sleep_for(10ms)) {
		// FIXME: modify the code below if you need.

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
	using namespace std::string_view_literals;
	using std::cerr,
	      std::cout;

	program_name = my_basename(argv[0]);

	for (; (argc > 1) && (argv[1][0] == '-') && (argv[1][1] != '\0'); argc--, argv++) {
		const auto *p = &argv[1][1];

		if (argv[1][1] == '-') {
			p = &argv[1][2];

			if (*p == '\0') {
				argc--, argv++;
				break;
			} else if (p == "help"sv) {
				usage(cout);
				return EXIT_SUCCESS;
			} else if (p == "version"sv) {
				version();
				return EXIT_SUCCESS;
			} else {
				usage(cerr);
				return EXIT_FAILURE;
			}
			continue;
		}

		do switch (*p) {
		case 'h':
			usage(cout);
			return EXIT_SUCCESS;
		case 'v':
			version();
			return EXIT_SUCCESS;
		default:
			usage(cerr);
			return EXIT_FAILURE;
		} while (*++p != '\0');
	}

	if (argc >= 2) {
		usage(cerr);
		return EXIT_FAILURE;
	}

	info("service starting...");

	auto retval = service_main();

	notice("service stopped (exit program).");

	return retval;
}
