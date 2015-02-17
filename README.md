# didimama

didimama is program to measure difference distance matrix map
Copyright 2015 Miguel A. Ballicora

## Compilation and Installation in GNU/Linux

type

`make`

to generate the program and then

`make install`

or `sudo make install` in Ubuntu. The program is very portable, so it should be very easy to compile in other systems.

## Usage

As an example, a typical use would be

`didimama -a file1.pdb -b file2.pdb -f 100 -t 300 > map.csv`

then, difference distances will be measured between `file1.pdb` and `file2.pdb` from residue 100 to 300
The output will be in a comma separated value file `map.csv`, which can be processed with QTIplot to obtain a heat map.

There is a further help if didimama is executed with the switch -h in the command line. That is:
```
Obtain a delta distance matrix map (didimama)

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
```


