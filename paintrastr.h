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

#ifndef PAINTRASTR_H
#define PAINTRASTR_H

#include <QWidget>

class PaintRastr : public QWidget
{
    Q_OBJECT
public:
    explicit PaintRastr(QWidget *parent = 0);
    void setParameters(int height, int width, int axisX, int axisY, int step, QColor color);
    int ProcessX(int i);
    int ProcessY(int j);
    void setRastr(int **&localRastr);
    int **rastr;
    int stepMov; // Step of movement


protected:
    void paintEvent(QPaintEvent *);

private:
    int windowHeight; // Height of the draw window
    int windowWidth; // Width of the draw window
    int rastrHeight; // Height of rastr
    int rastrWidth; // Width of rastr
    int indentSpace; // Space between the border of the canvas and the rastr
    int elemCountX; // Amount of elements on one side of rastr
    int elemCountY; // Amount of elements on one side of rastr
    int cellHeight; // Height of one cell in rastr
    int cellWidth; // Width of one cell
    QColor rastrColor;


signals:

public slots:
};

#endif // PAINTRASTR_H
