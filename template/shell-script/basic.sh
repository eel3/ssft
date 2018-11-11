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
    echo "usage: $progname [-hv] [file ...]" 1>&2
    exit $1
}

# version (no parameter)
version() {
    echo "$progname $version" 1>&2
    exit 0
}

# main routine

opt=
while getopts 'ho:v' opt; do
    case $opt in
    h)      usage 0 ;;
    v)      version ;;
    \?)     usage 1 ;;
    esac
done
shift $(($OPTIND - 1))

# FIXME: write a sctipt here.
if [ $# = 0 ]; then
    echo hello, world
else
    printf %s\\n ${@+"$@"}
fi
