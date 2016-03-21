// Copyright 2016, Protopopov Mikhail G. <mikprotopopov@yandex.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RASTRMANIPULATION_H
#define RASTRMANIPULATION_H

#include <QMainWindow>

class RastrManipulation
{
public:
    RastrManipulation();
    int importRastr(QString fileName);
    int exportRastr(QString fileName);
    void deleteArray(int DeleteLines);
    void fillRastr2();
    int compareRastr(int stepHorisontal, int stepVertical);
    int checkForSave();
    //
    bool oscillation; // Oscillation on/off (1/0)
    int iRastr; //Number of lines in Rastr
    int jRastr; //Number of elements in lines of Rastr
    int **rastr1; //main matrix, dynamic
    int **rastr2; //copy of rastr1, for scanning


    void createNewRastr(const int &xInt, const int &yInt);
};

#endif // RASTRMANIPULATION_H
