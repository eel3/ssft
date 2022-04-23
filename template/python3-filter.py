#!/usr/bin/env python3
# encoding: utf-8
# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix
# @(#) FIXME: <edit a description of this sctipt>
"""FIXME: <edit a description of this sctipt>.
"""

from __future__ import annotations

import argparse
import os
import sys

from typing import Any, BinaryIO, Final, NoReturn

progname: Final[str] = os.path.basename(sys.argv[0])


def eprint(*args: Any, **keywords: Any) -> None:
    """Wrapper function of print() (for error messages).

    Args:
        *args (tuple): Variable length argument list.
        **keywords (dict[str, Any]): Arbitrary keyword arguments.
    """
    print(progname + ':', *args, file=sys.stderr, **keywords)


def do_job(istream: BinaryIO,
           ostream: BinaryIO,
           opts: argparse.Namespace) -> None:
    """Do a job.

    Args:
        istream (BinaryIO): Input binary IO stream.
        ostream (BinaryIO): Output binary IO stream.
        opts (argparse.Namespace): Option parameters.
    """
    # FIXME: write a sctipt here.
    ostream.write(b'hello, world\n')


def parse_args() -> tuple[argparse.Namespace, list[str]]:
    """Parse CLI arguments.

    Returns:
        tuple[argparse.Namespace, list[str]]: Results of argument parsing.
    """
    parser = argparse.ArgumentParser(description=
            'FIXME: <edit a description of this sctipt>')

    parser.add_argument('files', metavar='file', nargs='*', help='input file')
    parser.add_argument('-o', '--output', metavar='file', nargs=1,
                        type=argparse.FileType('wb'), default=[sys.stdout.buffer],
                        help='place output in file')
    parser.add_argument('-v', '--version', action='version',
                        version='%(prog)s 1.0.0')

    return parser.parse_known_args()


def main() -> NoReturn:
    """Main routine function.
    """
    args = parse_args()

    files = args[0].files
    if len(files) <= 0:
        files.append('-')

    ostream = args[0].output[0]
    retval = 0

    for f in files:
        try:
            if f == '-':
                do_job(sys.stdin.buffer, ostream, args[0])
            else:
                with open(f, 'rb') as istream:
                    do_job(istream, ostream, args[0])
        except Exception as e:
            eprint(e)
            retval = 1

    sys.exit(retval)


if __name__ == '__main__':
    main()
