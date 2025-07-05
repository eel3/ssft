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
#include <algorithm>
#include <cstdlib>
#include <filesystem>
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
	out << "usage: " << program_name << " [-hv] [argument...]" << std::endl;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

void version()
{
	std::cout << program_name << " 1.0.0" << std::endl;
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

	if (argc <= 1) {
		usage(cerr);
		return EXIT_FAILURE;
	}

	// FIXME: write a code here.

	std::for_each(&argv[1], &argv[argc], [](const auto *arg) {
		std::cout << arg << std::endl;
	});

	return EXIT_SUCCESS;
}
