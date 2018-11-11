// -*- coding: utf-8-unix -*-
// vim:fileencoding=utf-8:ff=unix
//
// FIXME: <edit a description of this file>

package main

import (
	"flag"
	"fmt"
	"os"
	"path/filepath"
)

const (
	exit_success = iota // EXIT_SUCCESS
	exit_failure        // EXIT_FAILURE
)

func doJob(in *os.File, out *os.File) {
	// FIXME: write a code here.
	fmt.Fprintln(out, "hello, world")
}

func doJobFromFile(infile string, out *os.File) error {
	var in *os.File

	if infile == "-" {
		in = os.Stdin
	} else {
		var err error
		in, err = os.Open(infile)
		if err != nil {
			return err
		}
		defer in.Close()
	}

	doJob(in, out)
	return nil
}

// Main routine.
func main() {
	flag.Usage = func() {
		fmt.Fprintf(os.Stderr, "usage: %s [options] [file ...]\n", filepath.Base(os.Args[0]))
		flag.PrintDefaults()
	}
	output := flag.String("o", "-", "place output in file, or stdout (`-')")
	version := flag.Bool("v", false, "show program's version number and exit")
	flag.Parse()

	if *version {
		fmt.Fprintf(os.Stderr, "%s 1.0.0\n", filepath.Base(os.Args[0]))
		os.Exit(exit_success)
	}

	var out *os.File
	if *output == "-" {
		out = os.Stdout
	} else {
		var err error
		out, err = os.OpenFile(*output, os.O_CREATE|os.O_WRONLY, 0644)
		if err != nil {
			fmt.Println(err)
			os.Exit(exit_failure)
		}
		defer out.Close()
	}

	retval := exit_success

	if flag.NArg() <= 0 {
		doJob(os.Stdin, out)
	} else {
		for i := 0; i < flag.NArg(); i++ {
			err := doJobFromFile(flag.Arg(i), out)
			if err != nil {
				fmt.Println(err)
				retval = exit_failure
			}
		}
	}

	os.Exit(retval)
}
