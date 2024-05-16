// -*- coding: utf-8-unix -*-
// vim:fileencoding=utf-8:ff=unix
//
// FIXME: <edit a description of this file>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#ifdef __linux__
#	ifndef _POSIX_C_SOURCE
#		define _POSIX_C_SOURCE 2
#	endif // ndef _POSIX_C_SOURCE
#endif // def __linux__

// C++ standard library
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

// Unix system call and library
#include <libgen.h>
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

#if defined(_WIN32) || defined(_WIN64)
#	include <cerrno>
#	include <fcntl.h>
#	include <io.h>
#	ifndef STDIN_FILENO
#		define STDIN_FILENO 0
#	endif
#	ifndef STDOUT_FILENO
#		define STDOUT_FILENO 1
#	endif
#endif // defined(_WIN32) || defined(_WIN64)

namespace {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

std::string program_name;

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void usage(std::ostream& out)
{
	out << "usage: " << program_name << " [options] [file...]\n"
	    << "    -o FILE\n"
	    << "     place output in file FILE" << std::endl;
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

void do_job(std::istream& /* in */, std::ostream& out)
{
	// FIXME: write a code here.
	out << "hello, world" << std::endl;
}

} // namespace

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
	using std::cerr;
	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios;
	using std::string;

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
#endif // defined(_WIN32) || defined(_WIN64)

	string output { "-" };

	int c;
	while ((c = getopt(argc, argv, "ho:v")) != -1) {
		switch (c) {
		case 'h':
			usage(cout);
			return EXIT_SUCCESS;
		case 'o':
			output = optarg;
			break;
		case 'v':
			version();
			return EXIT_SUCCESS;
		default:
			usage(cerr);
			return EXIT_FAILURE;
		}
	}

	auto use_stdout = (output == "-");
	std::ofstream fout;
	if (!use_stdout) {
		fout.open(output, ios::binary);
		if (!fout) {
			cerr << program_name << ": " << output << ": cannot open" << endl;
			return EXIT_FAILURE;
		}
	}
	std::ostream& out = use_stdout ? cout : fout;

	auto retval = EXIT_SUCCESS;

	if (optind >= argc) {
		do_job(cin, out);
	} else {
		std::for_each(&argv[optind], &argv[argc], [&out, &retval](const auto *s) {
			string arg { s };

			if (arg == "-") {
				do_job(cin, out);
			} else {
				std::ifstream fin(arg, ios::binary);
				if (!fin) {
					cerr << program_name << ": " << arg << ": cannot open" << endl;
					retval = EXIT_FAILURE;
					return;
				}
				do_job(fin, out);
			}
		});
	}

	return retval;
}
