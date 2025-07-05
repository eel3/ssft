// -*- coding: utf-8-with-signature-dos -*-
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
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

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
#	include <cstdio>
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

void usage(std::ostream& out)
{
	out << "usage: " << program_name << " [-hv] [-o output] [file...]" << std::endl;
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
	using namespace std::string_view_literals;
	using std::cerr,
	      std::cin,
	      std::cout,
	      std::endl,
	      std::ios,
	      std::strerror;

	program_name = my_basename(argv[0]);

#if defined(_WIN32) || defined(_WIN64)
	errno = 0;
	if (_setmode(STDIN_FILENO, O_BINARY) == -1) {
		std::perror("_setmode");
		return EXIT_FAILURE;
	}
	errno = 0;
	if (_setmode(STDOUT_FILENO, O_BINARY) == -1) {
		std::perror("_setmode");
		return EXIT_FAILURE;
	}
#endif // defined(_WIN32) || defined(_WIN64)

	auto output = "-"sv;

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
			} else if (p == "output"sv) {
				if (argc < 3) {
					usage(cerr);
					return EXIT_FAILURE;
				} else {
					argc--, argv++;
					output = argv[1];
				}
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
		case 'o':
			if (p[1] != '\0') {
				output = &p[1];
				p += output.size();
			} else if (argc < 3) {
				usage(cerr);
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
			usage(cerr);
			return EXIT_FAILURE;
		} while (*++p != '\0');
	}

	std::ofstream fout;
	auto& out = [&]() mutable -> std::ostream& {
		if (output == "-") {
			return cout;
		} else {
			errno = 0;
			fout.open(output.data(), ios::binary);
			if (!fout) {
				cerr << program_name << ": " << output << ": " << strerror(errno) << endl;
				std::exit(EXIT_FAILURE);
			}
			return fout;
		}
	}();

	auto retval = EXIT_SUCCESS;

	if (argc <= 1) {
		do_job(cin, out);
	} else {
		for (auto i = 1; i < argc; i++) {
			if (argv[i] == "-"sv) {
				do_job(cin, out);
			} else {
				errno = 0;
				std::ifstream fin(argv[i], ios::binary);
				if (!fin) {
					cerr << program_name << ": " << argv[i] << ": " << strerror(errno) << endl;
					retval = EXIT_FAILURE;
					continue;
				}
				do_job(fin, out);
			}
		}
	}

	return retval;
}
