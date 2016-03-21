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
