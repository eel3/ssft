/*
 * -*- coding: utf-8-with-signature-dos -*-
 * vim:fileencoding=utf-8:ff=dos
 *
 * FIXME: <edit a description of this file>
 */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#if defined(WIN32) || defined(WIN64)
#	if !defined(__MINGW32__) && !defined(__MINGW64__)
#		ifndef _CRT_SECURE_NO_WARNINGS
#			define _CRT_SECURE_NO_WARNINGS
#		endif /* ndef _CRT_SECURE_NO_WARNINGS */
#	endif /* !defined(__MINGW32__) && !defined(__MINGW64__) */
#endif /* defined(WIN32) || defined(WIN64) */

/* C standard library */
#include <stdio.h>
#include <stdlib.h>

/* Third party library */
/* FIXME: include header files. */

/* User library */
/* FIXME: include header files. */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

int
main(int argc, char *argv[])
{
	/* FIXME: write a code here. */
	int i;

	for (i = 0; i < argc; ++i) {
		(void) puts(argv[i]);
	}

	return EXIT_SUCCESS;
}
