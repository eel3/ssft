// -*- coding: utf-8-unix -*-
// vim:fileencoding=utf-8:ff=unix
//
// FIXME: <edit a description of this file>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

// Objective-C library
#import <Foundation/Foundation.h>

// Objective-C third party library
// FIXME: import header files.

// Objective-C user library
// FIXME: import header files.

// C++ standard library
#include <algorithm>
#include <iostream>

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

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int main(int argc, char *argv[]) {
    @autoreleasepool {
        // FIXME: write a code here.
        std::for_each(&argv[0], &argv[argc], [] (char *arg) {
            std::cout << arg << std::endl;
        });
    }
}
