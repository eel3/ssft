#!/usr/bin/env perl
# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix
# @(#) FIXME: <edit a description of this sctipt>

=head1 DESCRIPTION

brief   FIXME: <edit a description of this sctipt>
author  # FIXME
date    20YY-MM-DD  # FIXME

=head1 SYNOPSIS

  perl5-script.pl [option] [file...]    # FIXME

  -o, --output <FILE>
    place output in file FILE

=cut

use 5.026;
use strict;
use warnings;

use Getopt::Long qw/:config auto_help bundling no_ignore_case posix_default/;
use Pod::Usage qw/pod2usage/;

sub error {
    say STDERR @_;
    exit 1;
}

sub main {
    GetOptions(
        \my %opt, qw/
        output|o=s
        version|v
    /) or pod2usage 1;

    if (exists $opt{version}) {
        say STDERR "$0 1.0.0";
        exit;
    }

    my $ostream = *STDOUT;
    if (exists $opt{output} and $opt{output} ne '-') {
        open $ostream, '>', $opt{output}
            or error("$0: $opt{output}: cannot open");
    }

    # FIXME: write a sctipt here.
    my $retval = 0;
    local $/;
    local $!;

    for ($! = 0; <>; $! = 0) {
        $retval = 1 unless $! == 0;
        say $ostream 'hello, world';
    }
    $retval = 1 unless $! == 0;

    close $ostream unless $ostream eq *STDOUT;

    exit $retval;
}

main();
