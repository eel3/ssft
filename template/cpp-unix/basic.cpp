// -*- coding: utf-8-unix -*-
// vim:fileencoding=utf-8:ff=unix
//
// FIXME: <edit a description of this file>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

// C++ standard library
#include <algorithm>
#include <iostream>

// Unix system call and library
// FIXME: include header files.

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

// FIXME: write a code here.

} // namespace

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
	// FIXME: write a code here.
	std::for_each(&argv[0], &argv[argc], [](const auto *arg) {
		std::cout << arg << std::endl;
	});
}
