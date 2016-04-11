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

#define indentSpace 10

// Constructor
PaintRastr::PaintRastr(QWidget *parent) : QWidget(parent)
{
    rastr = NULL;
    stepMov = 0;
    bgColor = Qt::white;
}

// Set parameters for calculations
void PaintRastr::setParameters(int height, int width, int axisX, int axisY, int step, QColor color,
                               int staticAxisX, int staticAxisY, int typeOfRastr)
{
    elemCountX = axisX; // Rastr's dimentions on X axis
    elemCountY = axisY; // Rastr's dimentions on Y axis
    staticX = staticAxisX;
    staticY = staticAxisY;
    cellHeight = (height - 2*indentSpace) / staticX; // Height of one cell of rastr
    cellWidth = (width / 3 - 2*indentSpace) / staticY; // Width of one cell of rastr
    rastr = NULL; // Empty moving rastr
    stepMov = step;
    rastrColor = color;
    oStatus = 0;
    rastrType = typeOfRastr;
    cellColor = Qt::white;
}

void PaintRastr::setBGColor(QColor color)
{
    bgColor = color;
}

// Returns the color
QColor PaintRastr::getBGColor()
{
    return bgColor;
}

// Set new color for drawing background rastr
void PaintRastr::setRastrColor(QColor color0, QColor color1)
{
    rastrColor = color0;
    cellColor = color1;
}

// Procces coordinate on X axis
int PaintRastr::ProcessX(int i)
{
   return indentSpace + i*cellHeight;

}

// Procces coordinate on Y axis
int PaintRastr::ProcessY(int j)
{
   return indentSpace + (j + abs(staticX-elemCountX))*cellWidth - (oStatus % 2)*cellWidth;
}

// Drawing
void PaintRastr::paintEvent(QPaintEvent *)
{
    if (NULL == rastr)
        return;

    if (0 == rastrType)
    {
        QPainter bg(this);
        bg.setPen(QPen(bgColor,1,Qt::SolidLine));
        QRect bgRect = QRect(0,0, 780, 270); // CHANGE 780 and 270 FOR ACTUAL VARIABLES WITH H/W OF GRAPHICSVIEW_1
        bg.fillRect(bgRect,QColor(bgColor));
    }

    QPainter main(this);
    main.setPen(QPen(rastrColor,1,Qt::SolidLine));

    for (int i=0; i < elemCountY; i++)
        for (int j=0; j < elemCountX; j++)
        {
            if (0 == rastr[j][i])
            {
                QRect rect = QRect(ProcessX(i + stepMov),ProcessY(j),cellHeight,
                               cellWidth); // Draw rectangle
                main.fillRect(rect,QColor(rastrColor)); // Fill rectangle
            }
            if ((1 == rastr[j][i]) && (0 == rastrType))
            {
                QRect rect = QRect(ProcessX(i + stepMov),ProcessY(j),cellHeight,
                               cellWidth); // Draw rectangle
                main.fillRect(rect,QColor(cellColor)); // Fill rectangle
            }
        }
    main.drawRect(ProcessX(stepMov),ProcessY(0),cellHeight*elemCountY,cellWidth*elemCountX);
}

// Set moving rastr
void PaintRastr::setRastr(int **&localRastr)
{
    rastr = localRastr;
}

