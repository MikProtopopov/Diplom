#ifndef PAINTRASTR_H
#define PAINTRASTR_H

#include <QWidget>

class PaintRastr : public QWidget
{
    Q_OBJECT
public:
    explicit PaintRastr(QWidget *parent = 0);
    void drawRastr();
    void setParameters(int height, int width, int count);
    int ProcessX(int i, int iRastr);
    int ProcessY(int j, int jRastr);
    void setRastr(int **&localRastr);
    int **rastr3;


protected:
    void paintEvent(QPaintEvent *);

private:
    int windowHeight; // Height of the draw window
    int windowWidth; // Width of the draw window
    int rastrHeight; // Height of rastr
    int rastrWidth; // Width of rastr
    int indentSpace; // Space between the border of the canvas and the rastr
    int elemCount; // Amount of elements on one side of rastr
    int cellHeight; // Height of one cell in rastr
    int cellWidth; // Width of

signals:

public slots:
};

#endif // PAINTRASTR_H
