#!/bin/sh
# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix
# @(#) FIXME: <edit a description of this sctipt>

set -u
umask 0022
IFS=$(printf ' \t\n_'); IFS=${IFS%_}
PATH=/bin:/usr/bin
export IFS LC_ALL=C LANG=C PATH

readonly progname=${0##*/}
readonly version=1.0.0

# usage <exit-code>
usage() {
    echo "usage: $progname [-hv] [-o output] [file ...]" 1>&2
    exit $1
}

# version (no parameter)
version() {
    echo "$progname $version" 1>&2
    exit 0
}

# error <message>
error() {
    echo "$progname:" "$@" 1>&2
    exit 1
}

# main routine

output=

opt=
while getopts 'ho:v' opt; do
    case $opt in
    h)      usage 0 ;;
    o)      output=$OPTARG ;;
    v)      version ;;
    \?)     usage 1 ;;
    esac
done
shift $(($OPTIND - 1))

if [ -n "$output" -a "$output" != - ]; then
    { exec >"$output"; } 2>/dev/null
    [ $? -eq 0 ] || error "$output: cannot open"
fi

# FIXME: write a sctipt here.
if [ $# = 0 ]; then
    echo hello, world
else
    printf %s\\n ${@+"$@"}
fi
