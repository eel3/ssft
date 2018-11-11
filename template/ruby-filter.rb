#!/usr/bin/env ruby
# encoding: utf-8
# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix
# @(#) FIXME: <edit a description of this sctipt>

require 'optparse'

output = STDOUT

OptionParser.new {|op|
  begin
    op.banner = "usage: #{op.program_name} [options] [file ...]"
    op.release = '20YY-MM-DD'   # FIXME
    op.summary_width = 80
    op.version = '1.0.0'

    op.accept(File) {|s|
      begin
        s == '-' ? STDOUT : File.open(s, 'wb')
      rescue
        raise OptionParser::InvalidArgument, s
      end
    }

    op.on('-o', '--output FILE', File, 'place output in file FILE') {|v|
      output = v
    }

    op.permute!
  rescue
    abort op.help
  end
}

retval = 0

begin
  # FIXME: write a sctipt here.
  ARGF.argv.each do |i|
    output.puts i
  end
rescue Errno::ENOENT => e
  STDERR.puts e
  retval = 1
  retry
end

output.close unless output == STDOUT

exit retval
