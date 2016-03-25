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

#ifndef PAINTGRAPH_H
#define PAINTGRAPH_H

#include <QWidget>

class PaintGraph : public QWidget
{
    Q_OBJECT
public:
    explicit PaintGraph(QWidget *parent = 0);
    void setParameters(int height, int width, int step, int countX, int countY);
    int ProcessX(int x);
    int ProcessY(int y);
    void setCount(int count);
    int processCount(int count);
    int processStep(int step);
    int stepMov;
    int windowCount;
    int prevPointX;
    int prevPointY;

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    int windowHeight; // Height of the draw window
    int windowWidth; // Width of the draw window
    int indentSpace; // Space between the border of the canvas and the rastr
    int elemCountX; // Amount of elements on one side of rastr
    int elemCountY; // Amount of elements on one side of rastr
    int drawAreaWidth;
    int drawAreaHeight;

};

#endif // PAINTGRAPH_H
