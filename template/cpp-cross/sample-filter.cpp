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
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

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

#define STREQ(s1, s2) (((s1)[0] == (s2)[0]) && (std::strcmp((s1), (s2)) == 0))

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

inline std::string trim_right(const std::string& s, const std::string& chars = "\t\n\v\f\r ")
{
	auto rpos = s.find_last_not_of(chars);

	return (rpos == std::string::npos) ? "" : s.substr(0, rpos + 1);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

std::string my_basename(const char * const s)
{
	using std::string;

	static const string DOT { "." };
	static const string SEP { "/" };
#if defined(_WIN32) || defined(_WIN64)
	static const string WSEP { "\\" };
	static const string SEPS { SEP + WSEP };
#else // defined(_WIN32) || defined(_WIN64)
	static const string SEPS { SEP };
#endif // defined(_WIN32) || defined(_WIN64)

	if (s == nullptr) {
		return DOT;
	}

	string t = s;

	if (t.empty()) {
		return DOT;
	}

	const auto path = trim_right(t, SEPS);
	if (path.empty()) {
		return string { t.back() };
	}

	auto pos = path.find_last_of(SEPS);
	return (pos == string::npos) ? path : path.substr(pos + 1);
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
	using std::cerr;
	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios;
	using std::string;

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
#endif // defined(_WIN32) || defined(_WIN64)

	string output { "-" };

	for (; (argc > 1) && (argv[1][0] == '-') && (argv[1][1] != '\0'); argc--, argv++) {
		if (argv[1][1] == '-') {
			const auto *p = &argv[1][2];

			if (*p == '\0') {
				argc--, argv++;
				break;
			} else if (STREQ(p, "help")) {
				usage(cout);
				return EXIT_SUCCESS;
			} else if (STREQ(p, "output")) {
				if (argc < 3) {
					usage(cerr);
					return EXIT_FAILURE;
				} else {
					argc--, argv++;
					output = argv[1];
				}
			} else if (STREQ(p, "version")) {
				version();
				return EXIT_SUCCESS;
			} else {
				usage(cerr);
				return EXIT_FAILURE;
			}
			continue;
		}

		const auto *p = &argv[1][1];

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

	if (argc <= 1) {
		do_job(cin, out);
	} else {
		std::for_each(&argv[1], &argv[argc], [&out, &retval](const auto *s) {
			string arg { s };

			if (arg == "-") {
				do_job(std::cin, out);
			} else {
				std::ifstream fin(arg, ios::binary);
				if (!fin) {
					std::cerr << program_name << ": " << arg << ": cannot open" << endl;
					retval = EXIT_FAILURE;
					return;
				}
				do_job(fin, out);
			}
		});
	}

	return retval;
}
