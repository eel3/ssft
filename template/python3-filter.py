#!/usr/bin/env python3
# encoding: utf-8
# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix
# @(#) FIXME: <edit a description of this sctipt>

import argparse
import sys


def eprint(*args, **keywords):
    print(sys.argv[0] + ':', *args, file=sys.stderr, **keywords)


def do_job(istream, ostream, opts):
    # FIXME: write a sctipt here.
    ostream.write(b'hello, world\n')


def parse_args():
    parser = argparse.ArgumentParser(description=
            'FIXME: <edit a description of this sctipt>')

    parser.add_argument('files', metavar='file', nargs='*', help='input file')
    parser.add_argument('-o', '--output', metavar='file', nargs=1,
                        type=argparse.FileType('wb'), default=[sys.stdout.buffer],
                        help='place output in file')
    parser.add_argument('-v', '--version', action='version',
                        version='%(prog)s 1.0.0')

    return parser.parse_known_args()


def main():
    args = parse_args()

    files = args[0].files
    if len(files) <= 0:
        files.append('-')

    ostream = args[0].output[0]
    retval = 0

    for f in files:
        try:
            if f == '-':
                do_job(sys.stdin, ostream, args[0])
            else:
                with open(f, 'rb') as istream:
                    do_job(istream, ostream, args[0])
        except Exception as e:
            eprint(e)
            retval = 1

    sys.exit(retval)

if __name__ == '__main__':
    main()
