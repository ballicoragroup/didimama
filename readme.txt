DIDIMAMA

To compile, type 

make

then, if you have ruby installed, you can run a quicktest with

ruby quicktest.rb

This program obtains a delta distance matrix map (didimama).

quick example: didimama -a file1.pdb -b file2.pdb -f 260 -t 519

delta distance matrix map is created from residues 260 to 519 in this example.
files for comparison are file1.pdb and file2.pdb
output is in comma separated values

usage: didimama [-OPTION]
 -h        print this help
 -v        print version number and exit
 -L        display the license information
 -a <file> first  input file (pdb format)
 -b <file> second input file (pdb format)
 -f <num>  first residue number included in the analysis
 -t <num>  last  residue number included in the analysis

Copyright (c) 2015 Miguel A. Ballicora
There is NO WARRANTY of any kind

=====================================================================================
"   Copyright (c) 2015 Miguel A. Ballicora\n"
"   Didimama is program fobtains a delta distance matrix map in protein structures\n"
"\n"
"   Didimama is free software: you can redistribute it and/or modify\n"
"   it under the terms of the GNU General Public License as published by\n"
"   the Free Software Foundation, either version 3 of the License, or\n"
"   (at your option) any later version.\n"
"\n"
"   Didimama is distributed in the hope that it will be useful,\n"
"   but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
"   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
"   GNU General Public License for more details.\n"
"\n"
"   You should have received a copy of the GNU General Public License\n"
"   along with Didimama.  If not, see <http://www.gnu.org/licenses/>.\n"
;

