/*
	Didimama is program calculating difference distance matrix maps
	between two different protein conformers.
    Copyright 2015 Miguel A. Ballicora

    This file is part of Didimama.

    Didimama is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ordo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Didimama.  If not, see <http://www.gnu.org/licenses/>.
*/

#if !defined(H_RMSDCMP)
#define H_RMSDCMP
/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

extern int rmsdcmp(char *FILE1, char* FILE2, int window);

extern int matdist(char *FILE1, char* FILE2, int resfr, int resto);

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#endif

