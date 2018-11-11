#!/usr/bin/env tclsh
# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix
# @(#) FIXME: <edit a description of this sctipt>

package require Tcl 8.6
package require cmdline 1.5

set auto_noexec 1

proc dojob {input output} {
    # FIXME: write a sctipt here.
    puts $output "hello, world"
}

proc main {argv} {
    set options {
        {o.arg - "place output in file, or stdout (`-'). default is"}
        {v       "show program's version number and exit"}
    }
    set usage "\[option] \[file...]"
    set version "[::cmdline::getArgv0] 1.0.0"

    try {
        array set params [::cmdline::getoptions argv $options $usage]
    } trap {CMDLINE USAGE} {msg o} {
        puts stderr $msg
        exit 1
    }
    if {$params(v)} {
        puts $version
        exit 0
    }

    if {$params(o) == "-"} {
        set output stdout
    } elseif {[catch {open $params(o) w} output]} {
        puts stderr $output
        exit 1
    }

    set result 0

    foreach file $argv {
        if {$file == "-"} {
            set input stdin
        } elseif {[catch {open $file r} input]} {
            puts stderr $input
            set result 1
            continue
        }

        dojob $input $output

        if {$file != "-"} {close $input}
    }

    if {$params(o) != "-"} {close $output}

    exit $result
}

main $argv
