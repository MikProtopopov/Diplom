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


PaintRastr::PaintRastr(QWidget *parent) : QWidget(parent)
{
    rastr3 = NULL;
}

void PaintRastr::setParameters(int height, int width, int count)
{
    RastrManipulation rastrManipulation;
    windowHeight = height; // Высота области рисования
    windowWidth = width; // Ширина области рисования
    indentSpace = windowHeight*0.04; // Отступ от краев
    rastrHeight = windowHeight - indentSpace; // Высота рисуемого растра
    rastrWidth = (windowWidth - indentSpace) / 3 - indentSpace; // Ширина рисуемого растра
    elemCount = count; // Размерность растра
    cellHeight = rastrHeight / elemCount; // Размер одной рисуемой ячейки растра
    cellWidth = rastrWidth / elemCount;
    rastr3 = NULL;
}

// Обработка координаты X
int PaintRastr::ProcessX(int i, int iRastr)
{
   return indentSpace + i*(rastrHeight/iRastr);
}

// Обработка координаты Y
int PaintRastr::ProcessY(int j, int jRastr)
{
   return indentSpace + j*(rastrWidth/jRastr);
}

void PaintRastr::paintEvent(QPaintEvent *)
{
    if(NULL == rastr3)
        return;
    QPainter main(this);
    main.setPen(QPen(Qt::black,2,Qt::SolidLine));
    main.drawRect(ProcessX(0,0) + rastrWidth,ProcessY(0,0),rastrHeight,rastrWidth);
    main.drawRect(ProcessX(0,0) + rastrWidth*2,ProcessY(0,0),rastrHeight,rastrWidth);

    for (int i=0; i < elemCount; i++)
        for (int j=0; j < elemCount; j++)
        {
            if (0 == rastr3[j][i])
            {
                QRect rect = QRect(ProcessX(i,elemCount) + rastrWidth,ProcessY(j,elemCount),cellHeight,
                               cellWidth); // Draw rectangle
                main.fillRect(rect,QColor(0,0,0,255)); // Fill rectangle
            }
        }

    for (int i=0; i < elemCount; i++)
        for (int j=0; j < elemCount; j++)
        {
            if (0 == rastr3[j][i])
            {
                QRect rect = QRect(ProcessX(i,elemCount) + rastrWidth*2,ProcessY(j,elemCount),cellHeight,
                               cellWidth); // Draw rectangle
                main.fillRect(rect,QColor(0,0,0,255)); // Fill rectangle
            }
        }
}

void PaintRastr::setRastr(int **&localRastr)
{
        rastr3 = localRastr;
}

void PaintRastr::drawRastr()
{

}
