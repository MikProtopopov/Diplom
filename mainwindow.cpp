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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "startwindow.h"
#include "rastrmanipulation.h"
#include "paintrastr.h"
#include "qcustomplot.h"

#include <malloc.h>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <QString>
#include <QMenu>
#include <QMenuBar>
#include <QIODevice>
#include <cstdlib>
#include <stdlib.h>
#include <QWidget>

using namespace std;
// Constructor for MainWindow
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dialog = NULL;
    sWindow = NULL;
    paintRastr1 = NULL;
    paintRastr2 = NULL;
    try
    {
        dialog = new Dialog(this);
        sWindow = new StartWindow(this);
        paintRastr1 = new PaintRastr(this);
        paintRastr2 = new PaintRastr(this);
    } catch (...){
        QMessageBox::information(this, tr("Ошибка"), tr("Недостаточно памяти для работы программы."));
        if (NULL != dialog)
            dialog->deleteLater();
        if (NULL != sWindow)
            sWindow->deleteLater();
        if (NULL != paintRastr1)
            paintRastr1->deleteLater();
        if (NULL != paintRastr2)
            paintRastr2->deleteLater();
        exit(0);
    }

    ui->verticalLayout->addWidget(paintRastr1);
    ui->verticalLayout_2->addWidget(paintRastr2);

    // Hiding plots for graphs
    ui->customPlot1->hide();
    ui->customPlot2->hide();
    ui->customPlot3->hide();

    // Adding graphs on plots
    ui->customPlot1->addGraph();
    ui->customPlot2->addGraph();
    ui->customPlot3->addGraph();

    // Adding first (0) element to vectors
    graphX.append(0);
    graphY.append(0);

    // Setting first point in graphs
    ui->customPlot1->graph(0)->setData(graphX,graphY);
    ui->customPlot2->graph(0)->setData(graphXOsci,graphYOsci);
    ui->customPlot3->graph(0)->setData(graphXComp,graphYComp);

    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(on_actionExport_clicked()));
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(on_actionImport_clicked()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_clicked()));

}

MainWindow::~MainWindow()
{
    paintRastr1->deleteLater(); // Clearing paintRastr1 from memory
    paintRastr2->deleteLater(); // Clearing paintRastr2 from memory
    delete ui; // Clearing UI from memory
}

// Function for drawing lines on non-oscillated graph
int MainWindow::drawGraph(QCustomPlot *customPlot)
{
    // Stop work if rastr, needed for work, does not exist
    if (NULL == rastrManipulation.rastr1)
        return 0;

    try {
        graphX.append(paintRastr2->stepMov); // Add value to vector for horizontal coordinates
        graphY.append(rastrManipulation.compareRastr(paintRastr2->stepMov,1)); // Add value to vector for vertical coordinates
    } catch(...){
        return 7;
    }

    customPlot->graph(0)->setData(graphX,graphY); // Sets point on the graph and connects it to the precious point
    customPlot->replot(); // Refreshes the plot
    return 0;
}

// Function for drawing lines on oscillated graph
int MainWindow::drawGraphOsci(QCustomPlot *customPlot)
{
    // Stop work if rastr, needed for work, does not exist
    if (NULL == rastrManipulation.rastr1)
        return 0;

    try {
        graphXOsci.append(paintRastr2->stepMov); // Add value to vector for horizontal coordinates
        graphYOsci.append(rastrManipulation.compareRastr(paintRastr2->stepMov,0)); // Add value to vector for vertical coordinates
    } catch(...){
        return 7;
    }

    customPlot->graph(0)->setData(graphXOsci,graphYOsci); // Sets point on the graph and connects it to the precious point
    customPlot->replot(); // Refreshes the plot
    return 0;
}

// Function for drawing lines on comparison graph
int MainWindow::drawGraphCompare(QCustomPlot *customPlot)
{
    // Stop work if rastr, needed for work, does not exist
    if (NULL == rastrManipulation.rastr1)
        return 0;

    try {
        graphXComp.append(paintRastr2->stepMov); // Add value to vector for horizontal coordinates
        graphYComp.append(
                    (abs(rastrManipulation.compareRastr(paintRastr2->stepMov,1) - rastrManipulation.compareRastr(paintRastr2->stepMov,0))
                    + (rastrManipulation.compareRastr(paintRastr2->stepMov,1) - rastrManipulation.compareRastr(paintRastr2->stepMov,0))) / 2); // Difference between rastrs
    } catch(...){
        return 7;
    }

    customPlot->graph(0)->setData(graphXComp,graphYComp); // Sets point on the graph and connects it to the precious point
    customPlot->replot(); // Refreshes the plot
    return 0;
}

// Error Processing Facility
void MainWindow::errorHandling(int errorCode) // Takes an error code and matches it with known errors. Sends message out about this error
{
    switch(errorCode)
    {
    case 0:
        break;
    case 2:
        QMessageBox::information(this, tr("Ошибка"), tr("Не удалось открыть файл."));
        break;
    case 3:
        QMessageBox::information(this, tr("Ошибка"), tr("Неверное количество строк."));
        break;
    case 4:
        QMessageBox::information(this, tr("Ошибка"), tr("Неверное число элементов в строке."));
        break;
    case 5:
        QMessageBox::information(this, tr("Ошибка"), tr("Некорректный элемент в строке."));
        break;
    case 6:
        QMessageBox::information(this, tr("Ошибка"), tr("Имя файла пустое."));
        break;
    case 7:
        QMessageBox::information(this, tr("Ошибка"), tr("Сбой в построении графика."));
        rastrManipulation.deleteArray(rastrManipulation.iRastr);
        exit(0);
    }
}

// Triggers saving feature
void MainWindow::on_actionSave_clicked()
{

}

// Triggers the start of rastr comparison
void MainWindow::on_pushButtonStart_clicked()
{
    if (QDialog::Accepted == dialog->exec())
        return;

    // TO DO CHECK HOW USER CLOSED THE WINDOW

    paintRastr2->setParameters(ui->graphicsView_1->height(), ui->graphicsView_1->width(),
                               rastrManipulation.iRastr - rastrManipulation.oscillation, rastrManipulation.jRastr,0, Qt::black,
                               rastrManipulation.iRastr, rastrManipulation.jRastr); // Set parameters for moving rastr
    paintRastr2->setRastr(rastrManipulation.rastr2);

    ui->pushButtonStep->setEnabled(1);
}

// Triggers the window for creating of the new rastr
// TO DO EVERYTHING
void MainWindow::on_actionNew_clicked()
{
    if ((rastrManipulation.rastr1)&&(rastrManipulation.checkForSave()))
        rastrManipulation.deleteArray(rastrManipulation.iRastr);
    sWindow->show();
    sWindow->activateWindow();
    ui->pushButtonStart->setEnabled(1);
}

// Triggers import of a rastr from a text file
void MainWindow::on_actionImport_clicked()
{
    // TO DO CHECK FOR EXISTING RASTR AND SEE IF USER WANTS TO SAVE IT
    QString fileName = QFileDialog::getOpenFileName(this, tr("Импортировать"),
                                                    "", tr("Текстовый файл (*.txt);")); // Call for an "import" window
    if (fileName.isEmpty())
        return;

    errorHandling(rastrManipulation.importRastr(fileName));

    paintRastr1->setParameters(ui->graphicsView_1->height(), ui->graphicsView_1->width(),
                               rastrManipulation.iRastr, rastrManipulation.jRastr,rastrManipulation.jRastr, Qt::gray,
                               rastrManipulation.iRastr, rastrManipulation.jRastr); // Set parameters for background rastr
    try {
        ui->customPlot1->show(); // Shows first graph on the main form
        ui->customPlot2->show();
        ui->customPlot3->show();
    } catch (...) {
        QMessageBox::information(this, tr("Ошибка"), tr("Сбой в построении графика."));
        rastrManipulation.deleteArray(rastrManipulation.iRastr);
        exit(0);
    }

    errorHandling(rastrManipulation.fillRastr2()); // Fills second, moving rastr
    paintRastr1->setRastr(rastrManipulation.rastr1); // Sets matrix for background rastr

    ui->pushButtonStart->setEnabled(1); // Enables "Start" button

    // give the axes some labels:
    ui->customPlot1->xAxis->setLabel("");
    ui->customPlot1->yAxis->setLabel("");
    // set axes ranges, so we see all data:
    ui->customPlot1->xAxis->setRange(0, rastrManipulation.iRastr*2);
    ui->customPlot1->yAxis->setRange(0, rastrManipulation.compareRastr(rastrManipulation.iRastr,1) + 2);

    ui->customPlot2->xAxis->setLabel("");
    ui->customPlot2->yAxis->setLabel("");
    // set axes ranges, so we see all data:
    ui->customPlot2->xAxis->setRange(0, rastrManipulation.iRastr*2);
    ui->customPlot2->yAxis->setRange(0, rastrManipulation.compareRastr(rastrManipulation.iRastr,1) + 2);

    ui->customPlot3->xAxis->setLabel("");
    ui->customPlot3->yAxis->setLabel("");
    // set axes ranges, so we see all data:
    ui->customPlot3->xAxis->setRange(0, rastrManipulation.iRastr*2);
    ui->customPlot3->yAxis->setRange(0, rastrManipulation.compareRastr(rastrManipulation.iRastr,1) + 2);

    errorHandling(drawGraph(ui->customPlot1)); // Draw line in graph 1
    if (1 == rastrManipulation.oscillation)
    {
        errorHandling(drawGraphOsci(ui->customPlot2)); // Draw line in graph 2
        errorHandling(drawGraphCompare(ui->customPlot3)); // Draw line in graph 3
    }

    ui->actionExport->setEnabled(1);
}

// Triggers export from a rastr into a text file
void MainWindow::on_actionExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Экспортировать"),
                                                    "", tr("Текстовый файл (*.txt);;Все файлы(*)")); // Call for an "export" window
    if (fileName.isEmpty())
        return;

    errorHandling(rastrManipulation.exportRastr(fileName));
}

// Triggers movement of the moving rastr
void MainWindow::on_pushButtonStep_clicked()
{
    if (1 == rastrManipulation.oscillation)
    {
        if ((paintRastr2->stepMov < rastrManipulation.jRastr * 2)&&(paintRastr2->stepMov == paintRastr2->oStatus))
            paintRastr2->stepMov += 1;  // Do a step
        else
            paintRastr2->oStatus += 1;

        if (0 == paintRastr2->oStatus % 2)
            errorHandling(drawGraph(ui->customPlot1)); // Draw line in graph 1
        else
        {
            errorHandling(drawGraphOsci(ui->customPlot2)); // Draw line in graph 2
            errorHandling(drawGraphCompare(ui->customPlot3)); // Draw line in graph 3
        }
    }
    else
        if (paintRastr2->stepMov < rastrManipulation.jRastr * 2)
        {
            paintRastr2->stepMov += 1;  // Do a step
            errorHandling(drawGraph(ui->customPlot1)); // Draw line in graph 1
        }

    paintRastr2->update(); // Update painted rastr with new coordinates
}

// Quits the program
void MainWindow::on_actionQuit_triggered()
{
    // TO DO CHECK FOR SAVE
    if (NULL != rastrManipulation.rastr1)
        rastrManipulation.deleteArray(rastrManipulation.iRastr);
    exit(0);
}
