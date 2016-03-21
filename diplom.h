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

#ifndef DIPLOM_H
#define DIPLOM_H

#include <QMainWindow>
#include <QWidget>
#include "dialog.h"
#include "startwindow.h"
#include "rastrmanipulation.h"
#include "paintrastr.h"

namespace Ui {
class Diplom;
}

class Diplom : public QMainWindow
{
    Q_OBJECT

public:
    explicit Diplom(QWidget *parent = 0);
    ~Diplom();
    void errorHandling(int);
    RastrManipulation rastrManipulation;
    PaintRastr *paintRastr1;
    PaintRastr *paintRastr2;

private slots:
    void on_pushButtonLeft_clicked();
    void on_actionExport_clicked();
    void on_actionImport_clicked();
    void on_actionNew_clicked();

private:
    Ui::Diplom *ui;
    Dialog *dialog;
    StartWindow *sWindow;
    void createAction();
    void createMenu();
    void newFile();
    void open();
    void save();
    void saveAs();
    void quit();

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionLoad;
    QAction *actionQuit;
    QAction *exitAction;
    QAction *actionExport;
    QAction *actionImport;


    void on_actionSave_clicked();
};

#endif // DIPLOM_H
