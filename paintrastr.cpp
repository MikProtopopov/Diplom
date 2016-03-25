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

#include "paintrastr.h"
#include "rastrmanipulation.h"
#include <QPainter>

// Constructor
PaintRastr::PaintRastr(QWidget *parent) : QWidget(parent)
{
    rastrBg = NULL;
    rastrMov = NULL;
    stepMov = 0;
}

// Set parameters for calculations
void PaintRastr::setParameters(int height, int width, int axisX, int axisY, int step)
{
    RastrManipulation rastrManipulation;
    windowHeight = height; // Height of the paint area
    windowWidth = width; // Width of the paint area
    indentSpace = 10; // Border margin
    rastrHeight = windowHeight - 2*indentSpace; // Height of the drawn rastr
    rastrWidth = windowWidth / 3 - 2*indentSpace; // Width of the drawn rastr
    elemCountX = axisX; // Rastr's dimentions on X axis
    elemCountY = axisY; // Rastr's dimentions on Y axis
    cellHeight = rastrHeight / elemCountY; // Height of one cell of rastr
    cellWidth = rastrWidth / elemCountX; // Width of one cell of rastr
    rastrBg = NULL; // Empty background rastr
    rastrMov = NULL; // Empty moving rastr
    stepMov = step;
}

// Procces coordinate on X axis
int PaintRastr::ProcessX(int i, int iRastr, int step)
{
   return indentSpace + i*(rastrHeight/iRastr) + step*cellHeight;
}

// Procces coordinate on Y axis
int PaintRastr::ProcessY(int j, int jRastr)
{
   return indentSpace + j*(rastrWidth/jRastr);
}

// Drawing
void PaintRastr::paintEvent(QPaintEvent *)
{
    QPainter main(this);
    main.setPen(QPen(Qt::black,2,Qt::SolidLine));

    if (NULL != rastrBg)
    {
        main.drawRect(ProcessX(0,0,0) - indentSpace,ProcessY(0,0),rastrHeight,rastrWidth);
        for (int i=0; i < elemCountY; i++)
            for (int j=0; j < elemCountX; j++)
            {
                if (0 == rastrBg[j][i])
                {
                    QRect rect = QRect(ProcessX(i,elemCountX,0) - indentSpace,ProcessY(j,elemCountY),cellHeight,
                                   cellWidth); // Draw rectangle
                    main.fillRect(rect,QColor(150,150,150,255)); // Fill rectangle
                }
            }
        main.drawRect(ProcessX(0,0,0) - indentSpace,ProcessY(0,0),rastrHeight,rastrWidth);
    }
    else
        if (NULL != rastrMov)
        {
            for (int i=0; i < elemCountY; i++)
                for (int j=0; j < elemCountX; j++)
                {
                    if (0 == rastrMov[j][i])
                    {
                        QRect rect = QRect(ProcessX(i,elemCountX,stepMov),ProcessY(j,elemCountY),cellHeight,
                                       cellWidth); // Draw rectangle
                        main.fillRect(rect,QColor(0,0,0,255)); // Fill rectangle
                    }
                }
            main.drawRect(ProcessX(0,0,stepMov),ProcessY(0,0),rastrHeight,rastrWidth);
        }
    else
        return;
}

// Set rastr for background (not moving)
void PaintRastr::setRastrBg(int **&localRastr)
{
    rastrBg = localRastr;
}

// Set moving rastr
void PaintRastr::setRastrMov(int **&localRastr)
{
    rastrMov = localRastr;
}

