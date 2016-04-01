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

#include "paintgraph.h"
#include "rastrmanipulation.h"
#include <QPainter>

PaintGraph::PaintGraph(QWidget *parent) : QWidget(parent)
{
    stepMov = -1;
    windowCount = 0;
}

void PaintGraph::setParameters(int height, int width, int step, int countX, int countY)
{
    windowHeight = height;
    windowWidth = width;
    indentSpace = 10;
    stepMov = step;
    elemCountX = countX;
    elemCountY = countY;
    drawAreaHeight = windowHeight - indentSpace*2;
    drawAreaWidth = windowWidth - indentSpace*2;
    prevPointX = indentSpace;
    prevPointY = indentSpace;
}

int PaintGraph::ProcessX(int x)
{
    return x + indentSpace;
}

int PaintGraph::ProcessY(int y)
{
    return y + indentSpace;
}

int PaintGraph::processCount(int count)
{
    return drawAreaHeight - indentSpace - count*(drawAreaHeight / elemCountX / elemCountY * 2);
}

int PaintGraph::processStep()
{
    return indentSpace + stepMov*(drawAreaWidth / elemCountY / 2);
}

void PaintGraph::paintEvent(QPaintEvent *)
{
    if (-1 != stepMov)
    {
        QPainter main(this);
        main.setPen(QPen(Qt::black,2,Qt::SolidLine));
        main.drawLine(prevPointY, prevPointX, processStep(), processCount(windowCount));

        prevPointX = processCount(windowCount);
        prevPointY = processStep();
    }
}


















