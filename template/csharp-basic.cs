// -*- coding: utf-8-with-signature-unix -*-
// vim:fileencoding=utf-8:ff=unix
//
// FIXME: <edit a description of this file>

using System;
using System.IO;

// FIXME
class AppMain
{
	static void Main(string[] args)
	{
		// FIXME: write a code here.
		Console.WriteLine(Path.GetFileName(Environment.GetCommandLineArgs()[0]));
		Array.ForEach(args, arg => Console.WriteLine(arg));
	}
}
