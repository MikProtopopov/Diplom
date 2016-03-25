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
//
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialog = new Dialog(this);
    sWindow = new StartWindow(this);
    paintRastr1 = new PaintRastr(this);
    paintRastr2 = new PaintRastr(this);
    paintGraph1 = new PaintGraph(this);

    ui->verticalLayout->addWidget(paintRastr1);
    ui->verticalLayout_2->addWidget(paintRastr2);
    ui->verticalLayout_3->addWidget(paintGraph1);

    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(on_actionExport_clicked()));
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(on_actionImport_clicked()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(on_actionNew_clicked()));
}

MainWindow::~MainWindow()
{
    paintRastr1->deleteLater();
    paintRastr2->deleteLater();
    paintGraph1->deleteLater();
    delete ui;
}

// Error Processing Facility
void MainWindow::errorHandling(int errorCode)
{
    switch(errorCode)
    {
    case 0:
        return;
    case 6:
        QMessageBox::information(this, tr("Ошибка 6"), tr("Имя файла пустое."));
        return;
    case 2:
        QMessageBox::information(this, tr("Ошибка 2"), tr("Не удалось открыть файл."));
        return;
    case 3:
        QMessageBox::information(this, tr("Ошибка 3"), tr("Неверное количество строк."));
        return;
    case 4:
        QMessageBox::information(this, tr("Ошибка 4"), tr("Неверное число элементов в строке."));
        return;
    case 5:
        QMessageBox::information(this, tr("Ошибка 5"), tr("Некорректный элемент в строке."));
        return;
    }
}

void MainWindow::on_actionSave_clicked()
{

}

void MainWindow::on_pushButtonLeft_clicked()
{
    dialog->show();
    dialog->activateWindow();
}

void MainWindow::on_actionNew_clicked()
{
    if ((rastrManipulation.rastr1)&&(rastrManipulation.checkForSave()))
        rastrManipulation.deleteArray(rastrManipulation.iRastr);
    sWindow->show();
    sWindow->activateWindow();
    ui->pushButtonLeft->setEnabled(1);
}

void MainWindow::on_actionImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Импортировать"),
                                                    "", tr("Текстовый файл (*.txt);"));
    errorHandling(rastrManipulation.importRastr(fileName));

    paintRastr1->setParameters(ui->graphicsView_1->height(), ui->graphicsView_1->width(),
                               rastrManipulation.iRastr, rastrManipulation.jRastr,0);
    paintRastr2->setParameters(ui->graphicsView_1->height(), ui->graphicsView_1->width(),
                               rastrManipulation.iRastr, rastrManipulation.jRastr,0);
    paintGraph1->setParameters(ui->graphicsView_2->height(), ui->graphicsView_2->width(), 0,
                               rastrManipulation.iRastr,rastrManipulation.jRastr);

    rastrManipulation.fillRastr2();
    paintRastr1->setRastrBg(rastrManipulation.rastr1);
    paintRastr2->setRastrMov(rastrManipulation.rastr2);

    ui->pushButtonLeft->setEnabled(1);
    ui->pushButtonStep->setEnabled(1);
}

void MainWindow::on_actionExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Экспортировать"),
                                                    "", tr("Текстовый файл (*.txt);;Все файлы(*)"));
    errorHandling(rastrManipulation.exportRastr(fileName));
}

void MainWindow::on_pushButtonStep_clicked()
{
    if (paintRastr2->stepMov < rastrManipulation.jRastr * 2)
    paintRastr2->stepMov += 1;
    paintRastr2->update();

    paintGraph1->stepMov +=1;
    paintGraph1->windowCount = rastrManipulation.compareRastr(paintGraph1->stepMov, 0);
    paintGraph1->update();
}
