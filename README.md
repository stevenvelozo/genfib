  ____ _____ _   _ _____ ___ ____
 / ___| ____| \ | |  ___|_ _| __ )
| |  _|  _| |  \| | |_   | ||  _ \
| |_| | |___| |\  |  _|  | || |_) |
 \____|_____|_| \_|_|   |___|____/                                version 0.1

 =============================================================================

This application generates a 2 dimensional table of numbers based on the
Fibonacci sequence and a modulus table for each value.

Genfib relies on the GNU MP arbitrary precision math library, which is
released under the GNU GPL v3 License.  No code within GNU MP codebase has
been altered, and it was compiled separately.

Genfib also relies on the libpng image persistence and depersistence library
to render images.  This is being linked from the /usr/local/lib/png.h that
homebrew installs when you do a 'brew install libpng' .. if you want some
other libpng, you need to change the three references in the rendering/
header and source files.

All testing and execution of this application has occurred on a Mac OS/X
Mountain Lion machine, using the "brew" installed GNU MP.

The code is pure C, only using std libs.

Upon execution it prints out the following table:

--

Column 0: Ordinal of the value, which is the n in f(n) when computing the
          Fibonacci value.
Column 1: Size in base10 of the value, which is the number of digits in
          the Fibonacci value.
Column 2: The Fibonacci value for said ordinal.  This column is optional; to
          disable the printing of this column you send the optional "n"
          parameter on the command line (e.g. "genfib 10 10 n").  It was made
          optional because at very high ordinals, Fibonacci numbers begin to
          have tens of thousands of digits.  Although the GNU MP arbitrary
          precision math library is extremely fast at working with massive
          numbers, it takes the computer a lot of time to convert them to
          strings and display/spool them to disk.  Plus the comma separated
          table which is generated cannot be loaded into traditional
          spreadsheet software with 20,000 digit numbers :)
Additional Columns: The computed modulo of the row's Fibonacci value.

--

   Command Line Arguments:
 --------------------------------
 -h                         Show the CSV Header
 -a                         Show Column Value
 -d                         Show Row Value
 -s                         Show the Approximate Number of Characters
 -o                         Show the Ordinal
 -r [number]                Show [number] Rows (default 10)
 -R [iteration_number]      Use [iteration_number] Algorithm for Row Values
 -c [number]                Show [number] Columns (default 10)
 -C [iteration_number]      Use [iteration_number] Algorithm for Column Values
 -I [computation_style]     Use [computation_style] for Intersections
 -i [file_name]             Create a png image of the set called [file_name]
 -?                         Show help

   Iteration Styles:
 -------------------------------
 1 . . . . . . . . . . Fibonacci
 2 . . . . . . . . . . . . Lucas
 3 . . . . . . . . . Incremental
 4 . . . . . . . . . . . Padovan
 5 . . . . . . . . . . . .  Pell

   Computation Styles:
 -------------------------------
 1 . . . . . . . . . . .  Modulo
 2 . . . . . . . . . . .  Divide
 3 . . . . . . . . . .  Multiply
 4 . . . . . . . . . . . . . Add
 5 . .. . . . . . . . . Subtract

--

For example, the executing without parameters returns a table of the
intersection between the first ten numbers in the Fibonacci Sequence
and the first ten integers:

	$ ./genfib
	0,0,0,0,0,0,0,0,0,0
	1,1,0,1,1,0,1,1,0,1
	1,1,2,0,2,2,1,0,1,1
	1,1,2,3,1,0,1,1,2,3
	1,1,2,3,0,3,3,1,4,0
	1,1,2,3,5,2,1,3,4,1
	1,1,2,3,5,1,6,0,6,6
	1,1,2,3,5,0,5,5,2,7
	1,1,2,3,5,8,4,3,7,1
	1,1,2,3,5,8,3,1,4,5

If we want to see the values for each, and a header, we could execute the
following:
	$ ./genfib -o -a -d -h
	Ordinal,Value,1,2,3,4,5,6,7,8,9,10
	,,1,1,2,3,5,8,13,21,34,55
	1,1,0,0,0,0,0,0,0,0,0,0
	2,2,1,1,0,1,1,0,1,1,0,1
	3,3,1,1,2,0,2,2,1,0,1,1
	4,4,1,1,2,3,1,0,1,1,2,3
	5,5,1,1,2,3,0,3,3,1,4,0
	6,6,1,1,2,3,5,2,1,3,4,1
	7,7,1,1,2,3,5,1,6,0,6,6
	8,8,1,1,2,3,5,0,5,5,2,7
	9,9,1,1,2,3,5,8,4,3,7,1
	10,10,1,1,2,3,5,8,3,1,4,5

Let's say we want to see the intersection between the Lucas set (rows) and
the Fibonacci set (columns):
	./genfib -o -a -d -h -R 2 -C 1
	Ordinal,Value,1,2,3,4,5,6,7,8,9,10
	,,1,1,2,3,5,8,13,21,34,55
	1,1,0,0,0,0,0,0,0,0,0,0
	2,3,1,1,2,0,2,2,1,0,1,1
	3,4,1,1,2,3,1,0,1,1,2,3
	4,7,1,1,2,3,5,1,6,0,6,6
	5,11,1,1,2,3,5,8,2,10,1,0
	6,18,1,1,2,3,5,8,13,3,16,1
	7,29,1,1,2,3,5,8,13,21,5,26
	8,47,1,1,2,3,5,8,13,21,34,8
	9,76,1,1,2,3,5,8,13,21,34,55
	10,123,1,1,2,3,5,8,13,21,34,55

And let's say we want to see the same intersection between the Lucas set
(rows) and the Fibonacci set (columns), but would like 15 row values and
8 columns:
	$ ./genfib -o -a -d -h -R 2 -C 1 -r 15 -c 8
	Ordinal,Value,1,2,3,4,5,6,7,8
	,,1,1,2,3,5,8,13,21
	1,1,0,0,0,0,0,0,0,0
	2,3,1,1,2,0,2,2,1,0
	3,4,1,1,2,3,1,0,1,1
	4,7,1,1,2,3,5,1,6,0
	5,11,1,1,2,3,5,8,2,10
	6,18,1,1,2,3,5,8,13,3
	7,29,1,1,2,3,5,8,13,21
	8,47,1,1,2,3,5,8,13,21
	9,76,1,1,2,3,5,8,13,21
	10,123,1,1,2,3,5,8,13,21
	11,199,1,1,2,3,5,8,13,21
	12,322,1,1,2,3,5,8,13,21
	13,521,1,1,2,3,5,8,13,21
	14,843,1,1,2,3,5,8,13,21
	15,1364,1,1,2,3,5,8,13,21

Maybe we decide we want to load this in Excel/Matlab/Maple/Sage and so
only need the data set... we could just run the following and pipe it to
a .csv file or directly script it into our math application:
	./genfib -R 2 -C 1 -r 15 -c 15
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	1,1,2,0,2,2,1,0,1,1,2,0,2,2,1
	1,1,2,3,1,0,1,1,2,3,1,0,1,1,2
	1,1,2,3,5,1,6,0,6,6,5,4,2,6,1
	1,1,2,3,5,8,2,10,1,0,1,1,2,3,5
	1,1,2,3,5,8,13,3,16,1,17,0,17,17,16
	1,1,2,3,5,8,13,21,5,26,2,28,1,0,1
	1,1,2,3,5,8,13,21,34,8,42,3,45,1,46
	1,1,2,3,5,8,13,21,34,55,13,68,5,73,2
	1,1,2,3,5,8,13,21,34,55,89,21,110,8,118
	1,1,2,3,5,8,13,21,34,55,89,144,34,178,13
	1,1,2,3,5,8,13,21,34,55,89,144,233,55,288
	1,1,2,3,5,8,13,21,34,55,89,144,233,377,89
	1,1,2,3,5,8,13,21,34,55,89,144,233,377,610
	1,1,2,3,5,8,13,21,34,55,89,144,233,377,610

Lastly we would like to see the intersection operation be subtract rather
than modulo:
	$ ./genfib -R 2 -C 1 -r 15 -c 15 -I 5
	0,0,1,2,4,7,12,20,33,54,88,143,232,376,609
	-2,-2,-1,0,2,5,10,18,31,52,86,141,230,374,607
	-3,-3,-2,-1,1,4,9,17,30,51,85,140,229,373,606
	-6,-6,-5,-4,-2,1,6,14,27,48,82,137,226,370,603
	-10,-10,-9,-8,-6,-3,2,10,23,44,78,133,222,366,599
	-17,-17,-16,-15,-13,-10,-5,3,16,37,71,126,215,359,592
	-28,-28,-27,-26,-24,-21,-16,-8,5,26,60,115,204,348,581
	-46,-46,-45,-44,-42,-39,-34,-26,-13,8,42,97,186,330,563
	-75,-75,-74,-73,-71,-68,-63,-55,-42,-21,13,68,157,301,534
	-122,-122,-121,-120,-118,-115,-110,-102,-89,-68,-34,21,110,254,487
	-198,-198,-197,-196,-194,-191,-186,-178,-165,-144,-110,-55,34,178,411
	-321,-321,-320,-319,-317,-314,-309,-301,-288,-267,-233,-178,-89,55,288
	-520,-520,-519,-518,-516,-513,-508,-500,-487,-466,-432,-377,-288,-144,89
	-842,-842,-841,-840,-838,-835,-830,-822,-809,-788,-754,-699,-610,-466,-233
	-1363,-1363,-1362,-1361,-1359,-1356,-1351,-1343,-1330,-1309,-1275,-1220,-1131,-987,-754

--

The best use of this application is spooling output to a file:
$ ./genfib 10000 1000 n > Table.csv

The command above will generate a Table.csv file.  Because with large
numbers of iterations it can take a *very long time*, the following command
may be useful when run from another terminal in the same folder:
$ tail -f Table.csv |sed 's/\([0-9]*\),\([0-9]*\),.*/Ordinal: \1 (\2 digits)/'

This will output the following:
	Ordinal: 1 (1 digits)
	Ordinal: 2 (1 digits)
	...
	Ordinal: 58521 (12230 digits)

And will continue to output lines until the command completes.

--

From Saphrosit on Stack Exchange:

 solved with a manual installation of libpng:

download the source from official web site
in Terminal, go in the downloaded folder and launch

cp ./scripts/makefile.darwin makefile
make
sudo make install
make clean
if it doesn't work (as in my case) open makefile with TextEdit (or equivalent) and change line

ARCH="-arch i386 -arch x86_64"

in

ARCH=-arch x86_64

(assuming, of course, your system is 64 bit).

--

The genfib application is released under the MIT license:

Copyright (c) 2013 Steven Velozo (steven@velozo.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
