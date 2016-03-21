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

#include "diplom.h"
#include "ui_diplom.h"
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
Diplom::Diplom(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Diplom)
{
    ui->setupUi(this);
    dialog = new Dialog(this);
    sWindow = new StartWindow(this);
    paintRastr1 = new PaintRastr(this);

    ui->verticalLayout->addWidget(paintRastr1);

    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(on_actionExport_clicked()));
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(on_actionImport_clicked()));
    connect(ui->actionNew_2, SIGNAL(triggered()), this, SLOT(on_actionNew_clicked()));
}

Diplom::~Diplom()
{
    paintRastr1->deleteLater();
    delete ui;
}



// Error Processing Facility
void Diplom::errorHandling(int errorCode)
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

void Diplom::on_actionSave_clicked()
{

}

void Diplom::on_pushButtonLeft_clicked()
{
    dialog->show();
    dialog->activateWindow();
}

void Diplom::on_actionNew_clicked()
{
    if ((rastrManipulation.rastr1)&&(rastrManipulation.checkForSave()))
        rastrManipulation.deleteArray(rastrManipulation.iRastr);
    sWindow->show();
    sWindow->activateWindow();
}

void Diplom::on_actionImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Импортировать"),
                                                    "", tr("Текстовый файл (*.txt);"));
    errorHandling(rastrManipulation.importRastr(fileName));

    paintRastr1->setParameters(ui->graphicsView_1->height(), ui->graphicsView_1->width(),rastrManipulation.jRastr);
//    rastrManipulation.fillRastr2();
    paintRastr1->setRastr(rastrManipulation.rastr1);
//    for (int i=0; i<rastrManipulation.jRastr*2+1; i++)
//    {
//        ui->tableWidget->insertRow(i);
//        QString rastrAnswer = QString::number(rastrManipulation.compareRastr(i,1));
//        ui->tableWidget->setItem(0,i,new QTableWidgetItem(rastrAnswer));
//    }
}

void Diplom::on_actionExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Экспортировать"),
                                                    "", tr("Текстовый файл (*.txt);;Все файлы(*)"));
    errorHandling(rastrManipulation.exportRastr(fileName));
}
