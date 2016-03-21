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
